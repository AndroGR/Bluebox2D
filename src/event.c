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

#include "message.h"
#include <SDL2/SDL_scancode.h>
#include <event.h>
#include <save.h>
#include <render.h>
#include <main.h>
#include <exit.h>
#include <save.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * Return the path to a sprite that needs to be loaded.
 * This is an attempt to seperate the brush size selection from the
 * material selection without impact on portability.
 */
void SetTexturePath(char **path, int *type) {
  switch (*type) {
  case 0:
#ifndef _WIN32
    *path = "/usr/share/bluebox/tree.png";
#else
    *path = "res/tree.png";
#endif
    break;
  case 1:
#ifndef _WIN32
    *path = "/usr/share/bluebox/sand.png";
#else
    *path = "res/sand.png";
#endif
    break;
  case 2:
#ifndef _WIN32
    *path = "/usr/share/bluebox/pwater.png";
#else
    *path = "res/pwater.png";
#endif
    break;
  case 3:
#ifndef _WIN32
    *path = "/usr/share/bluebox/grass.png";
#else
    *path = "res/grass.png";
#endif
    break;
  case 4:
#ifndef _WIN32
    *path = "/usr/share/bluebox/grass.png";
#else
    *path = "res/grass.png";
#endif
    break;
  case 5:
#ifndef _WIN32
    *path = "/usr/share/bluebox/dirt.png";
#else
    *path = "res/dirt.png";
#endif
    break;
  case 6:
#ifndef _WIN32
    *path = "/usr/share/bluebox/building.png";
#else
    *path = "res/building.png";
#endif
    break;
  default:
    InfoMessage("This key is not yet corresponding to any assets.", NULL);
    printf("\n%s Error: Asset code %d not implemented.", BLUEBOX_CONSOLE_PREFIX,
           *type);
    *path = NULL;
    return;
  }
}

