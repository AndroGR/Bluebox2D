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

#ifndef _FONT_H
#define _FONT_H
#include "Bluebox.h"
/* Get a title above SetBufferText() function. This should be called first to in a 14 pixel distance from the
   normal text calls.
*/

extern Texture SetBufferTextTitle(const char* text, Renderer* Renderer, int y);

/* Display a welcome message to the buffer (window). As this text is not supposed to stay there forever, we will need
   to destroy it at some point, hence we return the texture of the text to control through main() (The reason we also use
   single pointers instead of double ("int* i" instead of "int** i") to avoid memory violation issues).
*/

extern SDL_Texture* SetBufferText(const int prev, TTF_Font* Font, SDL_Renderer* Renderer, const char* text, SDL_Color white);

/* Write in the bottom of the screen the size of the brush selected. Soon
 * a similar function will be added for selecting the texture.
*/
extern int BrushText(TTF_Font** font, SDL_Renderer** XRender,
                     SDL_Window** XWindow, int* size);

// A copy of the function above
extern int SetTextureTXT(TTF_Font** font, SDL_Renderer **XRender, char* TextureID, SDL_Window** XWindow);

/* Return which texture is selected based on a code, given in the
 * event handling part. Can be freely extended.
*/
extern char* GetTexture(int* code);

// DEPRECATED
/* Write in a screen corner the FPS the game is running at. */
extern int LoadFPSText(float FPS, SDL_Color Color, SDL_Renderer** WindowRenderer);

#endif /* _FONT_H */
