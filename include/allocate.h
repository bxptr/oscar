#include <stddef.h>

#define PAGE 4096

typedef struct header_ {
    unsigned int size;
    struct header_ *next;
} header;

void* allocate(size_t size);