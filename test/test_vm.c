#include "../virtual_machine.h"
#include "../third_party/unity/unity.h"

void setUp() {}
void tearDown() {}

void test_1() {
    int passed = 1;
    VM* vm = createVirtualMachine(320, 32);

    int number = 500;
    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    if (*(int*)(obj1->data) != 500) {
        passed = 0;
    }

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    if (occupiedMemoryBlocks != 2) {
        passed = 0;
    }

    if ((void*) vm->heap->memory != obj1) {
        passed = 0;
    }

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

    TEST_ASSERT_EQUAL_INT(1, passed);

    destroyVirtualMachine(vm);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_1);

    return UNITY_END();
}
