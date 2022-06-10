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
# Compiling
Bluebox offers two ways of building its source code and installing it. One is through the Makefile (It is mostly used for debugging) and one using the CMake build system, which will probably suit you more as all new features are added there. Assuming you want to compile using CMake, enter these commands in a terminal:

Download the source code:
```bash
git clone https://github.com/androgr/Bluebox2D.git ~/Bluebox2D && cd ~/Bluebox2D/
```
Create the required directories:
```bash
mkdir build && cd build
```
Create the build files to compile the application:
```bash
cmake ..
```
FInally, compile the source:
```bash
make -j$(nproc --all) && sudo make install
```
These steps should work on all OSes that the dependencies are installed. If not, you may want to use the Makefile instead, which still depends on GCC but can easily be changed to CLang. To use the Makefile (Assuming you do have GCC installed), follow the first step and then type the next command:
```bash
make -j$(nproc --all) && sudo make install
```
# License
Bluebox2D is licensed under the GNU General Public License, version 3. Clear licensing information can be found in `LICENSE`, `/usr/share/bluebox/LICENSE` (If you installed Bluebox2D already), or by executing Bluebox2D with the argument `license`. The first two show the entire GNU GPL license.
