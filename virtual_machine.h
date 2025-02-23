#include <stdint.h>

#define OPERATION_STACK_SIZE 256

enum VirtualMachineOperationalCodes {
    OP_ADD = 1000,
    OP_SUB = 1001,

    OP_PUSH = 2000,
    OP_POP = 2001,
    OP_DUP = 2002,

    OP_PRINT = 3000,

    OP_JMP = 4000,
    OP_JZ = 4001,
    OP_JNZ = 4002,
    OP_JEQ = 4003,
    OP_JNE = 4004,
    OP_JLT = 4005,
    OP_JGT = 4006,
    OP_JLE = 4007,
    OP_JGE = 4008,
    OP_CMP_EQ = 4009,
    OP_CMP_NEQ = 4010,
    OP_CMP_LT = 4011,
    OP_CMP_GT = 4012,
    OP_CMP_LTE = 4013,
    OP_CMP_GTE = 4014,

    OP_CALL = 5000,
    OP_LOAD = 5001,
    OP_STORE = 5002,
    OP_RET = 5003,

    OP_HALT = 9000,
};

typedef struct HeapObject HeapObj;

typedef enum VirtualMachineReturnCodes {
    VM_RC_ERROR_OBJ_ALREADY_DELETED,

    VM_RC_SUC_OBJ_DELETED,
} VmRetCode;

typedef enum {
    TYPE_INT,
    TYPE_OBJECT,
} VmValueType;

typedef struct VirtualMachineValue {
    VmValueType type;
    union {
        int32_t intVal;
        HeapObj* objectVal;
    };
} VmValue;

typedef struct VirtualMachineStackFrame {
    int32_t argsCount;
    int32_t localsCount;
    int32_t returnInstructionPointer;
    VmValue* locals;
    struct VirtualMachineStackFrame* prevFrame;
} VmStackFrame;

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

typedef struct VirtualMachine {
    VmHeap* heap;
    VmStackFrame* callStack;
    uint32_t heapSize;
    uint32_t heapBlockSize;
    int32_t stack[OPERATION_STACK_SIZE];
    int32_t stackPointer;
} VM;

enum ObjectMarker {
    VISITED = 2,
    MARKED = 4,
    CREATED = 8,
};

typedef enum ObjectMarker HeapObjMarker;

struct HeapObject {
    size_t objectSize;
    size_t dataSize;
    HeapObjMarker marker;
    uint8_t deleted;

    void* data;
};

HeapObj* createObject(VM* vm, size_t dataSize, void* data);

VmRetCode deleteObject(VM* vm, HeapObj* object);

void compactHeap(VM* vm, void (*func)(HeapObj*));

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
