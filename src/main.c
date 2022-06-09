/*
Copyright (C) 2022 Aggelos Tselios
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/* On Windows, we need to define this to tell SDL that we don't need SDL_main.
 */
#include <def.h>
#include <stdio.h>
#define SDL_MAIN_HANDLED

#define BLUEBOX
#include <Bluebox.h>
#include <GL/gl.h>
#include <event.h>
#include <init.h>
#include <log.h>
#include <message.h>
#include <version.h>

#ifndef VERSION_INFO
#error Version information is missing, please recompile with ''
#endif /* VERSION_INFO */

static void usage(const char *launch) {
  printf("\nQuick Usage: %s [Flags | Options]", launch);
  printf("\nFlags: ");
  printf("\n'help'    - Display this text and then exit.");
  printf("\n'version' - See version information about the application.");
  printf("\nFor more information see \'man bluebox\' (1).\n");
  return;
}

const char *__license__ =
    "Copyright (C) 2022 Aggelos Tselios\n"

    "\nThis program is free software; you can redistribute it and/or modify it "
    "under the terms of the GNU General Public License as published by the "
    "Free Software Foundation; either version 3 of the License, or (at your "
    "option) any later version.\n"
    "This program is distributed in the hope that it will be useful, but "
    "WITHOUT ANY WARRANTY; without even the implied warranty of "
    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General "
    "Public License for more details."

    "\nYou should have received a copy of the GNU General Public License along "
    "with this program; if not, see <https://www.gnu.org/licenses>.\n";

static inline void license(void) {
  printf("\nBluebox2D is licensed under the GNU GPL v3 license.\n");
  printf("\n%s", __license__);
  printf("\n\nDetails can be found in /usr/share/bluebox/LICENSE\n");
}

/* The prefix Bluebox uses on the console. */
static const char *bluebox_prefix = "\x1B[92m[ Bluebox ]\x1B[97m";

int main(const int argc, const char *argv[]) {
  Uint32 WindowFlags =
      SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
  SDL_SetMainReady();
  if (!argv[1] || argc < 2) {
#ifdef __LINUX__
    if (strcmp(getenv("XDG_SESSION_TYPE"), "wayland") == 0) {
      /* Bluebox flickers when we use it under Wayland. For that reason, we can
       * "force" SDL2 to use X11, even when Wayland is present.*/
      char *is_wayland_forced = getenv("BX_USE_WAYLAND");
      if (!is_wayland_forced) {
        WarningMessage(
            "Bluebox has detected that you are running under Wayland. To make sure that the game runs smoothly, \n\
XWayland is going to be used. This is available only after v0.2. \nYou \
can set the enviroment variable BX_USE_WAYLAND to \"true\" to use Wayland instead.",
            NULL);
        setenv("SDL_VIDEODRIVER", "x11", true);
      } else if (strcmp(is_wayland_forced, "true") == 0) {
        LogToBluebox(1, "Wayland is being forced through BX_USE_WAYLAND");
        setenv("SDL_VIDEODRIVER", "wayland", 1);
      }
    }
#endif /* __LINUX__ */

#ifdef __LINUX__ // Some performance optimizations for Linux
    SDL_SetHint(SDL_HINT_XINPUT_ENABLED, "0");
    SDL_SetHint(SDL_HINT_VIDEO_X11_XRANDR, "1");
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_PING, "0");
#elif defined(_WIN32)
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "direct3d");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
#else
    /* To maximize compatibility, we will use OpenGL ES 2. */
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");
#endif /* __LINUX__ */
    SDL_SetHint(SDL_HINT_VIDEO_ALLOW_SCREENSAVER, "1");
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");

    bool KeepWindowOpen = (bool)true;
    SDL_Event MainEvent;
    SDL_Window *XWindow = NULL;
    SDL_Renderer *XRender = NULL;
    TTF_Init();

    if (WindowInitializer(&XWindow, &XRender, WindowFlags) != 0) {
      InitFailureMsg(WindowFailure);
      abort();
    }
    void *ctx = SDL_GL_CreateContext(XWindow);
    assert(ctx != NULL);
    SDL_GL_MakeCurrent(XWindow, ctx);
#ifdef __BLUEBOX_ENABLE_MUSIC
    Mix_Music *MusicID = StartMusic(NULL);
#endif /* __BLUEBOX_ENABLE_MUSIC */
#ifdef HAVE__DEBUG
    SDL_RendererInfo RendererInfo;
    SDL_GetRendererInfo(XRender, &RendererInfo);
    printf("%s Renderer Info:\nDriver: %s\nFlags: %d\nMax Texture Size: %dx%d "
           "(%d)\n",
           BLUEBOX_CONSOLE_PREFIX, RendererInfo.name, RendererInfo.flags,
           RendererInfo.max_texture_width, RendererInfo.max_texture_height,
           (RendererInfo.max_texture_height * RendererInfo.max_texture_width));
#endif /* HAVE__DEBUG */
    printf("\n%s OpenGL Version: %s", bluebox_prefix, glGetString(GL_VERSION));
    printf("\n%s Renderer Info: %s", bluebox_prefix, glGetString(GL_RENDERER));
    do {
      SDL_RenderClear(XRender);
      SDL_RenderPresent(XRender);
      while (PollEvents(&MainEvent, &KeepWindowOpen, XRender, XWindow) == 0) {
        LogToBluebox(1, "No errors were detected at runtime");
        return 0;
      }
    } while (KeepWindowOpen == true);
  } else {
    if (strcmp(argv[1], "version") == 0) {
      SDL_version linked_version;
      SDL_version compiled_version;
      SDL_VERSION(&compiled_version);
      SDL_GetVersion(&linked_version);
      printf("\n%s", VERSION_INFO); // Defined in version.h
      printf("\nSDL Information: \nCompiled with version: %u.%u.%u.\nLinked "
             "against: %u.%u.%u.\nVideo driver used: %s.\n",
             compiled_version.major, compiled_version.minor,
             compiled_version.patch, linked_version.major, linked_version.minor,
             linked_version.patch, SDL_GetVideoDriver(0));
      return 0;
    } else if (strcmp(argv[1], "help") == 0) {
      usage(argv[0]);

    } else {
      if (strcmp(argv[1], "license") == 0) {
        license();
      } else {
        fprintf(stderr, "%s Invalid flag: %s.\n", bluebox_prefix, argv[1]);
        return -1;
      }
    }
  }
}
