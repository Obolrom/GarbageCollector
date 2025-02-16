#include <stdint.h>

typedef enum VirtualMachineReturnCodes {
    VM_RC_ERROR_OBJ_ALREADY_DELETED,

    VM_RC_SUC_OBJ_DELETED,
} VmRetCode;

typedef enum HeapMemoryBlockBusyIndicator {
    BI_GREEN = 0,
    BI_RED = 1,
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
    uint32_t heapSize;
    uint32_t heapBlockSize;
} VM;

VM* createVirtualMachine(uint32_t vmHeapSize, uint32_t vmHeapBlockSize);

void destroyVirtualMachine(VM* vm);

VmHeap* createVmHeap(VM* vm);

void destroyVmHeap(VmHeap* vmHeap);

uint32_t getOccupiedHeapBlocksAmount(VmHeap* heap);

uint32_t getFreeHeapBlocksAmount(VmHeap* heap);

void* findFreeBlockAddress(VM* vm, size_t objectSize);

void printShortHeapStats(VmHeap* heap);

void printFullHeapStats(VmHeap* heap);

void walkThroughHeap(VM* vm);
