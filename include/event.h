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

#pragma once

#ifndef _EVENT_H_
#define _EVENT_H_

#include "Bluebox.h"
#include "def.h"
/* 
 * Poll the events of the user.
 * This function should be called in main(). Everything else is handled here.
*/
extern int PollEvents(Event *Event, bool* KeepWindowOpen_ptr, Renderer RendererID, SDL_Window* Window);

#endif  /* _EVENT_H_ */
