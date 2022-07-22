
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


#include <init.h>

int WindowInitializer(SDL_Window** WindowPointer, SDL_Renderer **XRenderer, Uint32 flags) {
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    #ifndef _WIN32
    SDL_Surface* WindowIcon = IMG_Load("/usr/share/bluebox/logo.png");
    #else
    Surface* WindowIcon = IMG_Load("res/logo.png");
    #endif /* _WIN32 */
    *WindowPointer = SDL_CreateWindow("Bluebox2D (1280x720) | Beta Build", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, flags | SDL_WINDOW_RESIZABLE);
    if (!*WindowPointer) {
        LogToBluebox(7, "Could not create a window from SDL");
        SDL_Quit();
        return -127;
    }
    *XRenderer = SDL_CreateRenderer(*WindowPointer, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!*XRenderer) {
        InitFailureMsg(RendererFailure);
        LogToBluebox(7, "Cannot create a software renderer");
        SDL_Quit();
        // We return 0 because we don't want to receive the message twice (See main.c)
        return 0;
    }
    SDL_SetWindowIcon(*WindowPointer, WindowIcon);
    SDL_FreeSurface(WindowIcon);
    if (!WindowIcon) {
        LogToBluebox(5, "Failed to load the window icon, proceeding anyways: ");
    }
    return 0;
}
