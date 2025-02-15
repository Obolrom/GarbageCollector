#include <stdio.h>
#include <stdlib.h>
#include "virtual_machine.h"

VM* createVirtualMachine() {
    printf("VM init...\n");
    VM* virtualMachine = malloc(sizeof(struct VirtualMachine));
    virtualMachine->heap = createVmHeap();
    virtualMachine->stack = malloc(sizeof(VmStack));
    printf("VM initialized\n");

    return virtualMachine;
}

VmHeap* createVmHeap() {
    printf("VM heap init...\n");
    VmHeap* vmHeap = malloc(sizeof(VmHeap));
    uint32_t blockAmount = VM_HEAP_SIZE / VM_HEAP_BLOCK_SIZE;

    vmHeap->memory = malloc(VM_HEAP_SIZE);
    vmHeap->blockAmount = blockAmount;
    vmHeap->blocks = malloc(blockAmount * sizeof(VmHeapMemBlock));
    for (int i = 0; i < blockAmount; ++i) {
        VmHeapMemBlock* block = malloc(sizeof(VmHeapMemBlock));
        block->position = i;
        block->busyIndicator = GREEN;
        vmHeap->blocks[i] = block;
    }

    printf("VM heap initialized; Blocks: %d; Block size: %d\n", blockAmount, VM_HEAP_BLOCK_SIZE);

    return vmHeap;
}

void* findFreeBlockAddress(VmHeap* heap, size_t objectSize) {
    uint32_t freeMemoryBytes = 0;
    int counter = 0;
    VmHeapMemBlock* freeMemoryStart = NULL;

    for (int i = 0; i < heap->blockAmount; ++i) {
        VmHeapMemBlock* block = heap->blocks[i];

        if (block->busyIndicator == GREEN) {
            if (counter == 0) {
                freeMemoryStart = block;
            }
            counter++;
            freeMemoryBytes += VM_HEAP_BLOCK_SIZE;

            if (freeMemoryBytes >= objectSize) {
                for (int j = 0; j < counter; j++) {
                    heap->blocks[i - j]->busyIndicator = RED;
                }
                return (void*)(heap->memory + (freeMemoryStart->position * VM_HEAP_BLOCK_SIZE));
            }
        }
        else {
            freeMemoryBytes = 0;
            counter = 0;
        }
    }

    return NULL;
}

uint32_t getOccupiedHeapBlocksAmount(VmHeap* heap) {
    uint32_t occupiedBlocks = 0;
    for (int i = 0; i < heap->blockAmount; ++i) {
        if (heap->blocks[i]->busyIndicator == RED) {
            ++occupiedBlocks;
        }
    }

    return occupiedBlocks;
}

uint32_t getFreeHeapBlocksAmount(VmHeap* heap) {
    return heap->blockAmount - getOccupiedHeapBlocksAmount(heap);
}

void printShortHeapStats(VmHeap* heap) {
    printf("--------------------------------\n");
    printf("Blocks (occupied / all): %d / %d\n", getOccupiedHeapBlocksAmount(heap), heap->blockAmount);
    printf("Free blocks: %d\n", getFreeHeapBlocksAmount(heap));
}

void printFullHeapStats(VmHeap* heap) {
    printf("--------------------------------\n");
    printf("Heap blocks dump\n");
    for (int i = 0; i < heap->blockAmount; ++i) {
        VmHeapMemBlock* block = heap->blocks[i];
        printf("|Block: %zu\t%d\t", block->position, block->busyIndicator);
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}
