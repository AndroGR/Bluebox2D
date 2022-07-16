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

#include <errno.h>
#include <stdlib.h>
#include <vector.h>
#include <log.h>

Vector CreateVector(size_t alignment) {
        Vector vec;
        vec.handle = calloc(1, alignment);
        if (!vec.handle) {
                LogMessage("Failed to allocate memory for the vector");
                abort();
        }
        vec.size = alignment;
        vec.alignment = alignment;
        vec.count = 0;
        /* 
         * Since adding to the buffer will increment the amount of items available,
         * we need to start at minus 1.
        */
        vec.amount_of_items = -1;
        return vec;
}

void PushToVector(Vector* vec, TextureData data) {
        size_t new_size = vec->size + vec->alignment;
        TextureData* new_handle = realloc(vec->handle, new_size);
        if (!new_handle) {
                LogMessage("Failed to allocate the new memory for the buffer");
                abort();
        } else {
                vec->amount_of_items++;
                vec->handle = new_handle;
        }
        vec->handle[vec->amount_of_items] = data;
        vec->size = new_size;
}

void PopFromVector(Vector* vec, int location) {
        TextureData data;
        data.raw_texture = NULL;
        vec->handle[location] = data;
}

void PopLastFromVector(Vector* vec) {
        PopFromVector(vec, vec->count);
        vec->size  -= vec->alignment;
        /* 
         * While some may consider this questionable, there isn't 
         * any reason for a second allocation to fail, if the first
         * one (Which was larger too) succeeded. We must be really unlucky to do this.
        */
        vec->handle = realloc(vec->handle, vec->size);
}

void DeleteVector(Vector* vec) {
        free(vec->handle);
        vec->length = 0;
        vec->amount_of_items = 0;
}