#include <stdint.h>
#include <stddef.h>
#include "vm_metaspace.h"

#define OPERATION_STACK_SIZE 256

enum VirtualMachineOperationalCodes {
    OP_ADD = 1,
    OP_SUB,
    OP_MUL,

    OP_PUSH_I8,
    OP_PUSH_I16,
    OP_POP,
    OP_DUP,

    OP_PRINT,

    OP_JMP,
    OP_JZ,
    OP_JNZ,
    OP_JEQ,
    OP_JNE,
    OP_JLT,
    OP_JGT,
    OP_JLE,
    OP_JGE,
    OP_CMP_EQ,
    OP_CMP_NEQ,
    OP_CMP_LT,
    OP_CMP_GT,
    OP_CMP_LTE,
    OP_CMP_GTE,

    OP_CALL,
    OP_LOAD,
    OP_STORE,
    OP_RET,

    OP_NEW,
    OP_SET_FIELD,
    OP_GET_FIELD,

    OP_HALT,
};

typedef struct HeapObject HeapObj;

typedef enum VirtualMachineReturnCodes {
    VM_RC_ERROR_OBJ_ALREADY_DELETED,

    VM_RC_SUC_OBJ_DELETED,
} VmRetCode;

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
    VmMetaspace* metaspace;
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

typedef struct VirtualMachineDebug {
    int32_t ip; // deprecated
    VmValue* stackValue; // deprecated

    int32_t ipCount;
    int32_t* pointers;

    VmValue** output;

    struct VirtualMachineDebug* next; // deprecated
} VmDebug;

HeapObj* createObject(VM* vm, size_t dataSize, void* data);

VmRetCode deleteObject(VM* vm, HeapObj* object);

void compactHeap(VM* vm, void (*func)(HeapObj*));

VM *createVirtualMachine(uint32_t vmHeapSize, uint32_t vmHeapBlockSize, VmMetaspace *vmMetaspace);

void executeBytecode(VM *vm, const int8_t *bytecode, VmDebug *vmDebug);

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

VmDebug* createVmDebug(int32_t ipCount);

void destroyVmDebug(VmDebug* vmDebug);
