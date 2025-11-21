# ialloc
A simple malloc/calloc/realloc/free intelligent wrapper that makes your life easier.

### This library features:
- Semi-automatic NULL pointer handling
- Easy all-cleanup

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
