#include <stdlib.h>
#include "../virtual_machine.h"
#include "../third_party/unity/unity.h"

void setUp() {}
void tearDown() {}

void test_1() {
    VM* vm = createVirtualMachine(320, 32);

    int number = 500;
    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    TEST_ASSERT_FALSE_MESSAGE(
        *(int*)(obj1->data) != 500,
        "Expected obj data = 500"
    );

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_FALSE_MESSAGE(
        occupiedMemoryBlocks != 2,
        "Expected occupiedMemoryBlocks = 2"
    );

    TEST_ASSERT_FALSE_MESSAGE(
        (void*) vm->heap->memory != obj1,
        "Expected heap memory pointer is equal to obj1 pointer"
    );

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
            BI_RED,
            vm->heap->blocks[i]->busyIndicator,
            "Expected free heap blocks to be BI_RED"
        );
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
            BI_GREEN,
            vm->heap->blocks[i]->busyIndicator,
            "Expected free heap blocks to be BI_GREEN"
        );
    }

    destroyVirtualMachine(vm);
}

void test_2() {
    VM* vm = createVirtualMachine(320, 32);

    int number = 500;
    short littleNum = 120;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj1->data) == 500,
            "Expected obj1 data = 500"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj2->data) == 120,
            "Expected obj2 data = 120"
    );

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_TRUE_MESSAGE(
            occupiedMemoryBlocks == 4,
            "Expected occupiedMemoryBlocks = 4"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == obj1,
            "Expected heap memory pointer is equal to obj1 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 2]) == obj2,
            "Expected obj2 pointer"
    );

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_GREEN,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_GREEN"
        );
    }

    destroyVirtualMachine(vm);
}

void test_3() {
    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj1->data) == 500,
            "Expected obj1 data = 500"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj2->data) == 120,
            "Expected obj2 data = 120"
    );

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_TRUE_MESSAGE(
            occupiedMemoryBlocks == 6,
            "Expected occupiedMemoryBlocks = 6"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == obj1,
            "Expected heap memory pointer is equal to obj1 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 3]) == obj2,
            "Expected obj2 pointer"
    );

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_GREEN,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_GREEN"
        );
    }

    destroyVirtualMachine(vm);
}

void test_4() {
    typedef struct CustomType {
        int test1;
        long test2;
        short test3;
    } Data;

    typedef struct CustomType3 {
        int orderNum;
        Data* data;
        int test;
        int test2;
        long test3;
        int test4;
        long test5;
        long test6;
    } Data3;

    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;
    Data3 data3 = { 1, NULL, 2, 3, 4, 5, 6, 7 };
    int8_t byte = 10;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj3 = createObject(vm, sizeof(data3), &data3);
    HeapObj* obj4 = createObject(vm, sizeof(byte), &byte);
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj1->data) == 500,
            "Expected obj1 data = 500"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(short*)(obj2->data) == 120,
            "Expected obj2 data = 120"
    );
    TEST_ASSERT_NULL_MESSAGE(
            ((Data3*)(obj3->data))->data,
            "Expected obj3 is null"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((Data3*)(obj3->data))->orderNum == 1,
            "Expected obj3 data.orderNum = 1"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int8_t *)(obj4->data) == 10,
            "Expected obj4 data = 10"
    );

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_TRUE_MESSAGE(
            occupiedMemoryBlocks == 15,
            "Expected occupiedMemoryBlocks = 15"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == obj1,
            "Expected obj1 is at the beginning of heap"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 3]) == obj2,
            "Expected obj2 pointer"
    );

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_GREEN,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_GREEN"
        );
    }

    destroyVirtualMachine(vm);
}

