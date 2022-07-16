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

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "Bluebox.h"
#include "render.h"

typedef struct Vector {
        TextureData* handle;
        long length;
        size_t size, alignment;
        int count, amount_of_items;
} Vector;

/* 
 * Creates a new, empty, resizable vector. 
 *'alignment' specifies how many bytes each block is. 
*/
extern Vector CreateVector(size_t alignment);

/* Adds a new value to the vector, a copy or reference of 'data'. */
extern void PushToVector(Vector* vec, TextureData data);

/* 
 * Removes the value from that size of the vector, setting it to NULL. 
 * This will not free any memory, since the next block will still be used.
*/
void PopFromVector(Vector* vec, int location);

/*
 * Removes the last block (value) from the vector, freeing memory in the
 * process equivalent to the size of a block.
*/
void PopLastFromVector(Vector* vec);

/*
 * Delete the vector and free memory in the process.
*/
void DeleteVector();

#endif /* __VECTOR_H__ */