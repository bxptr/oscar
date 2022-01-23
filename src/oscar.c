#include <oscar.h>
#include <allocate.h>
#include <scan.h>

#include <stdio.h>

static unsigned long stackBottom;

void oscarize() {
    static int initalized;
    FILE *statistics;
    if (initalized) {
        return;
    }
    else {
        initalized = 1;
        statistics = fopen("/proc/self/stat", "r");
        fscanf(statistics,
               "%*d %*s %*c %*d %*d %*d %*d %*d %*u "
               "%*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld "
               "%*ld %*ld %*ld %*ld %*llu %*lu %*ld "
               "%*lu %*lu %*lu %lu", &stackBottom
        );
        fclose(statistics);
        used = NULL;
        base.next = free = &base;
        base.size = 0;
    }
}
void oscar() {
    header* pointer;
    header* virtual;
    header* tagged;
    unsigned long stackTop;
    extern char end, etext;
    if (used == NULL) {
        return;
    } else {
        _scanRegion(&etext, &end);
        asm volatile ("movl %%ebp, %0" : "=r" (stackTop));
        _scanRegion(stackTop, stackBottom);
        _scanAllBlocks();
        for (
            virtual = used;
            pointer = UNTAG(used->next);
            virtual = pointer, pointer = UNTAG(pointer->next)
        ) {
            next:
                if (!((unsigned int) pointer->next & 1)) {
                    tagged = pointer;
                    pointer = UNTAG(pointer->next);
                    _updateFreeMemory(tagged);
                    if (used == tagged) {
                        used = NULL;
                        break;
                    }
                    virtual->next = (unsigned int) pointer | ((unsigned int) virtual->next & 1);
                    goto next;
                }
                pointer->next = ((unsigned int) pointer->next) & -1;
                if (pointer == used) {
                    break;
                }
        }

    }
}