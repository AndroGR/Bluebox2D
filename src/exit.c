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

#include <exit.h>
#include <log.h>
// Display a window asking the user if he actually wants to exit.
int AskForExit(SDL_Window** window) {
    int i = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Exit Bluebox", "Press OK to exit Bluebox", *window);
    if (i < 0) {
        char log_msg[50];
        sprintf(log_msg, "Cannot ask for exit (Error code is %d)", i);
        LogToBluebox(5, log_msg);
        return i;
    }
    return i;
}
