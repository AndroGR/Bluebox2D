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

#ifndef _SAVE_H
#define _SAVE_H
#include "Bluebox.h"
/* Save the renderer to a readable file. This file can then be loaded from the disk and used as a
   surface to draw on. Worth noting, this is not the final way of saving. On release v0.5, i plan
   to create a layer system to add entities to the game, and hence loading images is impossible for
   layers. */
extern int SaveProgress(const char* saveloc, bool autosave, SDL_Renderer** Renderer, SDL_Window** Window);
#ifdef __BLUEBOX_SAVING_ENABLED
extern void RemoveSave(const char* path);
#endif /* __BLUEBOX_SAVING_ENABLED */
#endif /* _SAVE_H */

