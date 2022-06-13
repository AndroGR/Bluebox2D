# Documentation of Bluebox2D
##### This document was updated last in 12/6/2022, 4:04AM.

### Contents:
#### 1. Introduction
#### 2. Getting Started
#### 3. Dependencies and runtime
#### 4. FAQ
#### 5. Windows Support
. 

.
## INTRODUCTION
This is the documentation of Bluebox2D. You are expected to read this as a guide for any questions you may have about it, any errors you may encounter or in general questions. For any developers, please check the ```dev/``` subdirectory to get started with contributing and developing for Bluebox2D.
Feel free to extend this documentation. As of now, the documentation is not finished and parts may be wrong or atleast not enough.
## GETTING STARTED
To get started with Bluebox2D, you must first install it in your operating system. Although the GitHub page does tell how to do so, we are going to dig further into these steps:
####** 1. Getting the source code:**
Bluebox2D is distributed through GitHub, where all of the development goes. Prebuilt binaries may be found in the Releases, while the master branch contains all the source code for Bluebox2D, including building files (CMake, Makefiles), runtime assets (PNGs and DLLs) and the actual C code/headers. That means that cloning (Downloading) the repository will include everything required to build and run Bluebox2D. Henceforth, we will first install it in the host machine. So first, we will clone or download the source tree:
####**For GNU/Linux, MacOS X and FreeBSD users:**
```
git clone --recursive --depth=1 https://github.com/AndroGR/Bluebox2D.git
```
You can also download it from the webpage directly, but we will focus on the terminal for now. If you are looking for a previous release, please see into the Releases.
####**2. Compile the source code:**
As mentioned before, the source code has to be compiled using either CMake or Makefiles. Don't worry if you are confused, both do their job in their way.  But first, let's go into the cloned directory:
```
cd Bluebox2D/
```
We are gonna use CMake here, for three reasons:
**1. It includes all the new features, unlike the Makefile.**
**2. It can be used with a GUI, unlike a Makefile.**
**3. It is very flexible, as in, you can remove parts of the program before compiling.**

You can ignore the second one since we are gonna be using the command line here. All you need to remember for now is that we are gonna use CMake, and now it's the right time to install the tools to build:
CMake requires a build system (Such as ninja), we are gonna be using Unix makefiles though, so let's install GNU Make along with the rest of the build tools:
**Arch Linux and derivatives:**
```
sudo pacman -Sy base-devel cmake gcc
```
**Ubuntu / Debian and derivatives:**
```
sudo apt-get -y update && sudo apt-get install -y cmake gcc make 
```
**Fedora Linux and RedHat-based distros:**
```
sudo dnf install cmake gcc make 
```
With the building tools ready, we will now need to compile the application. We will assume the **dependencies** are satisfied and Bluebox2D will be able to link to them. But in case it does not, please read the next section (3). 
First we have to generate the build files in a seperate directory:
```bash
mkdir -p build
```
```bash
cd build/ && cmake .. -G "Unix Makefiles"
```
And then, we need to use the generated build files to compile the application using Make:
```bash
make -j$(nproc --all)
```
Last, to finish off the job, we need to install all the runtime assets as well as the license to the installation path:
```
sudo make install -j4
```
This step only applies to non-Windows users. For Windows users, you will need a precompiled binary, or compile through a GNU/Linux machine. See the **Windows Support (5)** section for more.

Now that you have installed it, you may want to learn the controls around. The manpage is probably what you are looking for, which is available after installation. However, the basics are simple, press a key and click to place down the element.

## Dependencies and runtime
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
bluebox.bin version | grep -i "Video driver used"
```

It should return something like "x11", "wayland" or "windows".

**Audio:**

Play some sort of sound in your computer. It is not guaranteed that Bluebox2D will be able to use the sound though, as there have been issues in the past.

**Message:**

As mentioned above, just try to see if Bluebox2D already detects it.

**Rendering:**

Bluebox2D will always use OpenGL ES unless on Windows (Where it may use Direct3D). As both OpenGL and OpenGL ES are most likely available on both platforms already, you can just verify it to be sure (On GNU/Linux) using:

```sh
glxinfo | grep "OpenGL"
```

At least 1-2 values should be returned with the version of OpenGL.

## _TO BE CONTINUED_