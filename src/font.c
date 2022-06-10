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

#include <assert.h>
#include <font.h>
#include <log.h>

SDL_Texture* SetBufferText(const int prev, TTF_Font* Font, SDL_Renderer* Renderer, const char* text, SDL_Color white) {
    static const SDL_Color black = {
        .r = 0,
        .g = 0,
        .b = 0,
        .a = 0
    };
    SDL_Surface* TextureWrapper = TTF_RenderText_Shaded_Wrapped(Font, text, white, black, 512);
    ASSERT(TextureWrapper);
    SDL_Texture* TextTexture = SDL_CreateTextureFromSurface(Renderer, TextureWrapper);
    ASSERT(TextureWrapper);
    SDL_FreeSurface(TextureWrapper);
    SDL_Rect Rect;
    int w, h;
    SDL_QueryTexture(TextTexture, NULL, NULL, &w, &h);
    Rect.h = h;
    Rect.w = w;
    Rect.x = 25;
    Rect.y = prev * 2;
    SDL_RenderCopy(Renderer, TextTexture, NULL, &Rect);
    SDL_DestroyTexture(TextTexture);
    return NULL;
}

extern int BrushText(TTF_Font** font, SDL_Renderer **XRender,
              SDL_Window **XWindow, int *size) {

    static const SDL_Color white = {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = (float) 100.0f
    };
    ASSERT(*font != NULL);
    ASSERT(XRender != NULL);
    int w, h;
    static char text[36];
    snprintf(text, sizeof(text), "Selected brush size: %d", *size);
    SDL_Surface* text_surface = TTF_RenderText_Blended(*font, text, white);
    ASSERT(text_surface != NULL);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(*XRender, text_surface);
    SDL_FreeSurface(text_surface);
    if (!tex) {
        LogToBluebox(5, "Cannot load texture for the font.");
        return 127;
    }
    SDL_Rect rect;
    SDL_GetWindowSize(*XWindow, &w, &h);
    rect.x = 3;
    rect.y = h - 21;
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(*XRender, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
    return 0;
}

int SetTextureTXT(TTF_Font** font, SDL_Renderer **XRender, char* TextureID, SDL_Window** XWindow) {

    // Don't arrays start at index 0?
    int window_dims[2];
    static const SDL_Color white = {
        .r = 255,
        .g = 255,
        .b = 255,
        .a = (float) 100.0f
    };

    if (!*font) {
        LogToBluebox(5, "Font was not initialized");
        return -127;
    }

    if (TTF_Init() < 0) {
        LogToBluebox(7, "Couldn't initialize TTF Library");
        return -127;
    }
    
    static char text[128];
    sprintf(text, "Asset %s bound.", TextureID);
    SDL_Surface* text_surface = TTF_RenderText_Blended(*font, text, white);
    if (!text_surface) {
        LogToBluebox(5, "Cannot create surface for the font");
        return 127;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(*XRender, text_surface);
    SDL_FreeSurface(text_surface);
    if (!tex) {
        LogToBluebox(5, "Cannot load texture for the font.");
        return 127;
    }
    SDL_GetWindowSize(*XWindow, &window_dims[0], &window_dims[1]);
    SDL_Rect rect;
    rect.x = 450;
    rect.y = 700;
    SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(*XRender, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
    return 0;
}

Texture SetBufferTextTitle(const char* text, Renderer* Renderer, int y) {
    const SDL_Color Orange = {
        255, 140, 0, 255
    };
    #if defined (_WIN32)
    const SDL_Color black = {
    	0, 0, 0, 255
    };
    #endif /* _WIN32 */
    #ifndef _WIN32
    Font FontID = TTF_OpenFont("/usr/share/bluebox/fonts/InterV.ttf", 26);
    ASSERT(FontID != NULL);
    #else
    Font FontID = TTF_OpenFont("res/fonts/InterV.ttf", 26);
    ASSERT(FontID != NULL);
    #endif /* _WIN32 */

    #ifndef _WIN32
    Surface* AssetID = TTF_RenderText_Blended(FontID, text, Orange);
    #else
    Surface* AssetID = TTF_RenderText_Shaded_Wrapped(FontID, text, Orange, black, 512);
    #endif
    TTF_CloseFont(FontID);
    if (!AssetID)
	    LogToBluebox(5, "Failed rendering text");
    	    return NULL;
    Texture TextureID = SDL_CreateTextureFromSurface(*Renderer, AssetID);
    SDL_FreeSurface(AssetID);
    ASSERT(TextureID != NULL);
    int w, h;
    SDL_QueryTexture(TextureID, NULL, NULL, &w, &h);
    SDL_Rect RectID = {
        .h = h,
        .w = w,
        .x = 25,
        .y = y
    };
    SDL_RenderCopy(*Renderer, TextureID, NULL, &RectID);
    SDL_DestroyTexture(TextureID);
    return NULL;
}
