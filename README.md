# Bluebox2D
**NOTE: This repository is new, the old repository no longer exists due to some issues.**\
Bluebox2D is a free and open source sandbox game, designed to be very lightweight and easy to use. It is written in C99 and works on Windows, MacOS*, GNU/Linux, FreeBSD and other Unix-like enviroments.
# Dependencies
Bluebox requires some libraries at runtime to function. Those are needed to create pretty much everything you see on the screen. They are:
- [SDL2](https://libsdl.org) (Required)
- [SDL2_TTF](https://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf.html) (Also required)
- [SDL2_Image](https://www.libsdl.org/projects/SDL_image/) (Also required)
- [SDL2_Mixer](https://www.libsdl.org/projects/SDL_mixer/) (Not required, but future versions may require it)**
- OpenGL, OpenGL ES or Direct3D support (Contact your OS maintainer for more information).\
### Installing the dependencies:
Fedora and RedHat-based distributions:
```bash
sudo dnf install SDL2 SDL2-devel SDL2_ttf-devel SDL2_ttf SDL2_image SDL2_image-dev
```
Debian, Ubuntu and other distributions:
```bash
sudo apt install libsdl2 libsdl2-dev libsdl2-ttf libsdl2-ttf-dev libsdl2-image libsdl2-image-dev
```
Arch, Manjaro, EndeavourOS and other distributions:
```
sudo pacman -Sy sdl2 sdl2-image sdl2-ttf
```
For other distributions, compile the libraries specified above manually.
### Build dependencies (Required to compile Bluebox2D):
In order to compile Bluebox2D, you will need to have a compiler, CMake and GNU Make or Ninja. You can install them with these commands:\
**Fedora Linux and other RedHat-based distributions:**
```bash
sudo dnf install cmake make gcc
```
**Debian, Ubuntu and others:**
```bash
sudo apt install cmake make gcc
```
**Arch Linux, Manjaro, EndeavourOS and others:**
```bash
sudo pacman -Sy cmake make gcc 
```
