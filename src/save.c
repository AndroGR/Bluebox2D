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

#include "def.h"
#include <Bluebox.h>
#include <log.h>
#include <save.h>
#include <message.h>

FORCE_INLINE inline static void save_texture(const char* file_name, SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Texture* target = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, texture);
    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 28, 0, 0, 0, 0);
    if (!surface) {
        LogToBluebox(5, "Error creating renderer surface");
    }
    if (SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch) != 0) {
        LogToBluebox(5, "Error reading the renderer");
    }
    
    #ifdef HAVE__DEBUG
    printf("%s %s %s.", BLUEBOX_CONSOLE_PREFIX, "Saving the game status at ", file_name);
    #endif /* HAVE__DEBUG */
    ASSERT(IMG_SavePNG(surface, file_name) == 0);
    SDL_FreeSurface(surface);
    SDL_SetRenderTarget(renderer, target);
}

static __DEPRECATED__ void RemoveSave(const char* path) {
    if (remove(path) != 0) {
        char _tmp[256];
        snprintf(_tmp, 256, "Couldn't delete file %s: ", path);
        LogToBluebox(1, _tmp);
        return;
    } else {
        char __tmp[256];
        sprintf(__tmp, "Deleted save %s", path);
        LogToBluebox(1, __tmp);
    }
}

int SaveProgress(const char* saveloc, bool autosave, SDL_Renderer** Renderer, SDL_Window** Window) {
    // Autosave not yet required.
    if (autosave) return -127;
    int w, h;
    SDL_GetRendererOutputSize(*Renderer, &w, &h);
    Surface* Screen = SDL_CreateRGBSurface(0, w, h, 32, 0,0,0,0);
    if (!Screen) {
        LogToBluebox(5, "Failed to create the saving surface");
        return -127;
    }
    if (SDL_RenderReadPixels(*Renderer, NULL, SDL_PIXELFORMAT_RGBA8888, Screen->pixels, Screen->pitch) != 0) {
        LogToBluebox(5, "Error reading the renderer");
        return -1;
    }
    if (IMG_SavePNG(Screen, saveloc) < 0) {
        char str[256];
        sprintf(str, "Could not save the renderer output: %s.", IMG_GetError());
        ErrorMessage(str, Window);
        return -127;
    } else {
        LogToBluebox(1, "Saved succesfully.");
    }
    SDL_FreeSurface(Screen);
    return 0;
}
/* Work in progress */
__DEPRECATED__ static void* LoadSave(SDL_Renderer** Renderer, const char* path) {
    if (!path) return NULL;
    SDL_Texture* tex = IMG_LoadTexture(*Renderer, path);
    ASSERT(tex);
    return (void*) 1;
}