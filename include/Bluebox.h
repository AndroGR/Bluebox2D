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
 * This is a generic header containing commonly used types and structs,
 * definitions and enums.
 * You should probably include this header in most of the source code of Bluebox.
 * Maybe in v0.4 (Where maybe a new API is going to be designed) this header will become the
 * only way to access the API.
*/

#ifndef __BLUEBOX_H__
#define __BLUEBOX_H__

#include "version.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "def.h"
#include "type.h"
#include <stdint.h>
#include "type.h"

/* These are some macros to use for optimization.*/
#if defined(__GNUC__)
#define FORCE_INLINE __attribute__((always_inline))
#define NORETURN     __attribute__((noreturn))
#define __DEPRECATED__ __attribute__((deprecated))
#define NOSTRING __attribute__((nonstring))
#define NOINIT __attribute__((noinit))
#define ISUNUSED __attribute__((unused))
#define NULLPROHIB __attribute__((nonnull))
#else
#define FORCE_INLINE
#define NORETURN
#define __DEPRECATED__
#define NOSTRING
#define NOINIT
#define ISUNUSED
#endif /* __GNUC__ */

/* NONNULL means that the variable is not yet initialized, but you can safely write to it. */
#define NONNULL ((void*)1)

/*
 * Data about the output size of the renderer.
*/

typedef struct {
    int Width, Height;
    // Assumes these are 0 by default.
    int ViewportX, ViewportY;
} RendererSize;

/*
 * A function that renders a texture should return a struct with these
 * fields defined. Failure to do so will cause Bluebox to abort.
*/

typedef struct {
    int Width, Height;
    uint16_t X, Y;
    Renderer RendererID;
    RendererSize Size;
    char* path;
} ElementData;

FORCE_INLINE inline bool get_env(const char* name, const char* value) {
    const char* env = getenv(name);
    if (!env) return false;
    if (strcmp(env, value) != 0) {
        return false;
    } else {
        return true;
    }
    return -127;
}

#endif /* __BLUEBOX_H__ */