void test_5() {
    typedef struct CustomType {
        int test1;
        long test2;
        short test3;
    } Data;

    typedef struct CustomType3 {
        int orderNum;
        Data* data;
        int test;
        int test2;
        long test3;
        int test4;
        long test5;
        long test6;
    } Data3;

    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;
    Data3 data3 = { 1, NULL, 2, 3, 4, 5, 6, 7 };
    int8_t byte = 10;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj3 = createObject(vm, sizeof(data3), &data3);
    HeapObj* obj4 = createObject(vm, sizeof(byte), &byte);
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj1->data) == 500,
            "Expected obj1 data = 500"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj2->data) == 120,
            "Expected obj2 data = 120"
    );
    TEST_ASSERT_NULL_MESSAGE(
            ((Data3*)(obj3->data))->data,
            "Expected obj3 is null"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((Data3*)(obj3->data))->orderNum == 1,
            "Expected obj3 data.orderNum = 1"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int8_t *)(obj4->data) == 10,
            "Expected obj4 data = 10"
    );

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_TRUE_MESSAGE(
            occupiedMemoryBlocks == 15,
            "Expected occupiedMemoryBlocks = 15"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == obj1,
            "Expected obj1 is at the beginning of heap"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 3]) == obj2,
            "Expected obj2 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 6]) == obj3,
            "Expected obj3 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 12]) == obj4,
            "Expected obj4 pointer"
    );

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_GREEN,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_GREEN"
        );
    }

    for (int i = 0; i < 3; ++i) {
        vm->heap->blocks[i]->busyIndicator = BI_GREEN;
    }
    void* freeBlockPointer = findFreeBlockAddress(vm, 10);
    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == freeBlockPointer,
            "Expected freeBlockPointer is at the beginning of heap"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vm->heap->blocks[0]->busyIndicator == BI_RED,
            "Expected heap.blocks[0] should be BI_RED"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vm->heap->blocks[1]->busyIndicator == BI_GREEN,
            "Expected heap.blocks[1] should be BI_GREEN"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vm->heap->blocks[2]->busyIndicator == BI_GREEN,
            "Expected heap.blocks[2] should be BI_GREEN"
    );
    for (int i = 3; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }

    TEST_ASSERT_EQUAL_INT_MESSAGE(
            13,
            getOccupiedHeapBlocksAmount(vm->heap),
            "Expected occupied heap size should be 13"
    );

    destroyVirtualMachine(vm);
}

void test_6() {
    typedef struct CustomType {
        int test1;
        long test2;
        short test3;
    } Data;

    typedef struct CustomType3 {
        int orderNum;
        Data* data;
        int test;
        int test2;
        long test3;
        int test4;
        long test5;
        long test6;
    } Data3;

    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;
    Data3 data3 = { 1, NULL, 2, 3, 4, 5, 6, 7 };
    int8_t byte = 10;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj3 = createObject(vm, sizeof(data3), &data3);
    HeapObj* obj4 = createObject(vm, sizeof(byte), &byte);
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj1->data) == 500,
            "Expected obj1 data = 500"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj2->data) == 120,
            "Expected obj2 data = 120"
    );
    TEST_ASSERT_NULL_MESSAGE(
            ((Data3*)(obj3->data))->data,
            "Expected obj3 is null"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((Data3*)(obj3->data))->orderNum == 1,
            "Expected obj3 data.orderNum = 1"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int8_t *)(obj4->data) == 10,
            "Expected obj4 data = 10"
    );

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_TRUE_MESSAGE(
            occupiedMemoryBlocks == 15,
            "Expected occupiedMemoryBlocks = 15"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == obj1,
            "Expected obj1 is at the beginning of heap"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 3]) == obj2,
            "Expected obj2 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 6]) == obj3,
            "Expected obj3 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 12]) == obj4,
            "Expected obj4 pointer"
    );

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_GREEN,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_GREEN"
        );
    }

    VmRetCode returnCode = deleteObject(vm, obj1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            returnCode,
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );

    void* freeBlockPointer = findFreeBlockAddress(vm, 10);
    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == freeBlockPointer,
            "Expected freeBlockPointer is at the beginning of heap"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vm->heap->blocks[0]->busyIndicator == BI_RED,
            "Expected heap.blocks[0] should be BI_RED"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vm->heap->blocks[1]->busyIndicator == BI_GREEN,
            "Expected heap.blocks[1] should be BI_GREEN"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vm->heap->blocks[2]->busyIndicator == BI_GREEN,
            "Expected heap.blocks[2] should be BI_GREEN"
    );
    for (int i = 3; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }

    TEST_ASSERT_EQUAL_INT_MESSAGE(
            13,
            getOccupiedHeapBlocksAmount(vm->heap),
            "Expected occupied heap size should be 13"
    );

    destroyVirtualMachine(vm);
}

