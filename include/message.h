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

// An information window
extern int InfoMessage(const char* msg, SDL_Window** Parent);
// The same but for errors
extern int ErrorMessageT (const char *msg, SDL_Window **Parent, const char* title);
// Predecessor to ErrorMessageT(), should be removed from the code.
extern __DEPRECATED__ int ErrorMessage  (const char* message, SDL_Window** Parent);
// A warning message window
extern int WarningMessage(const char* message, SDL_Window** Parent);
/*
 * A function to use when something that has to do with
 * initialization failed. Usually you call this if SDL_Init() failed,
 * but any SDL call that is not initialized should call this function
 * for the error reporting.
*/
extern int InitFailureMsg(MessageError Message);

#endif
