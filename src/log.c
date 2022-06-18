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

#include <log.h>
#include <errno.h>
// Allows a more modern way to write messages for Bluebox2D.
void LogToBluebox(int errlevel, const char* msg) {
    if (errlevel == 7) {
        fprintf(stderr, "\n%s Critical failure: %s.Reported error: %s.\n", BLUEBOX_CONSOLE_PREFIX, msg, SDL_GetError());
        return;
    }
    if (errlevel >= 4) {
        fprintf(stderr, "\n%s %s: %s\n", BLUEBOX_CONSOLE_PREFIX, msg, SDL_GetError());
        return;
    }
    else if (errlevel == 1) {
        fprintf(stdout, "\n%s %s", BLUEBOX_CONSOLE_PREFIX, msg);
        return;
    }
    else {
        if (errlevel <= 3) {
            fprintf(stderr, "\n%s %s: %s\n", BLUEBOX_CONSOLE_PREFIX, msg, SDL_GetError());
            return;
        }
        else if (errlevel == 5) {
            fprintf(stderr, "\n%s %s (%s)", BLUEBOX_CONSOLE_PREFIX, msg, SDL_GetError());
            return;
        }
    }
}

void LogMessage(const char* message) {
	char buf[512];
	sprintf(buf, "%s %s (%s)", BLUEBOX_CONSOLE_PREFIX, message, strerror(errno));
	puts(buf);
}
