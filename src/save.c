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
#include <save.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <log.h>
#include <message.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <render.h>
#ifndef _WIN32
#include <sys/stat.h>
#endif /* _WIN32 */
#include <time.h>

#define MAX_PATH 1024

FORCE_INLINE inline static char* getdate(void) {
    char __retval[128];
    time_t rawtime;
    time(&rawtime);
    struct tm* tmp = localtime(&rawtime);
    strftime(__retval, sizeof(__retval), "%d", tmp);
    char* ret = __retval;
    return ret;
}

FORCE_INLINE inline static bool save_directory_exists(void) {
    #ifndef _WIN32
    struct stat st;
    char dir[MAX_PATH];
    snprintf(dir, sizeof(dir), "%s/.local/share/bluebox/", getenv("HOME"));
    return (stat(dir, &st) == 0);
    #else
    return -1;
    #endif /* _WIN32 */
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
    InfoMessage(err, NULL);
    return 0;
}
#ifdef __BLUEBOX_SAVING_ENABLED
int SaveProgress(bool autosave, SDL_Renderer** Renderer, SDL_Window** Window) {
    char dirpath[1024];
    if (!save_directory_exists()) {
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
        ErrorMessageT(str, Window, "Failed to save the renderer output !");
        return -127;
    } else {
        char str[MAX_PATH + 128];
        snprintf(str, sizeof(str), "PNG Save at %s.", location);
    }
    SDL_FreeSurface(Screen);
    char info[MAX_PATH + 128];
    snprintf(info, sizeof(info), "The game was saved at %s.\nDate: %s.", location, getdate());
    InfoMessage(info, Window);
    return 0;
}
#endif /* __BLUEBOX_SAVING_ENABLED */
/* Work in progress */
__DEPRECATED__ void LoadSave(Renderer* Renderer) {
    TextureData data;
    char save_location[MAX_PATH];
    snprintf(save_location, sizeof(save_location), "%s/.local/share/bluebox/save.png", getenv("HOME"));
    data.raw_texture = IMG_LoadTexture(*Renderer, save_location);

    if (!data.raw_texture) {
        char errmsg[MAX_PATH + 128];
        char errmsg_w[MAX_PATH + 128];
        snprintf(errmsg, sizeof(errmsg), "Failed to load %s", save_location);
        snprintf(errmsg_w, sizeof(errmsg_w), "\tYou tried to load a previous session of Bluebox2D, \nbut the data was not read successfully: %s", strerror(errno));
        perror(errmsg);
        ErrorMessageT(errmsg_w, NULL, "Failed to load data !");
    }
    
    InfoMessage("Loading saved game data...", NULL);
    RenderGrowthT(data);
    SDL_RenderPresent(*Renderer);
}
