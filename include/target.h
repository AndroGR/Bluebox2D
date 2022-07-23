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

#ifndef __TARGET_H__
#define __TARGET_H__

#include "Bluebox.h"
#include "render.h"
#include "type.h"

// A target is just a texture, so we can typedef it for readability.
typedef Texture RenderTarget;

// If true, the default rendering target for any rendering operations is a texture.
extern void SetTargetCurrent(bool toggle, Renderer* Renderer);
// Gets the rendering target, or NULL if the rendering target is not created.
extern RenderTarget GetRenderTarget(void);

#endif /* __TARGET_H__ */