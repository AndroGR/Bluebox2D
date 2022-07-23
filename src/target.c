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

#include <target.h>
#include <log.h>

static RenderTarget __target = NULL;

static void create_target(Renderer Render) {
        if (__target) return;
        RenderTarget* ptr = &__target;

        SDL_Rect r;
        SDL_RenderGetViewport(Render, &r);

        *ptr = SDL_CreateTexture(Render, SDL_PIXELFORMAT_RGBA8888, 
                    SDL_TEXTUREACCESS_TARGET, r.w, r.h);
        if (!*ptr) {
                LogToBluebox(4, "Failed to create a display target");
                return;
        }
}

void SetTargetCurrent(bool toggle, Renderer* Renderer) {
        RenderTarget* TargetPointer = &__target;
        if (toggle) {
                if (!__target) create_target(*Renderer);
                SDL_SetRenderTarget(Renderer, __target);
                return;
        } else {
                SDL_SetRenderTarget(Renderer, NULL);
                return;
        }
        return;
}

extern RenderTarget GetRenderTarget(void) { return __target; }
