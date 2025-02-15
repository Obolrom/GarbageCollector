#include <stdio.h>
#include <stdlib.h>
#include "virtual_machine.h"

VM* createVirtualMachine() {
    printf("VM init...\n");
    VM* virtualMachine = malloc(sizeof(struct VirtualMachine));
    virtualMachine->heap = malloc(sizeof(VmHeap));
    virtualMachine->heap->memory = malloc(VM_HEAP_SIZE);
    virtualMachine->stack = malloc(sizeof(VmStack));
    printf("VM initialized\n");

    return virtualMachine;
}
