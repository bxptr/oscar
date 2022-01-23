#include <stddef.h>

#define PAGE 4096

typedef struct header_ {
    unsigned int size;
    struct header_ *next;
} header;

static header base;
static header* free = &base;
static header* used;

void* allocate(size_t size);