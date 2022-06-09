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
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <log.h>
#include <save.h>
#include <message.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <render.h>

#define MAX_PATH 1024

FORCE_INLINE inline static bool save_directory_exists(void) {
    struct stat st;
    char dir[MAX_PATH];
    snprintf(dir, sizeof(dir), "%s/.local/share/bluebox/", getenv("HOME"));
    return (stat(dir, &st) == 0);
}

int RemoveSave() {
    char save_location[MAX_PATH];
    snprintf(save_location, sizeof(save_location), "%s/.local/share/bluebox/save.png", getenv("HOME"));
    if (remove(save_location) == 0) {
        LogToBluebox(1, "Save removed");
    } else {
        char err[MAX_PATH + 128];
        snprintf(err, sizeof(err), "Failed to remove %s: %s", save_location, strerror(errno));
        LogToBluebox(1, err);
        return 2;
    }
    char err[MAX_PATH + 128];
    snprintf(err, sizeof(err), "Deleted file %s (Saved from Bluebox2D)", save_location);
    LogToBluebox(1, err);
    return 0;
}

int SaveProgress(bool autosave, SDL_Renderer** Renderer, SDL_Window** Window) {
    #ifdef __BLUEBOX_SAVING_ENABLED
    char dirpath[1024];
    if (!save_directory_exists()) {
        char dirpath[1024];
        snprintf(dirpath, sizeof(dirpath), "%s/.local/share/bluebox/", getenv("HOME"));
        printf("%s Creating directory: %s", BLUEBOX_CONSOLE_PREFIX, dirpath);
        mkdir(dirpath, 0755);
    }
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
    char location[1024];
    snprintf(location, sizeof(location), "%s/.local/share/bluebox/save.png", getenv("HOME"));
    if (IMG_SavePNG(Screen, location) < 0) {
        char str[256];
        sprintf(str, "Could not save the renderer output: %s.", IMG_GetError());
        ErrorMessage(str, Window);
        return -127;
    } else {
        char str[MAX_PATH + 128];
        snprintf(str, sizeof(str), "PNG Save at %s.", location);
    }
    SDL_FreeSurface(Screen);
    #endif /* __BLUEBOX_SAVING_ENABLED */
    return 0;
}
/* Work in progress */
__DEPRECATED__ void* LoadSave(Renderer* Renderer) {
    char save_location[MAX_PATH];
    snprintf(save_location, sizeof(save_location), "%s/.local/share/bluebox/save.png", getenv("HOME"));
    Texture tex = IMG_LoadTexture(*Renderer, save_location);
    RenderGrowthT(tex, Renderer);
    SDL_RenderPresent(*Renderer);
    return tex;
}