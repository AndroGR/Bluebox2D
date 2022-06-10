#pragma once

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
#ifndef DEF_H
#define DEF_H

#include <signal.h>
#include <assert.h>
#define ASSERT assert
#if !defined (_WIN32)
#define BLUEBOX_CONSOLE_PREFIX "\x1b[92m[ Bluebox ]\x1B[97m"
#else
#define BLUEBOX_CONSOLE_PREFIX "bluebox:"
#endif
#define BLUEBOX_ERR -127
#define BLUEBOX_NULLPTR -1
#define ERRADDR 0x0FFFF

#endif
