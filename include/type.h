#pragma once
#ifndef _TYPE_H
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

#define _TYPE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
// Mouse type for mouse event handling.
// Bluebox >= 0.3 will require a mouse object.
typedef struct _Mouse {
    int x;
    int y;
    bool MouseDown;
    SDL_Point XYPoint;
    bool *start;
} Mouse;

/* Types commonly used can be shortened to their use. */
typedef SDL_Renderer* Renderer;
typedef SDL_Event Event;
typedef SDL_Surface Surface;
typedef SDL_Texture* Texture;
typedef TTF_Font* Font;
#endif /* _TYPE_H */