void test_7() {
    typedef struct CustomType {
        int test1;
        long test2;
        short test3;
    } Data;

    typedef struct CustomType3 {
        int orderNum;
        Data* data;
        int test;
        int test2;
        long test3;
        int test4;
        long test5;
        long test6;
    } Data3;

    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;
    Data3 data3 = { 1, NULL, 2, 3, 4, 5, 6, 7 };
    int8_t byte = 10;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj3 = createObject(vm, sizeof(data3), &data3);
    HeapObj* obj4 = createObject(vm, sizeof(byte), &byte);
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj1->data) == 500,
            "Expected obj1 data = 500"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj2->data) == 120,
            "Expected obj2 data = 120"
    );
    TEST_ASSERT_NULL_MESSAGE(
            ((Data3*)(obj3->data))->data,
            "Expected obj3 is null"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((Data3*)(obj3->data))->orderNum == 1,
            "Expected obj3 data.orderNum = 1"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int8_t *)(obj4->data) == 10,
            "Expected obj4 data = 10"
    );

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_TRUE_MESSAGE(
            occupiedMemoryBlocks == 15,
            "Expected occupiedMemoryBlocks = 15"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == obj1,
            "Expected obj1 is at the beginning of heap"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 3]) == obj2,
            "Expected obj2 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 6]) == obj3,
            "Expected obj3 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 12]) == obj4,
            "Expected obj4 pointer"
    );

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_GREEN,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_GREEN"
        );
    }

    VmRetCode obj1RetCode = deleteObject(vm, obj1);
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            obj1RetCode,
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );
    VmRetCode obj3RetCode = deleteObject(vm, obj3);
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            obj3RetCode,
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            getOccupiedHeapBlocksAmount(vm->heap) == 6,
            "Expected occupiedMemoryBlocks = 6"
    );
    for (int i = 0; i < vm->heap->blockAmount; ++i) {
        if (i == 3 || i == 4 || i == 5 || i == 12 || i == 13 || i == 14) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_RED,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_RED"
            );
        }
        else {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_GREEN,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_GREEN"
            );
        }
    }

    findFreeBlockAddress(vm, 32);
    for (int i = 0; i < vm->heap->blockAmount; ++i) {
        if (i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 12 || i == 13 || i == 14) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_RED,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_RED"
            );
        }
        else {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_GREEN,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_GREEN"
            );
        }
    }
    findFreeBlockAddress(vm, 10);
    for (int i = 0; i < vm->heap->blockAmount; ++i) {
        if (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 12 || i == 13 || i == 14) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_RED,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_RED"
            );
        }
        else {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_GREEN,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_GREEN"
            );
        }
    }

    findFreeBlockAddress(vm, 120);
    for (int i = 0; i < vm->heap->blockAmount; ++i) {
        if (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 12 || i == 13 || i == 14 ||
            i == 15 || i == 16 || i == 17 || i == 18 || i == 19 || i == 20 || i == 21 || i == 22) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_RED,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_RED"
            );
        }
        else {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_GREEN,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_GREEN"
            );
        }
    }

    findFreeBlockAddress(vm, 40);
    for (int i = 0; i < vm->heap->blockAmount; ++i) {
        if (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 12 || i == 13 || i == 14 ||
            i == 6 || i == 7 || i == 8 ||
            i == 15 || i == 16 || i == 17 || i == 18 || i == 19 || i == 20 || i == 21 || i == 22) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_RED,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_RED"
            );
        }
        else {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_GREEN,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_GREEN"
            );
        }
    }

    destroyVirtualMachine(vm);
}

