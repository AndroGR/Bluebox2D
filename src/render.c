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
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#define MS(x) ((float)(x / 1004))

#include <log.h>
#include <message.h>
#include <render.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

// A function to load textures with one call instead of doing the same work
// everytime. I plan to replace all of the code it provides with it.
static FORCE_INLINE inline Texture load_texture_wp(const char *path,
                                                   SDL_Renderer **XRender) {
  return IMG_LoadTexture(*XRender, path);
}
bool water_placed = false;

#ifdef __LINUX__
/* A function to check if the asset is readable. Linux-only. */
FORCE_INLINE inline static bool check_file(const char *filename) {
  /* stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c?rq=1
   */
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

TextureData RedrawTexture(TextureData data) {
    SDL_Rect temp_rect;
    temp_rect.x = data.x;
    temp_rect.y = data.y;
    temp_rect.w = 32;
    temp_rect.h = 32;
    SDL_RenderCopy(*data.RendererID, data.raw_texture, NULL, &temp_rect);
    return data;
}

TextureData RenderGrowth(Renderer* RendererID) {
    SDL_RenderPresent(*RendererID);
    TextureData data;
    data.RendererID = RendererID;
    data.raw_texture = load_texture_wp("/usr/share/bluebox/pwater.png", RendererID);
    assert(data.raw_texture != NULL);
    if (SDL_SetTextureBlendMode(data.raw_texture, SDL_BLENDMODE_BLEND) != 0 ||
        SDL_SetTextureAlphaMod(data.raw_texture, (char)(255.0f * 4)) != 0) {
        LogToBluebox(5, "Setting blend mode or alpha failed");
        data.success = false;
    }
    SDL_RenderCopy(*data.RendererID, data.raw_texture, NULL, NULL);
    data.success = true;
    return data;
}

TextureData RenderGrowthT(TextureData data) {
        SDL_RenderClear(*data.RendererID);
        SDL_RenderPresent(*data.RendererID);
        SDL_RenderCopy(*data.RendererID, data.raw_texture, NULL, NULL);
        return data;
}

FORCE_INLINE inline bool GetWaterPlaced() { return water_placed; }

NULLPROHIB TextureData _RenderParticle
(const int x, const int y, const float space, char **path, Renderer *Renderer, bool SingleClick) {
    bool is_water = false;
    // We need to declare this as static so that the same message doesn't appear twice.
    static bool MessageShown = false;
    register char* water =
    #ifdef _WIN32
    "res/pwater.png";
    #else
    "/usr/share/bluebox/pwater.png";
    #endif /* _WIN32 */
    TextureData data;
    data.RendererID = Renderer;
    data.success    = true;
    data.x = x;
    data.y = y;
    if (strcmp(*path, water) == 0 && SingleClick) {
        is_water = true;
      // Since changing the entire codebase is not a viable solution,
      // we can just call the function from here.
        bool *WaterPlacedPtr = &water_placed;
        *WaterPlacedPtr = true;
        data.raw_texture = load_texture_wp(water, Renderer);
        return RenderGrowthT(data);
    } else if (!SingleClick &&
              strcmp(water, *path) == 0) {
      #ifdef HAVE__DEBUG
      LogToBluebox(1,
        "This is a water texture. You cannot place them like other elements"
      );
      #endif /* HAVE__DEBUG */
      if (!MessageShown) {
          ErrorMessageT("It seems like the element you have chosen does not permit being placed multiple times. Try single-clicking instead.", NULL, "Could not place element.");
          MessageShown = true;
          return data;
      }  
      is_water = true;
    }
    if (!is_water) {
      ElementData prev, next;
      if (IsOverlaping(prev, next)) {
            data.success = true;
            return data;
      }
      SDL_Rect Rect;
      ASSERT(*path != NULL);
      #ifdef __LINUX__
      if (check_file(*path) != true) {
        char __msg[512];
        sprintf(
            __msg,
            "%s\n\nDebug information: \nPath specified: %s\nRenderer address: "
            "%p.",
            "Bluebox tried to load an asset from the disk, but failed. \nPlease make sure you \
have installed all the required assets before proceeding.\n \
You may also try checking if Bluebox has access to the filesystem.\n \
\nThe application will now be terminated.",
          *path, (void *)Renderer);
        ErrorMessageT(__msg, NULL, "Error loading assets !");
      }
      #endif /* __LINUX__ */
      data.raw_texture = load_texture_wp(*path, Renderer);
      Texture TextureID_Brightened = brighten_texture(data.raw_texture);
      if (data.raw_texture == NULL) {
          LogToBluebox(4, "Texture could not be loaded");
          data.success = false;
          return data;
      }
      ASSERT(TextureID_Brightened != NULL);
      /* Enabling blending allows us to have transparent textures. */
      SDL_SetTextureBlendMode(data.raw_texture, SDL_BLENDMODE_BLEND);
      Rect.h = 32 * space / (float)1.5f;
      Rect.w = 32 * space / (float)1.5f;
      Rect.x = x;
      Rect.y = y;
      SDL_RenderCopy(*data.RendererID, data.raw_texture, NULL, &Rect);
    } else {
        data.success = true;
        return data;
    }
    data.success = true;
    return data;
}


int FreeSDLResources(SDL_Window **AllocatedWindow,
                     SDL_Renderer **AllocatedRenderer) {
  SDL_DestroyRenderer(*AllocatedRenderer);
  SDL_DestroyWindow(*AllocatedWindow);
  return 0;
}

NULLPROHIB __DEPRECATED__ FORCE_INLINE inline void
ClearScreen(Renderer *RendererID) {
        SDL_SetRenderDrawColor(*RendererID, 0, 0, 0, 255);
        SDL_RenderClear(*RendererID);
        RenderGrowth(RendererID);
        WindowUpdate(RendererID);
}
