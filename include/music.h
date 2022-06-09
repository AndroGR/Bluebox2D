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

#pragma once
#ifndef _MUSIC_H
#define _MUSIC_H
#ifdef __BLUEBOX_ENABLE_MUSIC
#include <SDL2/SDL_mixer.h>
// Play a music track using SDL_Mixer. Can only be used with __BLUEBOX_ENABLE_MUSIC defined somewhere
// (Most preferably in the build tool).
extern Mix_Music* StartMusic(const char* filename);
#else
#ifdef HAVE__DEBUG
#pragma message ("Music has been disabled. Compile with __BLUEBOX_ENABLE_MUSIC defined to enable it.")
#endif /* HAVE__DEBUG */
#endif /* __BLUEBOX_ENABLE_MUSIC */

/*
 * Basically will play a sound everytime something is
 * placed.
*/
extern int PlayPlacingSF(void);

#endif /* _MUSIC_H */

