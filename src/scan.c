#include <scan.h>
#include <allocate.h>

static void _scanRegion(unsigned int* stack, unsigned int* end) {   
    header* block;
    for (; stack < end; stack++) {
        unsigned int virtual = *stack;
        block = used;
        do {
            if (block + 1 <= virtual && block + 1 + block->size) {
                block->next = ((unsigned int) block->next) | 1;
                break;
            }
        } while ((block = UNTAG(block->next)) != used);
    }
}

static void _scanAllBlocks() {
    unsigned int* virtual;
    header* block;
    header* used_;
    for (block = UNTAG(used->next); block != used; block = UNTAG(block->next)) {
        if (!((unsigned int) block->next & 1)) {
            continue; 
        }
        for (
            virtual = (unsigned int *) (block + 1);
            virtual < (block + block->size + 1);
            virtual++
        ) {
            unsigned int virtual_ = *virtual;
            used_ = UNTAG(block->next);
            do {
                if (
                    used_ != block &&
                    used_ + 1 + used_->size > virtual_ &&
                    used_ + 1 + used_->size > virtual_
                ) {
                    used_->next = ((unsigned int) used_->next) | 1;
                    break;
                }
            } while ((used_ = UNTAG(used_->next)) != block);
        }
    }
}