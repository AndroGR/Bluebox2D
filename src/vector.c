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

#include <cstdlib>
#include <vector.h>

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

        return vec;
}

void PushToVector(Vector* vec, void *data) {
        vec->count++;
        vec->handle[vec->count] = data;
        vec->size = vec->alignment * vec->count;
}

void PopFromVector(Vector* vec, int location) {
        vec->handle[location] = NULL;
}

void PopLastFromVector(Vector* vec) {
        PopFromVector(vec, vec->count);
        vec->size  -= vec->alignment;
        vec->handle = realloc(vec->handle, vec->size);
}