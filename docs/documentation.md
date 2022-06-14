# Documentation of Bluebox2D
##### This document was updated last in 13/6/2022, 8:50PM.

### Contents:
#### 1. Introduction [(Go To)](#1-introduction)
#### 2. Getting Started [(Go To)](#2-getting-started)
#### 3. Dependencies and runtime [(Go To)](#3-dependencies-and-runtime)
#### 4. FAQ [(Go To)](#4-faq)
#### 5. Windows Support [(Go To)](#5-windows-support)
#### 6. Developer Documentation [(Go To)](#6-developer-documentation)
. 

.
## (1) INTRODUCTION
This is the documentation of Bluebox2D. You are expected to read this as a guide for any questions you may have about it, any errors you may encounter or in general questions. For any developers, please check the ```dev/``` subdirectory to get started with contributing and developing for Bluebox2D.
Feel free to extend this documentation. As of now, the documentation is not finished and parts may be wrong or atleast not enough.

## (2) GETTING STARTED
To get started with Bluebox2D, you must first install it in your operating system. Although the GitHub page does tell how to do so, we are going to dig further into these steps:

#### ** 1. Getting the source code:**

Bluebox2D is distributed through GitHub, where all of the development goes. Prebuilt binaries may be found in the Releases, while the master branch contains all the source code for Bluebox2D, including building files (CMake, Makefiles), runtime assets (PNGs and DLLs) and the actual C code/headers. That means that cloning (Downloading) the repository will include everything required to build and run Bluebox2D. Henceforth, we will first install it in the host machine. So first, we will clone or download the source tree:

####**For GNU/Linux, MacOS X and FreeBSD users:**
```
$ git clone --recursive --depth=1 https://github.com/AndroGR/Bluebox2D.git
```
You can also download it from the webpage directly, but we will focus on the terminal for now. If you are looking for a previous release, please see into the Releases.
####**2. Compile the source code:**
As mentioned before, the source code has to be compiled using either CMake or Makefiles. Don't worry if you are confused, both do their job in their way.  But first, let's go into the cloned directory:
```
$ cd Bluebox2D/
```
We are gonna use CMake here, for three reasons:\
**1. It includes all the new features, unlike the Makefile.**\
**2. It can be used with a GUI, unlike a Makefile.**\
**3. It is very flexible, as in, you can remove parts of the program before compiling.**

You can ignore the second one since we are gonna be using the command line here. All you need to remember for now is that we are gonna use CMake, and now it's the right time to install the tools to build:

CMake requires a build system (Such as ninja), we are gonna be using Unix makefiles though, so let's install GNU Make along with the rest of the build tools:
**Arch Linux and derivatives:**
```
$ sudo pacman -Sy base-devel cmake gcc
```
**Ubuntu / Debian and derivatives:**
```
$ sudo apt-get -y update && sudo apt-get install -y cmake gcc make 
```
**Fedora Linux and RedHat-based distros:**
```
$ sudo dnf install cmake gcc make 
```
With the building tools ready, we will now need to compile the application. We will assume the **dependencies** are satisfied and Bluebox2D will be able to link to them. But in case it does not, please read the next section (3). 
First we have to generate the build files in a seperate directory:
```bash
$ mkdir -p build
```
```bash
$ cd build/ && cmake .. -G "Unix Makefiles"
```
And then, we need to use the generated build files to compile the application using Make:
```bash
$ make -j$(nproc --all)
```
Last, to finish off the job, we need to install all the runtime assets as well as the license to the installation path:
```
$ sudo make install -j4
```
This step only applies to non-Windows users. For Windows users, you will need a precompiled binary, or compile through a GNU/Linux machine. See the **Windows Support (5)** section for more.

Now that you have installed it, you may want to learn the controls around. The manpage is probably what you are looking for, which is available after installation. However, the basics are simple, press a key and click to place down the element.

## (3) Dependencies and runtime
Before we continue, let's explain something: **Dependencies and runtime does not only mean libraries !**. It means everything an application needs to function as expected. Bluebox2D provides a satisfactory amount of error handling, but error handling on its own is not enough, and hence sparing these 3-4 MBs of storage is pretty much needed.

For the sake of simplicity, we are going to break down the dependencies into 3 sections:
- 1. Libraries
- 2. Assets
- 3. Subsystems
, ranked based on their importance (That doesn't mean that not having some subsystems ready isn't serious, it means that the app MAY work without them).

So let's start with each of them:

#### **1. Libraries**
Bluebox2D depends on the next libraries (Not counting the dependencies of the said libraries):
- ```SDL2```
- ```SDL2_TTF```
- ```SDL2_Image```

**If music is enabled**:

- ```SDL2_Mixer```

Just so I don't waste your time, here is how to install them in each GNU/Linux distribution (For *BSD and MacOS X users, please compile them from source):

