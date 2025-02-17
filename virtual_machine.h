#include <stdint.h>

#define OPERATION_STACK_SIZE 256

enum VirtualMachineOperationalCodes {
    OP_ADD = 1000,
    OP_SUM,

    OP_PUSH = 2000,
    OP_POP = 2001,
    OP_DUP = 2002,

    OP_PRINT = 3000,

    OP_HALT = 4000,
};

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
    VmStack* callStack;
    uint32_t heapSize;
    uint32_t heapBlockSize;
    int32_t stack[OPERATION_STACK_SIZE];
    int32_t stackPointer;
} VM;

VM* createVirtualMachine(uint32_t vmHeapSize, uint32_t vmHeapBlockSize);

void executeBytecode(VM* vm, const int32_t* bytecode, void (*stackTopValueAtInstructionIndex)(int32_t, int32_t));

void destroyVirtualMachine(VM* vm);

VmHeap* createVmHeap(VM* vm);

void destroyVmHeap(VmHeap* vmHeap);

uint32_t getOccupiedHeapBlocksAmount(VmHeap* heap);

uint32_t getFreeHeapBlocksAmount(VmHeap* heap);

void* findFreeBlockAddress(VM* vm, size_t objectSize);

void printShortHeapStats(VmHeap* heap);

void printFullHeapStats(VmHeap* heap);

void walkThroughHeap(VM* vm);

size_t getFreeMemoryAmount(VM* vm);

size_t getUnusedMemoryAmountForTakenHeapBlocks(VM* vm);
