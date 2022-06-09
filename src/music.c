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

#include <music.h>

Mix_Music* StartMusic(const char* filename) {
    #ifndef __BLUEBOX_ENABLE_MUSIC
    #error "Music is not enabled, please do not compile the file \"music.c\""
    #endif
    Mix_Init(MIX_INIT_MP3);
    Mix_Music* MusicID = NULL;
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        char _err_[128];
        sprintf(_err_, "Could not open the audio device: %s.", Mix_GetError());
        WarningMessage(_err_, NULL);
        return NULL;
    }
    MusicID = Mix_LoadMUS(filename);
    if (Mix_PlayMusic(MusicID, -1) < 0) {
        char _err[128];
        sprintf(_err, "Could not play the music: %s.", Mix_GetError());
        WarningMessage(_err, NULL);
        return NULL;
    }
    ASSERT(MusicID);
    return MusicID;
}