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
    VmHeapMemBlock* initialBlock = *heap->blocks;
    size_t currentBlockIndex = 0;
    VmHeapMemBlock* currentBlock = initialBlock;
    size_t actualOccupiedMemory = 0;
    size_t totalBlocksOccupiedMemory = 0;

    while (currentBlock != NULL) {
        if (currentBlock->busyIndicator == BI_RED) {
            HeapObj* object = (void*) heap->memory + (sizeof(HeapObj) * currentBlockIndex);
            actualOccupiedMemory += object->objectSize;
            size_t consumedBlocks = object->objectSize / vm->heapBlockSize;
            if (consumedBlocks % vm->heapBlockSize > 0) {
                consumedBlocks++;
            }
            totalBlocksOccupiedMemory += (consumedBlocks * vm->heapBlockSize);
            for (int i = 0; i < consumedBlocks; ++i) {
                currentBlockIndex++;
            }
            printf("Block BI_RED %zu\t%zu\tconsumed blocks:%zu, %zu\t%p\n",
                   currentBlock->position,
                   object->objectSize,
                   consumedBlocks,
                   object->objectSize % vm->heapBlockSize,
                   object->data);

            currentBlock = heap->blocks[currentBlockIndex];
        }
        else {
            printf("Block %zu\n", currentBlock->position);
            currentBlock = heap->blocks[++currentBlockIndex];
        }
    }
    printf("Calculated occupied memory: %zu\n", actualOccupiedMemory);
    printf("Calculated total blocks occupied memory: %zu\n", totalBlocksOccupiedMemory);
    printf("Memory fragmentation (bytes): %zu\n", (totalBlocksOccupiedMemory - actualOccupiedMemory));
}
