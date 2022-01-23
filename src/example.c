#include <stdio.h>
#include <oscar.h>

int main() {
    oscarize();
    char* elmo = (char*) allocate(sizeof(char));
    *elmo = "f";
    printf(elmo);
    return 0;
}