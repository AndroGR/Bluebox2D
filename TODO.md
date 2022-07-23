This is a list containing everything related to future releases when it comes to features and bug fixes. Update this list if 
you encounter another problem, have a new feature to report or a bug was fixed but the list wasn't updated.
# Known Bugs:
- Buffers switching asynchronously (Fixed)
- When resizing, the particles stay in the same position (Fixed)
- Pressing S on some platforms is the same as pressing Ctrl+S (Not fixed)
- Wayland / VSync sessions present screen flickering (Fixed)
- Ubuntu packages do not work with Debian (Not fixed, abandoned)
# Planned changes for the next release:
- The window will be resizable (Done)
- Texture updates (In queue)
- Flatpak packages (In queue)
- Modules support  (In queue, currently developing.)
- Title changing on window resize (Done)
- Use the left mouse to draw many textures at once instead of the right (In queue, under development)
- Check for updates on startup (Questionable)
- Deprecate native packages (.deb, pacman, ..)(Questionable)
- Upload in the AUR (In queue)
- A user interface (Not in queue)
- Comment the code more (Currently developing)
# Next release plan
The next release is scheduled for August, unless something takes more time or everything is finished much sooner. That will be the first beta release too,
v0.5-beta.

There is also RustBox2D which I am developing for fun, [click here](https://github.com/AndroGR/RustBox2D/) for more information about it. It is a rewrite of this
project but using Rust, OpenGL and glutin. You can try it out but it's far from ready and it won't be ready anytime soon.