void test_8() {
    typedef struct CustomType {
        int test1;
        long test2;
        short test3;
    } Data;

    typedef struct CustomType3 {
        int orderNum;
        Data* data;
        int test;
        int test2;
        long test3;
        int test4;
        long test5;
        long test6;
    } Data3;

    typedef struct CustomType4 {
        long test1;
        long test2;
        long test3;
        long test4;
        long test5;
        long test6;
        long test7;
        long test8;
    } Data4;

    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;
    Data3 data3 = { 1, NULL, 2, 3, 4, 5, 6, 7 };
    Data4 data4 = { 1, 2, 3, 4, -100, 6, 7, 700 };
    int8_t byte = 10;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj3 = createObject(vm, sizeof(data3), &data3);
    HeapObj* obj4 = createObject(vm, sizeof(byte), &byte);
    HeapObj* obj5 = createObject(vm, sizeof(data4), &data4);

    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj1->data) == 500,
            "Expected obj1 data = 500"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int*)(obj2->data) == 120,
            "Expected obj2 data = 120"
    );
    TEST_ASSERT_NULL_MESSAGE(
            ((Data3*)(obj3->data))->data,
            "Expected obj3 is null"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((Data3*)(obj3->data))->orderNum == 1,
            "Expected obj3 data.orderNum = 1"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            *(int8_t *)(obj4->data) == 10,
            "Expected obj4 data = 10"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((Data4 *)(obj5->data))->test5 == -100,
            "Expected obj5 data.test5 = 10"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((Data4 *)(obj5->data))->test8 == 700,
            "Expected obj5 data.test8 = 700"
    );

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_TRUE_MESSAGE(
            occupiedMemoryBlocks == 21,
            "Expected occupiedMemoryBlocks = 21"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            (void*) vm->heap->memory == obj1,
            "Expected obj1 is at the beginning of heap"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 3]) == obj2,
            "Expected obj2 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 6]) == obj3,
            "Expected obj3 pointer"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((void*) &vm->heap->memory[vm->heapBlockSize * 12]) == obj4,
            "Expected obj4 pointer"
    );

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_RED,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_RED"
        );
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_GREEN,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_GREEN"
        );
    }

    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            deleteObject(vm, obj1),
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            deleteObject(vm, obj2),
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            deleteObject(vm, obj3),
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );

    HeapObj* objData4_2 = createObject(vm, sizeof(data4), &data4);

    TEST_ASSERT_TRUE_MESSAGE(
            ((Data4 *)(objData4_2->data))->test5 == -100,
            "Expected obj4_2 data.test5 = -100"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            ((Data4 *)(objData4_2->data))->test8 == 700,
            "Expected obj4_2 data.test8 = 700"
    );

    occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    TEST_ASSERT_TRUE_MESSAGE(
            occupiedMemoryBlocks == 15,
            "Expected occupiedMemoryBlocks = 15"
    );

    for (int i = 0; i < vm->heap->blockAmount; ++i) {
        if (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 5 || i == 12 || i == 13 || i == 14 ||
            i == 15 || i == 16 || i == 17 || i == 18 || i == 19 || i == 20) {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_RED,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_RED"
            );
        }
        else {
            TEST_ASSERT_EQUAL_INT_MESSAGE(
                    BI_GREEN,
                    vm->heap->blocks[i]->busyIndicator,
                    "Expected free heap blocks to be BI_GREEN"
            );
        }
    }

    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            deleteObject(vm, objData4_2),
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            deleteObject(vm, obj4),
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            deleteObject(vm, obj5),
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_ERROR_OBJ_ALREADY_DELETED,
            deleteObject(vm, obj1),
            "Expected returnCode should be VM_RC_ERROR_OBJ_ALREADY_DELETED"
    );

    for (int i = 0; i < vm->heap->blockAmount; ++i) {
        TEST_ASSERT_EQUAL_INT_MESSAGE(
                BI_GREEN,
                vm->heap->blocks[i]->busyIndicator,
                "Expected free heap blocks to be BI_GREEN"
        );
    }

    destroyVirtualMachine(vm);
}

