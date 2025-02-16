#include <stdio.h>
#include <stdlib.h>
#include "virtual_machine.h"
#include "vm_object.h"
#include "config.h"

VM* createVirtualMachine(uint32_t vmHeapSize, uint32_t vmHeapBlockSize) {
#ifdef VM_LOGS_ENABLED
    printf("VM init...\n");
#endif
    VM* virtualMachine = malloc(sizeof(struct VirtualMachine));
    virtualMachine->heapSize = vmHeapSize;
    virtualMachine->heapBlockSize = vmHeapBlockSize;
    virtualMachine->heap = createVmHeap(virtualMachine);
    virtualMachine->stack = malloc(sizeof(VmStack));
#ifdef VM_LOGS_ENABLED
    printf("VM initialized\n");
#endif

    return virtualMachine;
}

VmHeap* createVmHeap(VM* vm) {
#ifdef VM_LOGS_ENABLED
    printf("VM heap init...\n");
#endif
    VmHeap* vmHeap = malloc(sizeof(VmHeap));
    uint32_t blockAmount = vm->heapSize / vm->heapBlockSize;

    vmHeap->memory = malloc(vm->heapSize * sizeof(uint8_t));
    vmHeap->blockAmount = blockAmount;
    vmHeap->blocks = malloc(blockAmount * sizeof(VmHeapMemBlock));
    for (int i = 0; i < blockAmount; ++i) {
        VmHeapMemBlock* block = malloc(sizeof(VmHeapMemBlock));
        block->position = i;
        block->busyIndicator = BI_GREEN;
        vmHeap->blocks[i] = block;
    }

#ifdef VM_LOGS_ENABLED
    printf("VM heap initialized; Blocks: %d; Block size: %d\n", blockAmount, vm->heapBlockSize);
#endif

    return vmHeap;
}

void destroyVirtualMachine(VM* vm) {
#ifdef VM_LOGS_ENABLED
    printf("VM destroying...\n");
#endif
    destroyVmHeap(vm->heap);
    free(vm->stack);
    free(vm);

#ifdef VM_LOGS_ENABLED
    printf("VM destroyed\n");
#endif
}

void destroyVmHeap(VmHeap* vmHeap) {
#ifdef VM_LOGS_ENABLED
    printf("VM heap destroying...\n");
#endif
    for (int i = 0; i < vmHeap->blockAmount; ++i) {
        free(vmHeap->blocks[i]);
    }
    free(vmHeap->blocks);
    free(vmHeap->memory);
    free(vmHeap);

#ifdef VM_LOGS_ENABLED
    printf("VM heap destroyed\n");
#endif
}

void* findFreeBlockAddress(VM* vm, size_t objectSize) {
    VmHeap* heap = vm->heap;
    uint32_t freeMemoryBytes = 0;
    int counter = 0;
    VmHeapMemBlock* freeMemoryStart = NULL;

    for (int i = 0; i < heap->blockAmount; ++i) {
        VmHeapMemBlock* block = heap->blocks[i];

        if (block->busyIndicator == BI_GREEN) {
            if (counter == 0) {
                freeMemoryStart = block;
            }
            counter++;
            freeMemoryBytes += vm->heapBlockSize;

            if (freeMemoryBytes >= objectSize) {
                for (int j = 0; j < counter; j++) {
                    heap->blocks[i - j]->busyIndicator = BI_RED;
                }
                return (void*)(heap->memory + (freeMemoryStart->position * vm->heapBlockSize));
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
        if (heap->blocks[i]->busyIndicator == BI_RED) {
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

void walkThroughHeap(VM* vm) {
    VmHeap* heap = vm->heap;
    size_t currentBlockIndex = 0;
    size_t actualOccupiedMemory = 0;
    size_t totalBlocksOccupiedMemory = 0;

    while (currentBlockIndex < heap->blockAmount) {
        VmHeapMemBlock* currentBlock = heap->blocks[currentBlockIndex];
        if (currentBlock == NULL) {
            printf("Error: NULL block at index %zu\n", currentBlockIndex);
            break;
        }

        if (currentBlock->busyIndicator == BI_RED) {
            HeapObj* object = (HeapObj*)
                    ((uint8_t *)heap->memory + (currentBlock->position * vm->heapBlockSize));

            if (object->objectSize == 0 || object->objectSize > vm->heapSize) {
                printf("Error: Invalid objectSize at block %zu\n", currentBlockIndex);
                break;
            }

            actualOccupiedMemory += object->objectSize;

            size_t consumedBlocks = (object->objectSize + vm->heapBlockSize - 1) / vm->heapBlockSize;
            totalBlocksOccupiedMemory += consumedBlocks * vm->heapBlockSize;

            printf("Block BI_RED %zu\tObject size: %zu\tBlocks used: %zu\t%p\n",
                   currentBlock->position, object->objectSize, consumedBlocks, object->data);

            currentBlockIndex += consumedBlocks;
        } else {
            printf("Block %zu is free\n", currentBlock->position);
            currentBlockIndex++;
        }
    }

    printf("Total occupied memory: %zu bytes\n", actualOccupiedMemory);
    printf("Total allocated blocks memory: %zu bytes\n", totalBlocksOccupiedMemory);
    printf("Memory fragmentation: %zu bytes\n", totalBlocksOccupiedMemory - actualOccupiedMemory);
}
