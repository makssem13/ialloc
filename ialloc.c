/*
ialloc: intelligent memory allocation library
WARNING: Don't look there for fancy very good looking code
Features:
	1. Works with all popular compilers
	2. Easy all-cleanup
	3. Semi-automatic error handling
*/
#include "ialloc.h"

void** AllocList = NULL; //  pointer to the array of allocated memories
int    AllocListSize = 0; //     size of AllocList
int    AllocListCur = 0; //     current amount of allocated memory chunks


void AL_Add(void* pointer, void (*ErrorHandler)()) {


	if (AllocListCur == 0) {
		AllocList = calloc(1, sizeof(void*));
		AllocListSize = 1;
	}

	if (AllocListSize == AllocListCur) {
		AllocList = realloc(AllocList, AllocListSize * sizeof(void*) * 2); // vector-like size handling
		AllocListSize *= 2;
	}

	
	if (AllocList == NULL) {
		(*ErrorHandler)();
	}

	
	AllocList[AllocListCur] = pointer;
	AllocListCur++;
	return;
}

// intelligent malloc
void *imalloc(size_t size, void (*ErrorHandler)()) {
	void *array = malloc(size);
	if (array == NULL) {
		(*ErrorHandler)();
	}
	else {
		AL_Add(array, ErrorHandler);
		return array;
	}
}

// intelligent calloc
void* icalloc(size_t lengh, size_t size, void (*ErrorHandler)()) {
	void *array = calloc(lengh, size);
	if (array == NULL) {
		(*ErrorHandler)();
	}
	else {
		AL_Add(array, ErrorHandler);
		return array;
	}
}

// intelligent realloc
void* irealloc(void *pointer, size_t size, void (*ErrorHandler)()) {
	void *old = pointer;
	void *array = realloc(pointer, size);
	if (array == NULL) {
		(*ErrorHandler)();
	}
	else {
		for (int counter = 0; counter < AllocListCur; counter++) {
			if (AllocList[counter] == old) {
				AllocList[counter] = array;
			}
		}
		return array;
	}
}

//intelligent free
void ifree(void* pointer, void (*ErrorHandler)()) {
	if (pointer == NULL) { return; }
	for (int counter = 0; counter < AllocListCur; counter++) {
		if (AllocList[counter] == pointer) {
			int size = AllocListCur - 1 - counter;
			void* tempp = AllocList[AllocListCur - 1];
			AllocList[counter] = tempp;
			AllocListCur--;
			free(pointer);
			return;
		}
	}
	return;
}

//intelligent end allocations
void iend() {
	if (AllocList == NULL) { return; }
	for (int counter = 0; counter < AllocListCur; counter++) {
		if (AllocList[counter] != NULL) {
			free(AllocList[counter]);
			AllocList[counter] = NULL;
		}
	}
	free(AllocList);
	AllocList = NULL;
	return;
}