void test_9() {
    typedef struct CustomType {
        int test1;
        long test2;
        short test3;
    } Data;

    typedef struct CustomType3 {
        int orderNum;
        Data* data;
        int test;
        int test2;
        long test3;
        int test4;
        long test5;
        long test6;
    } Data3;

    typedef struct CustomType4 {
        long test1;
        long test2;
        long test3;
        long test4;
        long test5;
        long test6;
        long test7;
        long test8;
    } Data4;
    int passed = 1;

    VM* vm = createVirtualMachine(240, 48);

    int number = 500;
    short littleNum = 120;
    Data3 data3 = { 1, NULL, 2, 3, 4, 5, 6, 7 };
    Data4 data4 = { 1, 2, 3, 4, -100, 6, 7, 700 };
    int8_t byte = 10;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj3 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj4 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj5 = createObject(vm, sizeof(littleNum), &littleNum);

    uint32_t freeHeapBlocks1 = getFreeHeapBlocksAmount(vm->heap);
    size_t freeHeapBytes1 = getFreeMemoryAmount(vm);
    size_t fragmentedMemoryAmount1 = getUnusedMemoryAmountForTakenHeapBlocks(vm);

    TEST_ASSERT_TRUE_MESSAGE(
            freeHeapBlocks1 == 0,
            "Expected freeHeapBlocks1 = 0"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            freeHeapBytes1 == 0,
            "Expected freeHeapBytes1 = 0"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            fragmentedMemoryAmount1 == 68,
            "Expected fragmentedMemoryAmount1 = 68"
    );

    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            deleteObject(vm, obj1),
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );
    TEST_ASSERT_EQUAL_INT_MESSAGE(
            VM_RC_SUC_OBJ_DELETED,
            deleteObject(vm, obj3),
            "Expected returnCode should be VM_RC_SUC_OBJ_DELETED"
    );

    uint32_t freeHeapBlocks2 = getFreeHeapBlocksAmount(vm->heap);
    size_t freeHeapBytes2 = getFreeMemoryAmount(vm);
    size_t fragmentedMemoryAmount2 = getUnusedMemoryAmountForTakenHeapBlocks(vm);

    TEST_ASSERT_TRUE_MESSAGE(
            freeHeapBlocks2 == 2,
            "Expected freeHeapBlocks2 = 2"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            freeHeapBytes2 == 96,
            "Expected freeHeapBytes2 = 96"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            fragmentedMemoryAmount2 == 42,
            "Expected fragmentedMemoryAmount2 = 42"
    );

    HeapObj* obj6 = createObject(vm, sizeof(data3), &data3);
    TEST_ASSERT_NOT_NULL_MESSAGE(
            obj6,
            "Expected non null pointer"
    );

    destroyVirtualMachine(vm);
}

