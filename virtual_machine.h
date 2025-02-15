#include <stdint.h>

static const uint32_t VM_HEAP_SIZE = 4000;
static const uint32_t VM_HEAP_BLOCK_SIZE = 32;

typedef enum HeapMemoryBlockBusyIndicator {
    GREEN = 0,
    RED = 1,
} BusyIndicator;

typedef struct HeapMemoryBlock {
    size_t position;
    BusyIndicator busyIndicator;
} VmHeapMemBlock;

typedef struct HeapMemory {
    uint8_t* memory;
    uint32_t blockAmount;
    VmHeapMemBlock** blocks;
} VmHeap;

typedef struct StackMemory {

} VmStack;

typedef struct VirtualMachine {
    VmHeap* heap;
    VmStack* stack;
} VM;

VM* createVirtualMachine();

VmHeap* createVmHeap();

uint32_t getOccupiedHeapBlocksAmount(VmHeap* heap);

uint32_t getFreeHeapBlocksAmount(VmHeap* heap);

void* findFreeBlockAddress(VmHeap* heap, size_t objectSize);

void printShortHeapStats(VmHeap* heap);

void printFullHeapStats(VmHeap* heap);
