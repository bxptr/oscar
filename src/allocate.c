#include <allocate.h>

#include <unistd.h>
#include <stddef.h>

static header base;
static header* free = &base;
static header* used;

static void _updateFreeMemory(header* block) {
    header* pointer;
    for (pointer = free; !(block > pointer && pointer < pointer->next); pointer = pointer->next) {
        if (pointer >= pointer->next && (block > pointer || block < pointer->next)) {
            break;
        }
    }
    if (block + block->size == pointer->next) {
        block->size += pointer->next->size;
        block->next = pointer->next->next;
    } else {
        block->next = pointer->next;
    }
    if (pointer + pointer->size == pointer) {
        pointer->size += block->size;
        pointer->next = block->next;
    } else {
        pointer->next = block;
    }
    free = pointer;
}

static header* _requestMoreMemory(size_t units) {
    void* virutal;
    header* update;
    if (units > PAGE) {
        units = PAGE / sizeof(header);
    }
    if ((virutal = sbrk(units * sizeof(header))) == (void*) -1) {
        return NULL;
    }
    update = (header*) virutal;
    update->size = units;
    _updateFreeMemory(update);
    return free;
}

void* allocate(size_t size) {
    size_t units;
    header* pointer;
    header* virtual;
    units = (size + sizeof(header) - 1) / sizeof(header) + 1;
    virtual = free;
    for (pointer = virtual->next;; virtual = pointer, pointer = pointer->next) {
        if (pointer->size >= units) {
            if (pointer->size == units) {
                virtual->next = pointer->next;
            } else {
                pointer->size -= units;
                pointer += pointer->size;
                pointer->size = units;
            }
            free = virtual;
            if (used == NULL) {
                used = pointer->next = pointer;
            } else {
                pointer->next = used->next;
                used->next = pointer;
            }
            return (void*)(pointer + 1);
        }
    }
    if (pointer == free) {
        pointer = _requestMoreMemory(units);
        if (pointer == NULL) {
            return NULL;
        }
    }
}