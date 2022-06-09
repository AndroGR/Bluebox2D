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

#ifndef _INIT_H
#define _INIT_H
#include "message.h"
// Initialize a window and a renderer for usage with SDL2.
int WindowInitializer(SDL_Window** WindowPointer, SDL_Renderer **XRenderer, Uint32 flags);
#endif /* _INIT_H */