void test_10() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = malloc(sizeof(VmDebug));
    vmDebug->ipCount = 4;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 2;
    vmDebug->pointers[1] = 4;
    vmDebug->pointers[2] = 5;
    vmDebug->pointers[3] = 8;

    int32_t bytecode[] = {
            OP_PUSH, 10,
            OP_PUSH, 40,
            OP_ADD,
            OP_PUSH, 50,
            OP_ADD,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 10,
            "Expected output should be 10"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 40,
            "Expected output should be 40"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[2]->type == TYPE_INT && vmDebug->output[2]->intVal == 50,
            "Expected output should be 50"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[3]->type == TYPE_INT && vmDebug->output[3]->intVal == 100,
            "Expected output should be 100"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_11() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = malloc(sizeof(VmDebug));
    vmDebug->ipCount = 4;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 2;
    vmDebug->pointers[1] = 4;
    vmDebug->pointers[2] = 5;
    vmDebug->pointers[3] = 10;

    int32_t bytecode[] = {
            OP_PUSH, 10,
            OP_PUSH, 40,
            OP_ADD,
            OP_JMP, 10,
            OP_PUSH, 50,
            OP_ADD,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 10,
            "Expected output should be 10"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 40,
            "Expected output should be 40"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[2]->type == TYPE_INT && vmDebug->output[2]->intVal == 50,
            "Expected output should be 50"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[3]->type == TYPE_INT && vmDebug->output[3]->intVal == 50,
            "Expected output should be 100"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_12() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = malloc(sizeof(VmDebug));
    vmDebug->ipCount = 2;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 5;
    vmDebug->pointers[1] = 8;

    int32_t bytecode[] = {
            OP_PUSH, 10,
            OP_PUSH, 40,
            OP_ADD,
            OP_PUSH, 20,
            OP_SUB,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 50,
            "Expected output should be 50"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 30,
            "Expected output should be 30"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_13() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = malloc(sizeof(VmDebug));
    vmDebug->ipCount = 2;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 7;
    vmDebug->pointers[1] = 17;

    // should print 21 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 21,
            OP_PUSH, -10,
            OP_PUSH, 10,
            OP_ADD,
            OP_JZ, 17,
            OP_PUSH, 100,
            OP_PUSH, 200,
            OP_PUSH, 300,
            OP_PRINT,
            OP_PRINT,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 0,
            "Expected output should be 0"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 21,
            "Expected output should be 21"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_14() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = malloc(sizeof(VmDebug));
    vmDebug->ipCount = 2;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 7;
    vmDebug->pointers[1] = 17;

    // should print 21 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 21,
            OP_PUSH, -1,
            OP_PUSH, 10,
            OP_ADD,
            OP_JNZ, 17,
            OP_PUSH, 100,
            OP_PUSH, 200,
            OP_PUSH, 300,
            OP_PRINT,
            OP_PRINT,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 9,
            "Expected output should be 9"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 21,
            "Expected output should be 21"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_15() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = malloc(sizeof(VmDebug));
    vmDebug->ipCount = 3;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 2;
    vmDebug->pointers[1] = 4;
    vmDebug->pointers[2] = 12;

    // should print 77 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 15,
            OP_PUSH, 15,
            OP_JEQ, 10,
            OP_PUSH, 33,
            OP_PRINT,
            OP_HALT,
            OP_PUSH, 77,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 15,
            "Expected output should be 15"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 15,
            "Expected output should be 15"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[2]->type == TYPE_INT && vmDebug->output[2]->intVal == 77,
            "Expected output should be 77"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_16() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = malloc(sizeof(VmDebug));
    vmDebug->ipCount = 3;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 2;
    vmDebug->pointers[1] = 4;
    vmDebug->pointers[2] = 8;

    // should print 33 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 15,
            OP_PUSH, 11,
            OP_JEQ, 10,
            OP_PUSH, 33,
            OP_PRINT,
            OP_HALT,
            OP_PUSH, 77,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 15,
            "Expected output should be 15"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 11,
            "Expected output should be 11"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[2]->type == TYPE_INT && vmDebug->output[2]->intVal == 33,
            "Expected output should be 33"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_17() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = calloc(1, sizeof(VmDebug));
    vmDebug->ipCount = 8;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 2;
    vmDebug->pointers[1] = 4;
    vmDebug->pointers[2] = 6;
    vmDebug->pointers[3] = 7;
    vmDebug->pointers[4] = 9;
    vmDebug->pointers[5] = 11;
    vmDebug->pointers[6] = 13;
    vmDebug->pointers[7] = 15;

    // should print 300; 200; 100 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 21,
            OP_PUSH, -10,
            OP_PUSH, 10,
            OP_ADD,
            OP_JNZ, 17,
            OP_PUSH, 100,
            OP_PUSH, 200,
            OP_PUSH, 300,
            OP_PRINT,
            OP_PRINT,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 1; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stack[0] == 21,
            "Expected stack[0] to be 21"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == 0,
            "Expected stackPointer to be 0"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 21,
            "Expected output should be 21"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == -10,
            "Expected output should be -10"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[2]->type == TYPE_INT && vmDebug->output[2]->intVal == 10,
            "Expected output should be 10"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[3]->type == TYPE_INT && vmDebug->output[3]->intVal == 0,
            "Expected output should be 0"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[4]->type == TYPE_INT && vmDebug->output[4]->intVal == 21,
            "Expected output should be 21"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[5]->type == TYPE_INT && vmDebug->output[5]->intVal == 100,
            "Expected output should be 100"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[6]->type == TYPE_INT && vmDebug->output[6]->intVal == 200,
            "Expected output should be 200"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[7]->type == TYPE_INT && vmDebug->output[7]->intVal == 300,
            "Expected output should be 300"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_18() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = calloc(1, sizeof(VmDebug));
    vmDebug->ipCount = 3;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 2;
    vmDebug->pointers[1] = 4;
    vmDebug->pointers[2] = 14;

    // should print 77 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 15,
            OP_PUSH, 11,
            OP_JNE, 12,
            OP_PUSH, 100,
            OP_PUSH, 200,
            OP_PUSH, 300,
            OP_PUSH, 77,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 15,
            "Expected output should be 15"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 11,
            "Expected output should be 11"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[2]->type == TYPE_INT && vmDebug->output[2]->intVal == 77,
            "Expected output should be 77"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_19() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = calloc(1, sizeof(VmDebug));
    vmDebug->ipCount = 3;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 2;
    vmDebug->pointers[1] = 4;
    vmDebug->pointers[2] = 14;

    // should print 77 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 5,
            OP_PUSH, 7,
            OP_JLT, 12,
            OP_PUSH, 100,
            OP_PUSH, 200,
            OP_PUSH, 300,
            OP_PUSH, 77,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 5,
            "Expected output should be 5"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 7,
            "Expected output should be 7"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[2]->type == TYPE_INT && vmDebug->output[2]->intVal == 77,
            "Expected output should be 77"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

void test_20() {
    VM* vm = createVirtualMachine(240, 48);
    VmDebug *vmDebug = calloc(1, sizeof(VmDebug));
    vmDebug->ipCount = 3;
    vmDebug->pointers = malloc(sizeof(int32_t) * vmDebug->ipCount);
    vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
    vmDebug->pointers[0] = 2;
    vmDebug->pointers[1] = 4;
    vmDebug->pointers[2] = 5;

    // should print 1 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 5,
            OP_PUSH, 5,
            OP_CMP_EQ,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, vmDebug, NULL);

    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        TEST_ASSERT_TRUE_MESSAGE(
                vm->stack[i] == -1,
                "Expected to be -1"
        );
    }
    TEST_ASSERT_TRUE_MESSAGE(
            vm->stackPointer == -1,
            "Expected stackPointer to be -1"
    );

    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[0]->type == TYPE_INT && vmDebug->output[0]->intVal == 5,
            "Expected output should be 5"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[1]->type == TYPE_INT && vmDebug->output[1]->intVal == 5,
            "Expected output should be 5"
    );
    TEST_ASSERT_TRUE_MESSAGE(
            vmDebug->output[2]->type == TYPE_INT && vmDebug->output[2]->intVal == 1,
            "Expected output should be 1"
    );

    destroyVmDebug(vmDebug);
    destroyVirtualMachine(vm);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);
    RUN_TEST(test_5);
    RUN_TEST(test_6);
    RUN_TEST(test_7);
    RUN_TEST(test_8);
    RUN_TEST(test_9);
    RUN_TEST(test_10);
    RUN_TEST(test_11);
    RUN_TEST(test_12);
    RUN_TEST(test_13);
    RUN_TEST(test_14);
    RUN_TEST(test_15);
    RUN_TEST(test_16);
    RUN_TEST(test_17);
    RUN_TEST(test_18);
    RUN_TEST(test_19);
    RUN_TEST(test_20);

    return UNITY_END();
}