**Arch Linux and derivatives:**
```sh
sudo pacman -Sy sdl2 sdl2_ttf sdl2_mixer sdl2_image
```
**Ubuntu / Debian and derivatives:**
```sh
sudo apt-get update -y && sudo apt-get install libsdl2-image-2.0 libsdl2-image-dev libsdl2-2.0 libsdl2-dev libsdl2-ttf-2.0 libsdl2-ttf-dev libsdl2-mixer-2.0 libsdl2-mixer-dev
```
**Fedora and RedHat-based distributions:**
```sh
sudo dnf install SDL2 SDL2-devel SDL2_image-devel SDL2_image SDL2_ttf-devel SDL2_ttf
```
#### **2. Assets:**
Bluebox2D needs to load assets at runtime to display to the screen or configure itself. Most commonly, these assets are images that Bluebox2D transforms into textures and displays to the user. For example, when you place down an ocean of water, you basically load an image, send it to your graphics card and render it to a window. 
When installing Bluebox2D, you basically move all of the assets into a location in the filesystem Bluebox2D expects them to be (Usually ```/usr/share/bluebox```). So if you installed Bluebox2D, you can go safely into the next section.

#### **3. Subsystems:**
While Bluebox2D does take care of the first two, this one is purely up to the user to handle. A subsystem is basically a part of the system responsible for an action. Eg. On GNU/Linux, X11 is the video subsystem, as it has complete control over your screen, your windows and the input. Wayland also exists but let's not take that road for now.
Here all all the subsystems, which software implements them and why are they needed:

| Subsystem | Software implementing it | Why |
| --------- | ------------------------ | --- |
|   Video   | X11 or Wayland (GNU/Linux), Windows Video Subsystem (Windows), and Quartz(MacOS)|Create windows and talk to the display server|
|   Audio   | PulseAudio, Pipewire, Jack or Alsa (GNU/Linux), Windows Sound Subsystem (Windows)|Only required for music and sound|
|  Message  | The desktop enviroment or X11 directly (GNU/Linux), Win32 API (Windows), Cocoa API(MacOS)|Show window dialogs for information and errors|
| Rendering | Mesa - OpenGL (GNU/Linux), Graphics driver or Direct3D (Windows, GNU/Linux, MacOS X), Metal(MacOS X)| Accelerate rendering tasks with the GPU|

Most of these are probably already ready to go. What is an issue on (especially minimal) GNU/Linux distros is the "Message" one. There is nothing you can do directly about it, it will either be detected or not. SDL does not give an exact description on why there is no message subsystem detected, and hence I may give it a try to track it down.

In case you want to verify that you are good to go, here's what you can do (Do not worry if something fails, SDL will take care of falling back to an alternative or tell you what went wrong):

**Video:**

If you read this in a web browser with a GUI, then nothing to worry about.
But in case you still want to verify it, run in a terminal (After installation):

```sh
$ bluebox.bin version | grep -i "Video driver used"
```

It should return something like "x11", "wayland" or "windows".

**Audio:**

Play some sort of sound in your computer. It is not guaranteed that Bluebox2D will be able to use the sound though, as there have been issues in the past.

**Message:**

As mentioned above, just try to see if Bluebox2D already detects it.

**Rendering:**

Bluebox2D will always use OpenGL ES unless on Windows (Where it may use Direct3D). As both OpenGL and OpenGL ES are most likely available on both platforms already, you can just verify it to be sure (On GNU/Linux) using:

```sh
$ glxinfo | grep "OpenGL"
```

At least 1-2 values should be returned with the version of OpenGL.

## (4) FAQ
Here are some questions you may have about Bluebox2D in general. You may want to read this for the next releases.

### **1. When was Bluebox2D created?**
- Bluebox was a concept since August 2021, with similar but not the same goals. The initial idea is pretty much lost but even if it existed, it wouldn't be much better.

### **2. What platforms does Bluebox2D run on?**
- Bluebox has support for most platforms in its source code. Windows support was the last officially added in v0.2 (April 2022). The officially supported platforms include:

| Platform  | Supported | Officially (In Releases) |
| --------- | --------- | ------------------------ |
|  Windows  |    Yes    | Yes                      |
|   *BSD    |    Yes    | Since current release    |
|  MacOS X  |    Yes    | No                       |
| GNU/Linux |    Yes    | Yes                      |
|  Android  |     No    | No                       |
|    iOS    |     No    | No                       |
|  ReactOS  |    Yes    | No                       |
| KolibriOS |     No    | No                       |
|  Termux   | Through port | Through port          |
<h6> Please extend this list, if possible. </h6>

### **3. What will the next release include?**
<h5> Hint: Current release is v0.3. </h5>
- The next release is to become a large one, since lots of new features are going to be added to the game. Not to confirm something, but here are some things you may want to expect:

