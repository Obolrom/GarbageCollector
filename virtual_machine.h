#include <stdint.h>

static const int VM_HEAP_SIZE = 4000;

struct VirtualMachine {
    struct HeapMemory* heap;
    struct StackMemory* stack;
};

struct HeapMemory {
    uint8_t* memory;
};

struct StackMemory {

};

typedef struct VirtualMachine VM;
typedef struct HeapMemory VmHeap;
typedef struct StackMemory VmStack;

VM* createVirtualMachine();
