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

#if !defined(_EXIT_H)
#define _EXIT_H
#include <SDL2/SDL_messagebox.h>
#include <SDL2/SDL_config.h>

/* Display a window asking the user if he wants to exit.
 * The window is created by calling SDL_ShowSimpleMessageBox(..)
 * which may be unstable under Wayland or MacOS. For the sake of
 * completeness, this function will later use GTK on Linux and MacOS,
 * and win32 api on Windows (If the latter is available).
*/
extern int AskForExit(SDL_Window **window);
#endif /* _EXIT_H */