extern int PollEvents(Event *EventID, bool* KeepWindowOpen_ptr, Renderer RendererID, SDL_Window* WindowID) {
    ASSERT(RendererID != NULL);
    int ShouldClear = false;
    int i = 4;
    char* __default_texture =
    #ifdef _WIN32
    "res/pwater.png";
    #else
    "/usr/share/bluebox/pwater.png";
    #endif /* _WIN32 */
    char *texture_selected = __default_texture;
    Mouse MouseID;    
    unsigned int set_clear = 0;
    int BufferID  = 1;
    int TextureCode= 1;
    SDL_Color ColorID = {.r = 255, .g = 255, .b = 255, .a = 255};
    #ifndef _WIN32
    TTF_Font* InterV = TTF_OpenFont("/usr/share/bluebox/fonts/InterV.ttf", 17);
    ASSERT(InterV != NULL);
    #else
    TTF_Font* InterV = TTF_OpenFont("res/fonts/InterV.ttf", 17);
    #endif /* _WIN32 */
    for (int i = 0; i < 3; i++) {
        SDL_RenderClear(RendererID);
        WindowUpdate(&RendererID);
    }
    while (SDL_WaitEvent(*&EventID)) {
        /* We can't use newlines (\n) so we have to call them independently. */
          if (ShouldClear == false) {
            SetBufferTextTitle("Welcome to Bluebox !", &RendererID, 12);
            SetBufferText(24, InterV, RendererID, "Bluebox is a free and open source game", ColorID);
            SetBufferText(36, InterV, RendererID, "where you can create your own worlds freely.", ColorID);
            SetBufferText(48, InterV, RendererID, "The source code is available at the link below:", ColorID);
            SetBufferText(60, InterV, RendererID, "https://github.com/AndroGR/Bluebox2D .", ColorID);
            SetBufferText(72, InterV, RendererID, "You can visit the official site of the game", ColorID);
            SetBufferText(84, InterV, RendererID, "at https://androgr.github.io/Bluebox2D .", ColorID);
            SetBufferText(96, InterV, RendererID, "Press any key to clear this message and start the game.", ColorID);
            // Skipping a line here
            SetBufferText(120, InterV,RendererID, "Have fun playing ! :) -- The creator.", ColorID);
            // We need to update immediately so the user gets to see the message properly.
            WindowUpdate(&RendererID);
          }
        switch (EventID->type) {
        case SDL_QUIT:
          goto quit;
          break;

        case SDL_KEYDOWN:
            if (set_clear != 1) {
                ShouldClear = true;
                SDL_RenderClear(RendererID);
                BrushText(&InterV, &RendererID, &WindowID, &i);
                SetTextureTXT(&InterV, &RendererID,  texture_selected, &WindowID);
                WindowUpdate(&RendererID);
                BrushText(&InterV, &RendererID, &WindowID, &i);
                SetTextureTXT(&InterV, &RendererID,  texture_selected, &WindowID);
                set_clear = 1;
            }
            #if defined(__BLUEBOX_SAVING_ENABLED)
            const uint8_t *press = SDL_GetKeyboardState(NULL);
            if ((press[SDL_SCANCODE_LCTRL] || press[SDL_SCANCODE_RCTRL]) && press[SDL_SCANCODE_S]) {
                int result;
                if ((result = SaveProgress(false, &RendererID, &WindowID)) != 0)
                  LogToBluebox(5, "Cannot save the renderer");
            } else if ((press[SDL_SCANCODE_LCTRL] || press[SDL_SCANCODE_RCTRL]) && press[SDL_SCANCODE_O]) {
                LoadSave(&RendererID);
            } else if ((press[SDL_SCANCODE_LCTRL] || press[SDL_SCANCODE_RCTRL]) && press[SDL_SCANCODE_DELETE]) {
                RemoveSave();
            }
            #else
            LogToBluebox(1, "Requested action is not supported");
            #endif /* __BLUEBOX_SAVING_ENABLED */
            switch (EventID->key.keysym.sym) {
              case SDLK_c:
              #ifdef HAVE__DEBUG
              LogToBluebox(1, "Clearing buffer");
              #endif /* HAVE__DEBUG */
              SDL_RenderClear(RendererID);
              SetTextureTXT(&InterV, &RendererID,  texture_selected, &WindowID);
              SDL_RenderPresent(RendererID);
              SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Window contents erased", "Window contents have been erased.", WindowID);
              break;
              #ifdef HAVE__DEBUG
              case SDLK_r:
                fprintf(stdout, "\n[ Bluebox ] Refreshed logs and surfaces.\n");
                SDL_RenderPresent(RendererID);
                break;
              #endif /* HAVE__DEBUG */
              case SDLK_ESCAPE:
                AskForExit(&WindowID);
                LogToBluebox(1, "ESC Key was pressed -> Quitting");
                FreeSDLResources(&WindowID, &RendererID);
                *KeepWindowOpen_ptr = false;
                SDL_Quit();
                return 0;
                break;
              case SDLK_p:
               TextureCode= 4;
                SetTexturePath(&texture_selected, &TextureCode);
                SetTextureTXT(&InterV, &RendererID,  texture_selected, &WindowID);
                break;
              case SDLK_h:
                TextureCode = 6;
                SetTexturePath(&texture_selected, &TextureCode);
                SetTextureTXT(&InterV, &RendererID,  texture_selected, &WindowID);
                break;
              case SDLK_g:
               TextureCode= 3;
                SetTexturePath(&texture_selected, &TextureCode);
                SetTextureTXT(&InterV, &RendererID, texture_selected, &WindowID);
                break;
              case SDLK_t:
               TextureCode= 0;
                SetTexturePath(&texture_selected, &TextureCode);
                SetTextureTXT(&InterV, &RendererID, texture_selected, &WindowID);
                break;
              case SDLK_d:
               TextureCode= 5;
                SetTexturePath(&texture_selected, &TextureCode);
                SetTextureTXT(&InterV, &RendererID, texture_selected, &WindowID);
                break;
              case SDLK_w:
               TextureCode= 2;
                SetTexturePath(&texture_selected, &TextureCode);
                SetTextureTXT(&InterV, &RendererID, texture_selected, &WindowID);
                break;
              case SDLK_s:
               TextureCode= 1;
                SetTexturePath(&texture_selected, &TextureCode);
                SetTextureTXT(&InterV, &RendererID, texture_selected, &WindowID);
                break;
              case SDLK_0:
                i = 1;
                break;
              case SDLK_1:
                i = 2;
                break;
              case SDLK_2:
                i = 4;
                break;
              case SDLK_3:
                i = 6;
                break;
              case SDLK_4:
                i = 9;
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
        if (set_clear != 0) {
          ShouldClear = true;
          if (set_clear != 3214) {
            MouseID.MouseDown = true;
            MouseID.x = EventID->button.x - 25;
            MouseID.y = EventID->button.y - 25;
            if (EventID->button.button == SDL_BUTTON_RIGHT) {
            } else if (EventID->button.button == SDL_BUTTON_LEFT) {
                void* render_result = (void*) _RenderParticle(MouseID.x, MouseID.y, (float)i, &texture_selected, &RendererID, true);
                ASSERT(render_result != (void*) NULL);
                #ifdef HAVE__DEBUG
                LogToBluebox(1, "Left button pressed");
                #endif /* HAVE__DEBUG */
                BrushText(&InterV, &RendererID, &WindowID, &i);
		            SDL_RenderPresent(RendererID);
                SDL_Delay(1);
 	          }
          }
        }
        case SDL_MOUSEMOTION:
          ShouldClear = 2;
          if (set_clear != 0) {
            /* If you wonder why did i do that, then just place something
            and thank me for not being placed in a 25 pixel offset. */
            MouseID.x = EventID->motion.x - 25;
            MouseID.y = EventID->motion.y - 25;
            MouseID.MouseDown = true;
            if (EventID->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
              ShouldClear = true;
              if (BufferID == 2 && texture_selected != NULL) {
                      void* __render_result = (void*) _RenderParticle(MouseID.x, MouseID.y, i, &texture_selected, &RendererID, false);
                      assert(__render_result != NULL);
                      BrushText(&InterV, &RendererID, &WindowID, &i);
                      SetTextureTXT(&InterV, &RendererID, texture_selected, &WindowID);
                      BufferID = 1;
                      break;
              } else if (BufferID == 1) {
                BufferID = 2;
                WindowUpdate(&RendererID);
                SDL_Delay(1);
                break;
              }
            }
          }
        case SDL_WINDOWEVENT:
            
            switch (EventID->window.event) {

            case SDL_WINDOWEVENT_RESTORED:
                SDL_RenderClear(RendererID);
                WindowUpdate(&RendererID);
                SDL_RenderClear(RendererID);
                WindowUpdate(&RendererID);
                break;
            }

            case SDL_MOUSEBUTTONUP:
                MouseID.MouseDown = false;
                break;
        }
    } while(*KeepWindowOpen_ptr == (bool) true);

  quit:
    LogToBluebox(1, "Terminating application");
    AskForExit(&WindowID);
    *KeepWindowOpen_ptr = false;
    FreeSDLResources(&WindowID, &RendererID);
    
    #ifdef __BLUEBOX_ENABLE_MUSIC
    if (MusicID) {
      Mix_FreeMusic(MusicID);
    } else {
      LogToBluebox(1, "Warning: MusicID is NULL, hence no freeing will be done.");
    }
    Mix_Quit();
    #endif /* __BLUEBOX_ENABLE_MUSIC */
    TTF_CloseFont(InterV);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
