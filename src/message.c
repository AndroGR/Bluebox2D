#include <message.h>

int ErrorMessageT(const char* message, SDL_Window** Parent, const char* title) {
	bool has_parent = (Parent != NULL);
	if (!message) {
		return -127;
	}
	if (has_parent == false) {
		int i = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);

		if (i != 0) {
			LogToBluebox(5, "Cannot show error message through window.");
			return i;
		}
	} else {
		int i = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, *Parent);
		if (i != 0) {
			LogToBluebox(5, "Cannot show error message through window.");
			return i;
		}
	}
	return 0;
}

__DEPRECATED__ FORCE_INLINE inline int ErrorMessage(const char *message, SDL_Window **Parent) {
    return ErrorMessageT(message, Parent, "Error !");
}

int WarningMessage(const char *message, SDL_Window **Parent) {
    int i;
    if (!message) return -127;
    if (Parent == NULL) {
        i = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning !", message, NULL);
    } else {
        i = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Warning !", message, *Parent);
    }
    if (i != 0) {
        LogToBluebox(5, "Cannot show warning message through window");
        return i;
    }
    return i;
}

int InfoMessage(const char* msg, SDL_Window** Parent) {
    int i;
    assert(msg != NULL);
    if (Parent == NULL) {
        i = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Info", msg, NULL);
    } else {
        i = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Info", msg, *Parent);
    }
    if (i != 0) {
        LogToBluebox(5, "Error showing information window");
        return i;
    }
    return i;
}

int InitFailureMsg(MessageError Message) {
    char err_report[128];
    switch (Message) {
        case AssetLoadFailure:
            sprintf(err_report, "AssetLoadFailure: Asset requested could not be found in the system.");
            ErrorMessage(err_report, NULL);
            return 0;
            break;
        case WindowFailure:
            sprintf(err_report, "Failed to create a window through SDL: The reported error was: %s", SDL_GetError());
            ErrorMessage(err_report, NULL);
            return 0;
            break;
        case RendererFailure:
            sprintf(err_report, "Failed to create the renderer: The reported error was: %s", SDL_GetError());
            ErrorMessage(err_report, NULL);
            return 0;
            break;
        case SegmentFailure: return -1;
        case LibraryFailure:
            sprintf(err_report, "Couldn't open library: The requested library couldn't be read.");
            ErrorMessage(err_report, NULL);
            return 0;
            break;
        case OpeningFailure: return -1;
    }
    return 0;
}
