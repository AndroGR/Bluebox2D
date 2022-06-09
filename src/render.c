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

#include <Bluebox.h>
#define MS(x) ((float)(x / 1004))

#include <render.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <log.h>
#include <message.h>

// A function to load textures with one call instead of doing the same work everytime. I plan to
// replace all of the code it provides with it.
static FORCE_INLINE inline Texture load_texture_wp(const char* path, SDL_Renderer** XRender) {
    return IMG_LoadTexture(*XRender, path);
}
bool water_placed = false;
NOINIT static ElementData global;

#ifdef __LINUX__ 
/* A function to check if the asset is readable. Linux-only. */
FORCE_INLINE inline static bool check_file(const char* filename)
{
    /* stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c?rq=1 */
    struct stat buf;
    return (stat(filename, &buf) == 0);
}
#endif /* __LINUX__ */

// This function brightens up the texture we are rendering.
// We first render the texture returned by this function, then
// the normal (Loaded) texture.
FORCE_INLINE inline static Texture brighten_texture(Texture tex) {
    SDL_SetTextureColorMod(tex, 255, 255, 255);
    if (SDL_SetTextureAlphaMod(tex, (float)(255.0f * (char)1.22f)) != 0) {
        #ifdef HAVE__DEBUG
        LogToBluebox(5, "Error increasing the texture brightness");
        return NULL;
        #else
        return NULL;
        #endif /* HAVE__DEBUG */
    }
    return tex;
}

static bool IsOverlaping(ElementData Data0, ElementData Data1) {
    SDL_Point p1;
    SDL_Rect Rect;

    p1.x = Data0.X;
    p1.y = Data0.Y;

    Rect.x = Data1.X;
    Rect.y = Data1.Y;
    Rect.w = Data1.Width;
    Rect.h = Data1.Height;

    return SDL_PointInRect(&p1, &Rect);
}


inline static Texture darken_texture(Texture tex) {
        SDL_SetTextureColorMod(tex, 255, 255, 255);
    if (SDL_SetTextureAlphaMod(tex, (float)(255.0f / 4)) != 0) {
        #ifdef HAVE__DEBUG
        LogToBluebox(5, "Error increasing the texture brightness");
        return NULL;
        #else
        return NULL;
        #endif /* HAVE__DEBUG */
    }
    return tex;
}

Texture RenderGrowth(SDL_Renderer **Renderer) {
    /* This may be removed. */
    SDL_RenderClear(*Renderer);
    SDL_RenderPresent(*Renderer);
    Texture TextureID = load_texture_wp("/usr/share/bluebox/pwater.png", Renderer);
    assert(TextureID != NULL);
    if (SDL_SetTextureBlendMode(TextureID, SDL_BLENDMODE_BLEND) != 0 ||
        SDL_SetTextureAlphaMod(TextureID, (char)(255.0f * 4)) != 0) {
        LogToBluebox(5, "Setting blend mode or alpha failed");
    }
    SDL_RenderCopy(*Renderer, TextureID, NULL, NULL);
    SDL_DestroyTexture(TextureID);
    return TextureID;
}

FORCE_INLINE inline bool GetWaterPlaced() {
    return water_placed;
}

Texture _RenderParticle(const int x, const int y, const float space, char** path, Renderer* Renderer, bool SingleClick) {
    bool is_water = false;
    Texture TextureID = NULL;
    if (strcmp(*path, "/usr/share/bluebox/pwater.png") == 0 && SingleClick) {
        is_water = true;
        // Since changing the entire codebase is not a viable solution,
        // we can just call the function from here.
        bool* WaterPlacedPtr = &water_placed;
        *WaterPlacedPtr = true;
        return RenderGrowth(Renderer);
    } else if (!SingleClick && strcmp("/usr/share/bluebox/pwater.png", *path) == 0) {
            #ifdef HAVE__DEBUG
            LogToBluebox(1, "This is a water texture. You cannot place them like other elements");
            #endif /* HAVE__DEBUG */
            is_water = true;
    }
    if (!is_water) {
        ElementData prev, next;
        if (IsOverlaping(prev, next)) return NONNULL;
        SDL_Rect Rect;
        ASSERT(*path != NULL);
        #ifdef __LINUX__
        if (check_file(*path) != true) {
            char __msg[512];
            sprintf(__msg, "%s\n\nDebug information: \nPath specified: %s\nRenderer address: %p.", "Bluebox tried to load an asset from the disk, but failed. \nPlease make sure you \
have installed all the required assets before proceeding.\n \
You may also try checking if Bluebox has access to the filesystem.\n \
\nThe application will now be terminated.", *path, (void*)Renderer);
            ErrorMessageT(__msg, NULL, "Error loading assets !");
        }
        #endif /* __LINUX__ */
        TextureID = load_texture_wp(*path, Renderer);
        Texture TextureID_Brightened = brighten_texture(TextureID);
        if (TextureID == NULL) {
            LogToBluebox(4, "Texture could not be loaded");
            return NULL;
        }
        ASSERT(TextureID != NULL);
        ASSERT(TextureID_Brightened != NULL);
        /* Enabling blending allows us to have transparent textures. */
        SDL_SetTextureBlendMode(TextureID, SDL_BLENDMODE_BLEND);
        Rect.h = 32 * space / (float)1.5f;
        Rect.w = 32 * space / (float)1.5f;
        Rect.x = x;
        Rect.y = y;
        SDL_RenderCopy(*Renderer, TextureID, NULL, &Rect);
        SDL_DestroyTexture(TextureID);
        SDL_DestroyTexture(TextureID_Brightened);
    } else {
        return (void*) 1;
    }
    return (void*)TextureID;
}

// It looks like we won't be using it because it slows down the program for some reason.
int FreeSDLResources(SDL_Window** AllocatedWindow, SDL_Renderer** AllocatedRenderer) {
    SDL_DestroyRenderer(*AllocatedRenderer);
    SDL_DestroyWindow(*AllocatedWindow);
    return 0;
}

NULLPROHIB __DEPRECATED__ FORCE_INLINE inline void ClearScreen(Renderer* RendererID) {
    SDL_SetRenderDrawColor(*RendererID, 0, 0, 0, 255);
    SDL_RenderClear(*RendererID);
    RenderGrowth(RendererID);
    WindowUpdate(RendererID);
}
