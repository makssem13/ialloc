#pragma once

#include <stdlib.h>

void** AllocList = NULL; //  pointer to the array of allocated memories
int    AllocListSize = 0; //     size of AllocList
int    AllocListCur = 0; //     current amount of allocated memory chunks

void AL_Add(void* pointer, void (*ErrorHandler)());
void* imalloc(size_t size, void (*ErrorHandler)());
void* icalloc(size_t lengh, size_t size, void (*ErrorHandler)());
void* irealloc(void* pointer, size_t size, void (*ErrorHandler)());
void ifree(void* pointer, void (*ErrorHandler)());
void iend();