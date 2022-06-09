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

/*
  Header useful to obtain version information about Bluebox. 
  You should include this header almost everytime as it contains vital settings about the platform,
  the installation path (Where Bluebox resides its assets) and others.
  All functions in this header are small and simple to avoid complexity on simple tasks.
*/

#ifndef _VERSION_H_
#define _VERSION_H_

#define BLUEBOX_MAJOR_VER (const int) 0
#define BLUEBOX_MINOR_VER (const int) 3
#define BLUEBOX_PATCH_VER (const int) 0

typedef struct BlueboxVersion {
        int major, minor, patch;
        char* has_debug, *has_music;
} BlueboxVersion;

#if defined(__LINUX__) || defined(__linux__)
static char* __version_info = "Bluebox version v0.3.0-alpha, GNU/Linux build.\nAlpha release."
                              #ifdef HAVE__DEBUG
                              "\nCompiled with debug symbols."
                              #else
                              "\nNo debugging symbols detected."
                              #endif /* HAVE__DEBUG */

                              #ifdef __BLUEBOX_ENABLE_MUSIC
                              "\nSound enabled in-game.\n"
                              #else
                              "\nSound disabled.\n"
			      #endif /* __BLUEBOX_ENABLE_MUSIC */
                              ;
#define VERSION_INFO __version_info
                              
#elif defined(_WIN32)
static char* __version_info = "Bluebox version v0.3.0, Windows build.\nAlpha release."
                              #ifdef HAVE__DEBUG
                              "\nCompiled with debug symbols."
                              #else
                              "\nNo debugging symbols detected."
                              #endif /* HAVE__DEBUG */

                              #ifdef __BLUEBOX_ENABLE_MUSIC
                              "\nSound enabled in-game.\n"
                              #else
                              "\nSound disabled.\n"
                              #endif /* __BLUEBOX_ENABLE_MUSIC */
                              ;
#define VERSION_INFO __version_info
                              
#elif defined(__APPLE__) || defined(__MACOSX__)
#warning MacOS X Support is not official.
static char* __version_info = "Bluebox version v0.3.0, MacOS X build.\nAlpha release.\n"
			      "Compiled with: \n"
			      #ifdef HAVE__DEBUG
			      "enable_debug,"
			      #endif /* HAVE__DEBUG */
			      #ifdef __BLUEBOX_ENABLE_MUSIC
			      "enable_music,"
			      #endif /* __BLUEBOX_ENABLE_MUSIC */
			      #ifdef __BLUEBOX_ENABLE_SAVING
			      "enable_saving,"
			      #endif /* __BLUEBOX_ENABLE_SAVING */
			      "core_features\n";
#define VERSION_INFO __version_info
#else
static char* __version_info = "Bluebox version v0.3.0.\nUnknown platform.\nAlpha release."
                              #ifdef HAVE__DEBUG
                              "\nCompiled with debug symbols"
                              #else
                              "\nNo debugging symbols detected."
                              #endif /* HAVE__DEBUG */

                              #ifdef __BLUEBOX_ENABLE_MUSIC
                              "\nSound enabled in-game.\n"
                              #else
                              "\nSound disabled.\n"
                              #endif /* __BLUEBOX_ENABLE_MUSIC */
                              ;
#define VERSION_INFO __version_info
#endif /* Platform again */
#if defined(__LINUX__) || defined(__linux__)
#define VERSION_INFO __version_info
#define __BLUEBOX_LINUX_IMPL
#elif defined(_WIN32)
#define VERSION_INFO __version_info 
#define __BLUEBOX_WIN32_IMPL
#elif defined(__APPLE__) || defined(__MACOSX__)
#define __BLUEBOX_MACOS_IMPL
#define VERSION_INFO __version_info
#endif /* platform */

/*
  Get Bluebox's version information and store it in a struct (Passed as the parameter below).
  If you want to return the struct, use GetBlueboxVersionR() instead.
*/
inline void GetBlueboxVersion(BlueboxVersion* Version) {
        Version->major = BLUEBOX_MAJOR_VER;
        Version->minor = BLUEBOX_MINOR_VER;
        Version->patch = BLUEBOX_PATCH_VER;
        return;
}
inline BlueboxVersion GetBlueboxVersionR(void) {
        BlueboxVersion ver;
        GetBlueboxVersion(&ver);
        return ver;
}

#endif /* _VERSION_H_ */

