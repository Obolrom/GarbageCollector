#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "virtual_machine.h"
#include "vm_object.h"
#include "config.h"

static size_t offset = 0;

HeapObj* createObject(VM* vm, size_t dataSize, void* data) {
    size_t objectSize = sizeof(HeapObj) + dataSize;
    HeapObjMarker marker = CREATED;
    HeapObj* objectStartPtr = findFreeBlockAddress(vm, objectSize);
    if (objectStartPtr == NULL) {
        size_t freeHeapBytes = getFreeMemoryAmount(vm);
        if (freeHeapBytes <= objectSize) {
            return NULL;
        }
        compactHeap(vm, NULL);
        return createObject(vm, dataSize, data);
    }
    objectStartPtr->objectSize = objectSize;
    objectStartPtr->dataSize = dataSize;
    objectStartPtr->marker = marker;
    objectStartPtr->deleted = 0;
    objectStartPtr->data = (void*)(objectStartPtr + sizeof(HeapObj));

    memcpy(objectStartPtr->data, data, dataSize);
    offset += objectSize;
#ifdef VM_LOGS_ENABLED
    printf("Actual memory occupied: %zu\t\tfor obj: %zu\n", offset, objectSize);
#endif

    return objectStartPtr;
}

VmRetCode deleteObject(VM* vm, HeapObj* object) {
    if (object->deleted == 1) {
#ifdef VM_LOGS_ENABLED
        printf("\x1B[31mERROR: Object already deleted\x1B[0m\n");
#endif
        return VM_RC_ERROR_OBJ_ALREADY_DELETED;
    }
    object->deleted = 1;
    uint32_t occupiedBlocks = object->objectSize / vm->heapBlockSize;
    if (object->objectSize % vm->heapBlockSize > 0) {
        occupiedBlocks++;
    }
    uint32_t blockOffset = ((void*)object - (void*)vm->heap->memory) / vm->heapBlockSize;
    uint32_t curBlockIndex = blockOffset;
    VmHeapMemBlock* blockAddress = vm->heap->blocks[curBlockIndex];

    for (int i = 0; i < occupiedBlocks; ++i) {
        blockAddress->busyIndicator = BI_GREEN;
        curBlockIndex++;
        blockAddress = vm->heap->blocks[curBlockIndex];
    }

    return VM_RC_SUC_OBJ_DELETED;
}

void compactHeap(VM* vm, void (*func)(HeapObj*)) {
    VmHeap* heap = vm->heap;
    size_t currentBlockIndex = 0;
    void* temp = malloc(sizeof(uint8_t) * 100);

    while (currentBlockIndex < heap->blockAmount) {
        VmHeapMemBlock* currentBlock = heap->blocks[currentBlockIndex];
        if (currentBlock == NULL) {
            printf("Error: NULL block at index %zu\n", currentBlockIndex);
            break;
        }

        if (currentBlock->busyIndicator == BI_RED) {
            HeapObj* object = (HeapObj*)
                    ((uint8_t *)heap->memory + (currentBlock->position * vm->heapBlockSize));
            memcpy(temp, object->data, object->dataSize);
            size_t dataSize = object->dataSize;
            deleteObject(vm, object);
            object = createObject(vm, dataSize, temp);
            if (func != NULL) {
                func(object);
            }

            if (object->objectSize == 0 || object->objectSize > vm->heapSize) {
                printf("Error: Invalid objectSize at block %zu\n", currentBlockIndex);
                break;
            }

            size_t consumedBlocks = (object->objectSize + vm->heapBlockSize - 1) / vm->heapBlockSize;
            currentBlockIndex += consumedBlocks;
        } else {
            currentBlockIndex++;
        }
    }

    free(temp);
}