**An API:**

Bluebox2D has started growing, and although still small, it will sooner or later be ported to other platforms, or have some sort of plugin functionality. All of these need an API to work. The initial API is going to be purely to debug the code from different systems, but an API is an API, and an API needs to grow.

**Moving to the home directory:**

Eh, let's be honest. Who wants `/usr/share/bluebox`? It defeats the whole point of the game. Moving to the home directory will be a better idea for cleaning up too. It may be optional, it may be not, who knows?

**New packages:**

Creating a package for all distributions is hard and time-consuming. Technologies like AppImages will suit the game perfectly and will allow for cross-distro development.

Flatpak fans, I don't think there's a point into distributing a flatpak with such a small application. Especially if the user does not even use flatpaks in the first place. In all cases, native packages will remain.

**Layered rendering:**

A 3-layer system for placing down elements is kind of needed.

I did try to implement this into previous versions but failed. In any case, it would not make sense to a human being having a house above a tree, right?

Layers will be explained in the Developer Documentation.

**Updated textures:**

The old pixelart isn't exactly the best thing in the world. Why not take the chance and have a resource update? We may do this in v0.5 (Which will be a larger release anyways).

One of the core things to note here is the resolution. 32x32 is a bit too small, and without proper adjustments, it looks ugly and boring. Upgrading to atleast 64x64 (256x256 is probably the final one) will not change much in performance and still make the game much more fancy.

**Sound effects:**

I don't think I need to say anything. Just a spoiler alert, forget about SDL2_Mixer being optional. Live with it now, hope there's a package in your repos atleast.

### **4. How to contribute?**
See CONTRIBUTE.md (At the beginning of the source tree), or the Bluebox Developer Documentation.

### **5. What are the hardware requirements for Bluebox2D:**
I cannot say with certainty, but you can definitely run it on your machine. In the most extreme test it has been on, it ran pretty well too. Here is an approximate (Note that software may not be compatible):

- At least 256MBs of RAM (Bluebox2D takes about 33MBs)
- A single-core CPU
- At least 960x480 screen resolution (The window may fill the entire screen, about 1280x720 is the recommended resolution)
- Any GPU, if hardware-accelerated rendering is desired.

Again, that's just an estimate. You can still run it on virtually every platform tho.

### **6. What is the license of Bluebox2D?**

Bluebox2D is licensed under the GNU General Public License. In both the GitHub repository and `/usr/share/bluebox/`, a copy of the license can be found. You can also run:

```bash
$ bluebox.bin license
```

To get a notice in the command line.

## (5) Windows Support
Bluebox2D does offer support for Windows both in the source code and when a new release happens. The Windows version however is not available for compilation through Windows itself, but may be added in the future. To compile a Windows executable, and get it ready for distribution, this is what you need to do (From a GNU/Linux running machine):

- **1. Download the source code:**

Just like before, you need to download the source code to compile it. If you want to work from a terminal, the command is the same as before:

```sh
git clone --depth=1 https://github.com/androgr/Bluebox2D.git
```
Else, download it as a ZIP from either the Releases or directly through the "Download ZIP" button from the Code menu.

- **2. Download the dependencies:**

To save your time, we will not have to download all the libraries, DLLs and others, as the source tree provides them all. Instead, we will only need a cross compiler, which in this case is going to be MinGW. Here's how to install MinGW according to your distribution:

**Arch Linux:**

```sh
sudo pacman -Sy mingw-w64-gcc mingw-w64-crt mingw-w64-headers mingw-w64-winpthreads mingw-w64-binutils
```

**Ubuntu, Debian and derivatives:**

```sh
sudo apt-get update -y && sudo apt-get install binutils-mingw-w64 gcc-mingw-w64
```

**Fedora Linux and other RedHat-based distributions:**

```sh
sudo dnf install mingw-w64-tools mingw-binutils-generic
```

The rest is pretty much 1-2 commands. First we need to compile the executable with the Makefile, like we would do with a normal Bluebox2D executable:

```
make windows -j$(nproc --all)
```

The Makefile will inform you on the new location of the executable, and will also move everything from the `dll/` folder into the same folder. Usually, this is how the archives in the releases are built, unless anything changed.
Last, you can create an archive of the folder if you wish to distribute the compiled binaries (Please see LICENSE first), or just execute it through Wine to debug it.

## (6) Developer Documentation

Like any other open source project, someone may want to become a developer for Bluebox2D.

Reading the source code for any project is not a simple task, and different ideas / styles of coding definitely exist. For this reason, the **Bluebox Developer Documentation** exists, which is a set of different documentation pages about how to contribute, write code, optimize and compile Bluebox2D. 

The Bluebox Developer Docs can be found under the **`dev/`** directory (Under this one.)

[Go back to the beginning](#documentation-of-bluebox2d)
