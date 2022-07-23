#pragma once
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

#ifndef __RENDER__H__
#define __RENDER__H__

#include "Bluebox.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "def.h"

/*  This is a struct that contains everything associated with a texture. */
typedef struct TextureData {
    Texture raw_texture;
    int x, y;
    Renderer* RendererID;
    bool success;
} TextureData;

// This function copies the texture on the framebuffer again, without requiring additional memory.
// This is an experimental way to fix the buffers switching asynchronously.
extern int CopyTexture(TextureData data, float space);
// This basically redraws a texture given, useful to redraw
// textures when resizing the window.
extern TextureData RedrawTexture(TextureData data);
// Render a texture that fills the entire renderer.
extern TextureData RenderGrowthT(TextureData data);
// Erase a part of the renderer
extern NULLPROHIB void Erase(Renderer* RendererID);
// Use this function to render an element filling the screen.
extern NULLPROHIB TextureData RenderGrowth(SDL_Renderer** Renderer);
// Basically draw an image to the window. The function you see being called for 99% of the game loop.
extern NULLPROHIB TextureData _RenderParticle(const int x, const int y, const float space, char** path, SDL_Renderer** Renderer, bool SingleClick);
// Load a static texture for bigger dimensions. Will soon be replaced by Fill()
extern NULLPROHIB SDL_Texture* TextureLoader(int x, int y, const char* path, SDL_Renderer** WindowRenderer);
// Add a background in the start menu.
extern NULLPROHIB SDL_Texture* TextureBackground(const char* path, SDL_Renderer** Renderer);
// Free resources taken up by SDL like the window and the renderer.
extern NULLPROHIB int FreeSDLResources(SDL_Window** AllocatedWindow, SDL_Renderer** AllocatedRenderer);
// Set the window color to black.
extern NULLPROHIB void SetWindowColor(SDL_Renderer** RenderColor);
// Update the window by switching the buffers.
NULLPROHIB FORCE_INLINE inline void WindowUpdate(Renderer* RendererID) {
    SDL_RenderPresent(*RendererID);
}
// This is a function to both clear the screen and if the user placed down water, then
// also place that down.
extern NULLPROHIB __DEPRECATED__ void ClearScreen(Renderer* RendererID);

#endif /* _RENDER_H */

