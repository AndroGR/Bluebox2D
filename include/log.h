#ifndef _LOG_H
#define _LOG_H
#include "Bluebox.h"
// Logs an SDL error to the console
void LogToBluebox(int errlevel, const char* msg);

// Gets the latest errno, gets the string describing it, and then prints it to
// the console, along with the message provided here.
void LogMessage(const char* message);

#endif /* _LOG_H */
