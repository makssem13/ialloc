/*
ialloc: intelligent memory allocation library
Features:
	1. Works with all popular compilers
	2. Easy all-cleanup
	3. Semi-automatic error handling
*/
#include "ialloc.h"

void** AllocList = NULL; //  pointer to the array of allocated memories
int    AllocListSize = 0; // size of AllocList
int    AllocListCur = 0; //  current amount of allocated memory chunks


// add pointer to AllocList
bool AL_Add(void* pointer, void (*ErrorHandler)()) {

	void **old_AllocList = AllocList;
	
	if (AllocListSize == 0) {
		AllocList = calloc(1, sizeof(void*));
		AllocListSize = 1;
	}

	if (AllocListSize == AllocListCur) {
		old_AllocList = AllocList;
		AllocList = realloc(AllocList, AllocListSize * sizeof(void*) * 2); // vector-like size handling
		AllocListSize *= 2;
	}

	
	if (AllocList == NULL) {
		free(pointer);
		AllocList = old_AllocList;
		AllocListSize /= 2;
		(*ErrorHandler)();
		return false;
	}

	
	AllocList[AllocListCur] = pointer;
	AllocListCur++;
	return true;
}

// safe malloc
void *imalloc(size_t size, void (*ErrorHandler)()) {
	void *array = malloc(size);
	if (array == NULL) {
		(*ErrorHandler)();
		return NULL;
	}
	else {
		if(!AL_Add(array, ErrorHandler)){return NULL;}
		return array;
	}
}

// safe calloc
void* icalloc(size_t lengh, size_t size, void (*ErrorHandler)()) {
	void *array = calloc(lengh, size);
	if (array == NULL) {
		(*ErrorHandler)();
		return NULL;
	}
	else {
		if(!AL_Add(array, ErrorHandler)){return NULL;}
		return array;
	}
}

// safe realloc
void* irealloc(void *pointer, size_t size, void (*ErrorHandler)()) {
	if(pointer == NULL){
		return imalloc(size, ErrorHandler);
	}
	void *old = pointer;
	void *array = realloc(pointer, size);
	if (array == NULL) {
		(*ErrorHandler)();
		return NULL;
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

// free ialloc pointer
void ifree(void* pointer) {
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

// end ialloc session
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
	AllocListSize = 0;
	AllocListCur = 0;
	return;
}
