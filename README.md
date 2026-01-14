# ialloc
A simple malloc/calloc/realloc/free intelligent wrapper that makes your life easier.

### This library features:
- Semi-automatic NULL pointer handling
- Easy all-cleanup

### Compiling ialloc

You can use ialloc in your projects via FetchContent_Declare and FetchContent_MakeAvaible functions in CMake

### Working with ialloc:
There are some functions that you can use:
```
imalloc()
icalloc()
irealloc()
ifree()
iend()
```
All of them except of `iend` is analog of standard function from stdlib but get's pointer to error handler as last argument. Error handler don't get any argument.

`iend` is a function that free's anything and need's to be always called at the end of program.

#### example of use:

```
#include <stdio.h>
#include <ialloc.h>

void error_handler(){
  // this function is called when ialloc can't allocate memory
  printf("Allocation failed!\n");
  iend();
  exit(1);
}

int main(){
  printf("Allocating 1GB of memory\n");
  char *mem = (char*)icalloc(1024*1024*1024, sizeof(char), &error_handler);
  printf("Allocation complete!\n");
  ifree(mem); // here is ifree
  iend();
  return 0;
```

But you can write this code also and it will work:

```
#include <stdio.h>
#include <ialloc.h>

void error_handler(){
  // this function is called when ialloc can't allocate memory
  printf("Allocation failed!\n");
  iend();
  exit(1);
}

int main(){
  printf("Allocating 1GB of memory\n");
  char *mem = (char*)icalloc(1024*1024*1024, sizeof(char), &error_handler);
  printf("Allocation complete!\n");
  // here is no ifree
  iend();
  return 0;
```
