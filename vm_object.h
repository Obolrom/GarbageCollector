#include <stdint.h>

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

typedef struct HeapObject HeapObj;

HeapObj* createObject(VM* vm, size_t dataSize, void* data);

VmRetCode deleteObject(VM* vm, HeapObj* object);
