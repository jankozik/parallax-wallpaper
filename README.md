<div align="center">

# Parallax WallPaper

This allows you to create multi-layered parallax wallpapers.<br />
Each layer moves with Your mouse cursor, creating this beautiful effect.

[Installation](#installation) •
[Configuration](#configuration) •
[Creating Wallpapers](#creating-wallpapers)

https://user-images.githubusercontent.com/38699473/220888934-09788a6b-873c-469b-b147-b345e8a8949a.mp4

</div>

## Installation

<details>
  <summary>Linux</summary>
  
  #### Installation steps
  
  - Install `SDL2` using Your package manager
  - If You are using `Wayland`, You also must install `XWayland`
  - Download `.tar.gz` package from [releases](https://github.com/jankozik/parallax-wallpaper/releases/latest)
  - Extract the content to `/`:
  ```shell
  sudo tar -o -xvf [archive name].tar.gz --directory /
  ```
  - Test Layered WallPaper by running `lwp`
  - Setting `reload_rootwindow=1` in config file may be necessary on some distributions for Layered WallPaper to work properly (see [configuration](#configuration))
  - To make Layered WallPaper run on startup, add `lwp &` command to Your desktop enviroment `.rc` file
  
  #### Build from source instead
  - Install `SDL2` using Your package manager. On some distributions `SDL2` doesn't contain development files, so it may be also necessary to install development version of `SDL2`
  - If You are using `Wayland`, You also must install `XWayland`
  - Install `CMake`
  - Clone the repository and prepare a `build` directory:

  ```shell
  git clone https://github.com/jankozik/parallax-wallpaper
  cd lwp
  mkdir build
  cd build
  ```
  - Compile the project and generate a `.tar.gz` package
  ```shell
  cmake ../
  cmake --build .
  cpack
  ```
  - Extract `.tar.gz` package
  ```shell
  sudo tar -o -xvf [archive name].tar.gz --directory /
  ```
  - Test Layered WallPaper by running `lwp`
  - Setting `reload_rootwindow=1` in config file may be necessary on some distributions for Layered WallPaper to work properly (see [configuration](#configuration))
  - To make Layered WallPaper run on startup, add `lwp &` command to Your desktop enviroment `.rc` file
  
</details>

<details>
  <summary>macOS</summary>
  
  #### Installation steps
  - Download and run the installer from [releases](https://github.com/jankozik/parallax-wallpaper/releases/latest)
  - Drag and drop Layered_WallPaper into Applications
  - To make Layered WallPaper run on startup, run Toggle_Autorun.command
    - To stop running Layered WallPaper on startup, run it again
  
  #### Build from source instead
  - Install `SDL2` (homebrew: `brew install sdl2`)
  - To build this project, You need to install `cmake` (homebrew: `brew install cmake`)
  - Clone the repository:
    ```zsh
    git clone https://github.com/jankozik/parallax-wallpaper
    cd lwp
    
    ```
  - Compile and generate installer
    ```zsh
    mkdir build
    cd build
    cmake ../
    cmake --build .
    cpack -G DragNDrop
    ```
  - DMG installer should appear, open it and drag Layered_WallPaper into Applications
  - To make Layered WallPaper run on startup, run Toggle_Autorun.command
    - To stop running Layered WallPaper on startup, run it again
    
</details>

<details>
  <summary>Windows</summary>
  
  #### Installation steps
  - Download and run the installer from [releases](https://github.com/jankozik/parallax-wallpaper/releases/latest)
  - Layered WallPaper should run immediately after the installation
  
  #### Build from source instead
  - Layered WallPaper is built using [cmake](https://cmake.org/), so You must install it.
  - This project supports `MinGW` and `MSVC` compilers. Using different one could lead to unpredicted behavior. If You want to use `MSVC`, it should be installed with Visual Studio.
  - Download `SDL2` and `SDL2-devel` package for Your compiler from [SDL2 releases](https://github.com/libsdl-org/SDL/releases/latest) and extract them somewhere.
  - You also must install [NSIS](https://nsis.sourceforge.io/Download). It's required to build the installer, which is needed to correctly set the registry keys, that will make Layered WallPaper run on OS startup etc.
  - Clone the repository and create `build` directory
  ```shell
  git clone https://github.com/jszczerbinsky/lwp
  cd lwp
  mkdir -p build
  cd build
  ```
  - Type the following commands, replace square brackets elements with paths to extracted `SDL2` packages, that You've downloaded:


  For `MSVC`:
  ```shell
  cmake -G "Visual Studio 17" -DSDL2_DIR=[PATH TO SDL2-MSVC-DEVEL DIRECTORY]\cmake -DSDL2_RUNTIME_DIR=[PATH TO SDL2 RUNTIME DIRECTORY]  ../
  cmake --build . --config Release
  cpack
  ```
  For `MinGW`:
  ```shell
  cmake -G "MinGW Makefiles" -DSDL2_DIR=[PATH TO SDL2-MINGW-DEVEL DIRECTORY]\cmake -DSDL2_RUNTIME_DIR=[PATH TO SDL2 RUNTIME DIRECTORY] -DCMAKE_BUILD_TYPE=Release  ../
  cmake --build .
  cpack
  ```
  - The installer should appear in `build` directory, that You've created earlier. After completing the installation Layered WallPaper should run immediately.
  
</details>

## Configuration

#### Create a configuration file
<details>
  <summary>Linux</summary>
  
  - Copy default config file to `.config/lwp/lwp.cfg`:
  ```shell
  mkdir ~/.config/lwp
  cp /etc/lwp.cfg ~/.config/lwp/lwp.cfg
  ```
  
</details>
<details>
  <summary>macOS</summary>

  - Copy default config file to `~/.config/lwp/lwp.cfg`:
    ```zsh
    mkdir -p ~/.config/lwp
    cp /opt/lwp/lwp.cfg ~/.config/lwp/
    ```
</details>
<details>
  <summary>Windows</summary>
  
  - Press <kbd>⊞ Win</kbd> + <kbd>R</kbd>
  - Type `%appdata%` and press `Ok`
  - Create new directory and name it `lwp`
  - Copy file `C:\Program Files\lwp\defaultWin.cfg` to directory created in the previous step and rename it to `lwp.cfg`
  - Open `lwp.cfg` in notepad
  
</details>

#### Using config file

- Do not put spaces between `=` and values
- Do not leave trailing spaces
- Comments start with `#`
- Do not put strings in quotation marks

#### Available options:

|  Type  |      Name    | Description |
| ------ | ------------ | ----------- |
| int    | reload_rootwindow | Set this to 1 if You are using a compositor (linux only) |
| float  | smooth       | Smooth movement multipler |
| int    | monitors     | Monitors count |
| int    | monitor[n]_x | Position of nth monitor in X axis |
| int    | monitor[n]_y | Position of nth monitor in Y axis |
| int    | monitor[n]_w | Width of nth monitor |
| int    | monitor[n]_h | Height of nth monitor |
| string | monitor[n]_wallpaper   | Absolute path to the wallpaper directory |
| int    | monitor[n]_wallpaper_x | Position of the wallpaper relative to the monitor |
| int    | monitor[n]_wallpaper_y | Position of the wallpaper relative to the monitor |
| int    | monitor[n]_wallpaper_w | Wallpaper resolution |
| int    | monitor[n]_wallpaper_h | Wallpaper resolution |
| int    | target_fps     | How many times per second should the wallpaper render (imprecise, hence "target") |

## Creating Wallpapers

Parallax wallpapers are not popular. Because of this if You want some cool parallax wallpaper, You have to either find a parallax game background on the internet and use it as a wallpaper or cut some real wallpaper into layers using Gimp or Photoshop.

#### How to create a wallpaper for Layered WallPaper
- Create a directory for Your wallpaper
- Save each layer to this directory as `.bmp` file and name them `1.bmp`, `2.bmp` ... (`1.bmp` is bottom most layer)
- Create a wallpaper config file and name it `wallpaper.cfg` (You can make a copy from `C:\Program Files\lwp\wallpapers\default-fullhd\wallpaper.cfg`)

#### Example:

File structure:
```
C:
 └  MyCoolWallpaperDirectory
         └  wallpaper.cfg
         └  1.bmp
         └  2.bmp
         └  3.bmp
```

#### Config file:

|  Type  |      Name    | Description |
| ------ | ------------ | ----------- |
| int    | count        | Wallpaper layers count |
| float  | movement_x    | Mouse sensitivity in X axis |
| float  | movement_y    | Mouse sensitivity in Y axis |
| float  | movement[n]_x | Mouse sensitivity in X axis for nth layer (optional)|
| float  | movement[n]_y | Mouse sensitivity in Y axis for nth layer (optional)|
| int    | repeat_x     | Repeat the wallpaper in X axis |
| int    | repeat_y     | Repeat the wallpaper in Y axis |
