#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtual_machine.h"
#include "vm_object.h"

static size_t offset = 0;

HeapObj* createObject(VM* vm, size_t dataSize, void* data) {
    size_t objectSize = sizeof(HeapObj) + dataSize;
    HeapObjMarker marker = CREATED;
    HeapObj* objectStartPtr = findFreeBlockAddress(vm->heap, objectSize);
    objectStartPtr->objectSize = objectSize;
    objectStartPtr->dataSize = dataSize;
    objectStartPtr->marker = marker;
    objectStartPtr->data = (void*)(objectStartPtr + sizeof(HeapObj));

    memcpy(objectStartPtr->data, data, dataSize);
    offset += objectSize;

    return objectStartPtr;
}
