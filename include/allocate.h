#ifndef ALLOCATE
#define ALLOCATE

#include <stddef.h>

#define PAGE 4096

typedef struct header_ {
    unsigned int size;
    struct header_ *next;
} header;

static header base;
static header* free = &base;
static header* used;

static void _updateFreeMemory(header* block);
static header* _requestMoreMemory(size_t units);
void* allocate(size_t size);

#endif