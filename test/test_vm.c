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

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_1);
    RUN_TEST(test_2);
    RUN_TEST(test_3);
    RUN_TEST(test_4);

    return UNITY_END();
}
