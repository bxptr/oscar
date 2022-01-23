#define UNTAG(pointer) (((unsigned int) (pointer)) & 0xFFFFFFFC)

static void _scanRegion(unsigned int* top, unsigned int* bottom);
static void _scanAllBlocks();