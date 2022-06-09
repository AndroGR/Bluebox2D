#pragma once

#ifndef MESSAGE_H
#define MESSAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_messagebox.h>
#include <string.h>
#include "log.h"
// Type used on error reporting windows to optimize output.
typedef enum MessageError {
    WindowFailure,
    RendererFailure,
    SegmentFailure,
    OpeningFailure,
    LibraryFailure,
    AssetLoadFailure
} MessageError;

extern int ErrorMessageT (const char *msg, SDL_Window **Parent, const char* title);
extern int ErrorMessage  (const char* message, SDL_Window** Parent);
extern int WarningMessage(const char* message, SDL_Window** Parent);
extern int InitFailureMsg(MessageError Message);

#endif
