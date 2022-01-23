#include <stdio.h>

#include <oscar.h>

int main() {
    oscarize();
    printf("hello world!");
    int* elmo = (int*) allocate(sizeof(int));
    return 0;
}