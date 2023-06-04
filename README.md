# oscar
a highly efficient garbage collector

oscar is a conservative garbage collector for C that aims to automate and remove the `malloc` and `free` redundancy, replacing it with simpler and smarter functions. it is aimed to be highly efficient and fast, as suggested by it being named after the best Sesame Street character, [oscar](https://muppet.fandom.com/wiki/Oscar_the_Grouch), and following the virtues listed in his record-breaking song, [i love trash](https://www.youtube.com/watch?v=rxgWHzMvXOY).

- [x] reliable, and conservative design
- [x] page-sized memory allocation
- [x] smart and efficient memory scanning
- [x] simple and user-friendly API

example: allocate `char` sized memory to `elmo` and then garbage collect it before exiting.

```c
#include <stdio.h>
#include <oscar.h>

int main() {
    oscarize(); # initialize oscar
    char* elmo = (char*) allocate(sizeof(char));
    *elmo = "f";
    printf(elmo);
    oscar(); # garbage collect `elmo`
    return 0;
}
```
