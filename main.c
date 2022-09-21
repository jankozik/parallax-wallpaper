#include <X11/Xlib.h>
#include <SDL2/SDL.h>
#include <linux/limits.h>

typedef struct
{
	SDL_Rect dest;
	SDL_Texture *buffTex;
} Instance;

void init(Display **display, SDL_Window **window, SDL_Renderer **renderer)
{
	*display = XOpenDisplay(NULL);	
	Window rootWindow = RootWindow(*display, DefaultScreen(*display));

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
		SDL_Log("%s", SDL_GetError());

	*window = SDL_CreateWindowFrom((void*)rootWindow);	
	if(*window == NULL)
		SDL_Log("%s", SDL_GetError());

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(*renderer == NULL)
		SDL_Log("%s", SDL_GetError());

}

void loadTextures(SDL_Renderer *renderer, SDL_Texture **tex, char *dir, int count, int *srcWidth, int *srcHeight)
{
	char path[PATH_MAX];

	for(int i = 0; i < count; i++)
	{
		sprintf(path, "%s/%d.bmp", dir, i+1);
		SDL_Surface *surf = SDL_LoadBMP(path);
		if(i == 0)
		{
			*srcWidth = surf->w;
			*srcHeight = surf->h;
		}
		tex[i] = SDL_CreateTextureFromSurface(renderer, surf);
		SDL_FreeSurface(surf);
	}
}

int main(int argc, char *argv[])
{
	if((argc-3)%4 != 0 || argc < 7)
	{
		printf("\nLayered Wallpaper Engine\n");
		printf("Usage:\n");
		printf("	lwp [layers count] [img dir] [monitor1 options] [monitor2 options] ...\n\n");
		printf("Monitor options:\n");
		printf("	[x] [y] [width] [height]\n\n");
		return 0;
	}
	int instancesCount = (argc-2)/4;

	Instance instances[instancesCount];

	int count = atoi(argv[1]);
	char *dir = argv[2];

	int srcWidth, srcHeight;

	Display *display;
	SDL_Window *window;
	SDL_Renderer *renderer;

	SDL_Texture *tex[count];

	init(&display, &window, &renderer);
	loadTextures(renderer, tex, dir, count, &srcWidth, &srcHeight);

	for(int i = 0; i < instancesCount; i++)
	{
		instances[i].dest.x = atoi(argv[3+i*4]);
		instances[i].dest.y = atoi(argv[4+i*4]);
		instances[i].dest.w = atoi(argv[5+i*4]);
		instances[i].dest.h = atoi(argv[6+i*4]);
		instances[i].buffTex = SDL_CreateTexture(
			renderer, 
			SDL_PIXELFORMAT_ARGB8888, 
			SDL_TEXTUREACCESS_TARGET, 
			instances[i].dest.w, 
			instances[i].dest.h
		);
	}

	SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_Event event;
	int quit = 0;
	while(!quit)
	{
		int mx;

		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
				quit = 1;
			else if(event.type == SDL_MOUSEMOTION)
				mx = event.motion.x;
		}

		for(int u = 0; u < instancesCount; u++)
		{
			SDL_SetRenderTarget(renderer, instances[u].buffTex);
			SDL_RenderClear(renderer);

			for(int i = 0; i < count; i++)
			{
				SDL_Rect src = {
					.x = 0,
					.y = 0,
					.w = srcWidth,
					.h = srcHeight 
				};

				int x = 0-(mx/20)*i;

				for(int j = -1; j <= 1; j++)
				{
					SDL_Rect dest = {
						.x = x + j*instances[u].dest.w,
						.y = 0,
						.w = instances[u].dest.w,
						.h = instances[u].dest.h 
					};

					SDL_RenderCopy(renderer, tex[i], &src, &dest);
				}
			}
		
			SDL_SetRenderTarget(renderer, NULL);
			SDL_Rect src = {
				.x = 0,
				.y = 0,
				.w = instances[u].dest.w,
				.h = instances[u].dest.h 
			};
		
			SDL_RenderCopy(renderer, instances[u].buffTex, &src, &instances[u].dest);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(1000/60);
	}

	for(int i = 0; i < count; i++)
		SDL_DestroyTexture(tex[i]);
	for(int i = 0; i < instancesCount; i++)
		SDL_DestroyTexture(instances[i].buffTex);
	XCloseDisplay(display);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
