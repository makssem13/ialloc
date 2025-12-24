#pragma once

#include <stdlib.h>
#include <stddef.h>

extern void** AllocList; //  pointer to the array of allocated memories
extern int    AllocListSize; //     size of AllocList
extern int    AllocListCur; //     current amount of allocated memory chunks

void AL_Add(void* pointer, void (*ErrorHandler)());
void* imalloc(size_t size, void (*ErrorHandler)());
void* icalloc(size_t lengh, size_t size, void (*ErrorHandler)());
void* irealloc(void* pointer, size_t size, void (*ErrorHandler)());
void ifree(void* pointer, void (*ErrorHandler)());
void iend();
