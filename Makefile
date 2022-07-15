# Makefile used for Bluebox.
# If your operating system does not have CMake available, then using this Makefile
# might be easier. It was written for GNU Make but it should work on all POSIX-compliant
# operating systems.

# For Windows users, make sure MinGW is in your PATH variable.
# Change the W32CC to the correct name if its not the correct one.
CC:=/usr/bin/gcc
W32CC:=i686-w64-mingw32-gcc
W32_OUTFILE=bluebox.exe
SOURCES=src/win_init.c src/render.c src/font.c src/message.c src/log.c src/exit.c src/event.c src/main.c src/save.c
INCLUDEDIR=include/
CFLAGS=-std=c99 -Wno-switch-default -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls -Wsign-conversion -Wstrict-overflow=5 -Wundef -Wunused -Wno-implicit-fallthrough -O3 -Wno-unused-variable -Wunused
LIBFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lm -ldl
WLIBFLAGS=-lSDL2.dll -lSDL2_image.dll -lSDL2_ttf.dll -lopengl32
DEBUGFLAGS=-g -O0 -DHAVE__DEBUG
OUTFILE=bluebox

make: ${SOURCES}
	@${CC} ${SOURCES} -o ${OUTFILE} ${LIBFLAGS} ${CFLAGS} -I${INCLUDEDIR}

debug: ${SOURCES}
	@${CC} ${SOURCES} -o ${OUTFILE} ${LIBFLAGS} ${CFLAGS} ${DEBUGFLAGS} -I${INCLUDEDIR} -fsanitize=address

install: res/Bluebox.desktop res/fonts/InterV.ttf res/fonts/LICENSE_InterV.txt
	@mkdir -p /usr/share/bluebox/fonts/
	@cp res/Bluebox.desktop /usr/share/applications
	@cp ${OUTFILE} /usr/bin/
	@cp res/* /usr/share/bluebox -r
	@cp LICENSE /usr/share/bluebox/LICENSE
	@cp res/fonts/LICENSE_InterV.txt /usr/share/bluebox/fonts/
	@echo "The installation was finished succesfully."

uninstall: /usr/bin/${OUTFILE} /usr/share/bluebox/
	@rm -rf /usr/bin/${OUTFILE} && echo "Executable removed."
	@rm -rf /usr/share/bluebox/ && echo "The installation directory has been deleted."
	@rm -rf /usr/share/applications/Bluebox.desktop && echo "Removed .desktop file from /usr/share/applications/"
	@echo "Uninstalled succesfully."

windows: ${SOURCES}
	@${W32CC} -o ${W32_OUTFILE} ${SOURCES} -I${INCLUDEDIR} -Ivendor/SDL2 -L./lib/ ${WLIBFLAGS} ${DEBUGFLAGS}
	@echo "Compiled the executable."
	@[ -d ./Windows ] || mkdir -p ./Windows
	@cp ${W32_OUTFILE} ./Windows/
	@cp dll/* ./Windows
	@echo "The executable has been placed in the Windows/ directory."
	@cp res ./Windows -r
	@echo "Resources copied to Windows/ directory."
	@cp LICENSE ./Windows
	@echo "License moved to the Windows/ directory."
