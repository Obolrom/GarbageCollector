#include <stdio.h>
#include <string.h>
#include "virtual_machine.h"

int main() {
    VM* vm = createVirtualMachine();

    int number = 500;
    float pi = 3.14f;
    short littleNum = 120;

    memcpy(vm->heap->memory, &number, sizeof(int));
    memcpy(vm->heap->memory + sizeof(int), &pi, sizeof(int));
    memcpy(vm->heap->memory + sizeof(int) + sizeof(float), &littleNum, sizeof(short));

    printf("1. %p\n", vm->heap->memory);
    printf("1. %d\n", *(int *)(vm->heap->memory));
    printf("2. %p\n", vm->heap->memory + sizeof(int));
    printf("2. %f\n", *(float *)(vm->heap->memory + sizeof(int)));
    printf("3. %p\n", vm->heap->memory + sizeof(int) + sizeof(float));
    printf("3. %d\n", *(short *)(vm->heap->memory + sizeof(int) + sizeof(float)));

    printf("\nraw bytes\n");
    for (int i = 0; i < 8; ++i) {
        printf("%p: %02x\n", vm->heap->memory + i, vm->heap->memory[i]);
    }
    printf("\n");

    return 0;
}
