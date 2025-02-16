#include <stdio.h>
#include <string.h>
#include "virtual_machine.h"
#include "vm_object.h"

#define TEST_OUTPUT_ENABLED
#define RED   "\x1B[31m"
#define GREEN "\x1B[32m"
#define RESET "\x1B[0m"

typedef struct CustomType {
    int test1;
    long test2;
    short test3;
} Data;

typedef struct CustomType2 {
    int orderNum;
    Data* data;
    int test;
    int test2;
    int test3;
    int test4;
    int test5;
    int test6;
    int test7;
    int test8;
    int test9;
    long test10;
    long test11;
    long test12;
    long test13;
    long test14;
    long test15;
    long test16;
    long test17;
    long test18;
    long test19;
} Data2;

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

void test1(VM* vm);

void testSuite();
int testCase1();
int testCase2();
int testCase3();
int testCase4();
int testCase5();

int main() {
    testSuite();

//    VM* vm = createVirtualMachine(4000, 32);
//
//    printShortHeapStats(vm->heap);
//    printFullHeapStats(vm->heap);
//
//    test1(vm);
//
//    printShortHeapStats(vm->heap);
//    printFullHeapStats(vm->heap);
//
//    walkThroughHeap(vm);

    return 0;
}

void testSuite() {
    testCase1();
    testCase2();
    testCase3();
    testCase4();
    testCase5();
}

int testCase1() {
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
        if (vm->heap->blocks[i]->busyIndicator != BI_RED) {
            passed = 0;
        }
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_GREEN) {
            passed = 0;
        }
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase1' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase1' FAILED\n" RESET);
    }
#endif

    return passed;
}

int testCase2() {
    int passed = 1;
    VM* vm = createVirtualMachine(320, 32);

    int number = 500;
    short littleNum = 120;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    if (*(int*)(obj1->data) != 500) {
        passed = 0;
    }
    if (*(short*)(obj2->data) != 120) {
        passed = 0;
    }

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    if (occupiedMemoryBlocks != 4) {
        passed = 0;
    }

    if ((void*) vm->heap->memory != obj1) {
        passed = 0;
    }
    if (((void*) &vm->heap->memory[vm->heapBlockSize * 2]) != obj2) {
        passed = 0;
    }

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_RED) {
            passed = 0;
        }
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_GREEN) {
            passed = 0;
        }
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase2' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase2' FAILED\n" RESET);
    }
#endif

    return passed;
}

int testCase3() {
    int passed = 1;
    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    if (*(int*)(obj1->data) != 500) {
        passed = 0;
    }
    if (*(short*)(obj2->data) != 120) {
        passed = 0;
    }

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    if (occupiedMemoryBlocks != 6) {
        passed = 0;
    }

    if ((void*) vm->heap->memory != obj1) {
        passed = 0;
    }
    if (((void*) &vm->heap->memory[vm->heapBlockSize * 3]) != obj2) {
        passed = 0;
    }

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_RED) {
            passed = 0;
        }
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_GREEN) {
            passed = 0;
        }
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase3' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase3' FAILED\n" RESET);
    }
#endif

    return passed;
}

int testCase4() {
    int passed = 1;
    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;
    Data3 data3 = { 1, NULL, 2, 3, 4, 5, 6, 7 };
    int8_t byte = 10;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj3 = createObject(vm, sizeof(data3), &data3);
    HeapObj* obj4 = createObject(vm, sizeof(byte), &byte);
    if (*(int*)(obj1->data) != 500) {
        passed = 0;
    }
    if (*(short*)(obj2->data) != 120) {
        passed = 0;
    }
    if (((Data3*)(obj3->data))->data != NULL) {
        passed = 0;
    }
    if (((Data3*)(obj3->data))->orderNum != 1) {
        passed = 0;
    }
    if (*(int8_t *)(obj4->data) != 10) {
        passed = 0;
    }

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    if (occupiedMemoryBlocks != 15) {
        passed = 0;
    }

    if ((void*) vm->heap->memory != obj1) {
        passed = 0;
    }
    if (((void*) &vm->heap->memory[vm->heapBlockSize * 3]) != obj2) {
        passed = 0;
    }

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_RED) {
            passed = 0;
        }
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_GREEN) {
            passed = 0;
        }
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase4' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase4' FAILED\n" RESET);
    }
#endif

    return passed;
}

int testCase5() {
    int passed = 1;
    VM* vm = createVirtualMachine(4000, 16);

    int number = 500;
    short littleNum = 120;
    Data3 data3 = { 1, NULL, 2, 3, 4, 5, 6, 7 };
    int8_t byte = 10;

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj3 = createObject(vm, sizeof(data3), &data3);
    HeapObj* obj4 = createObject(vm, sizeof(byte), &byte);
    if (*(int*)(obj1->data) != 500) {
        passed = 0;
    }
    if (*(short*)(obj2->data) != 120) {
        passed = 0;
    }
    if (((Data3*)(obj3->data))->data != NULL) {
        passed = 0;
    }
    if (((Data3*)(obj3->data))->orderNum != 1) {
        passed = 0;
    }
    if (*(int8_t *)(obj4->data) != 10) {
        passed = 0;
    }

    uint32_t occupiedMemoryBlocks = getOccupiedHeapBlocksAmount(vm->heap);
    if (occupiedMemoryBlocks != 15) {
        passed = 0;
    }

    if ((void*) vm->heap->memory != obj1) {
        passed = 0;
    }
    if (((void*) &vm->heap->memory[vm->heapBlockSize * 3]) != obj2) {
        passed = 0;
    }
    if (((void*) &vm->heap->memory[vm->heapBlockSize * 6]) != obj3) {
        passed = 0;
    }
    if (((void*) &vm->heap->memory[vm->heapBlockSize * 12]) != obj4) {
        passed = 0;
    }

    for (int i = 0; i < occupiedMemoryBlocks; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_RED) {
            passed = 0;
        }
    }
    for (int i = (int) occupiedMemoryBlocks; i < vm->heap->blockAmount; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_GREEN) {
            passed = 0;
        }
    }

    for (int i = 0; i < 3; ++i) {
        vm->heap->blocks[i]->busyIndicator = BI_GREEN;
    }
    if ((void*) vm->heap->memory != findFreeBlockAddress(vm, 10)) {
        passed = 0;
    }
    if (vm->heap->blocks[0]->busyIndicator != BI_RED) {
        passed = 0;
    }
    if (vm->heap->blocks[1]->busyIndicator != BI_GREEN) {
        passed = 0;
    }
    if (vm->heap->blocks[2]->busyIndicator != BI_GREEN) {
        passed = 0;
    }
    for (int i = 3; i < occupiedMemoryBlocks; ++i) {
        if (vm->heap->blocks[i]->busyIndicator != BI_RED) {
            passed = 0;
        }
    }

    if (getOccupiedHeapBlocksAmount(vm->heap) != 13) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase5' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase5' FAILED\n" RESET);
    }
#endif

    return passed;
}

void test1(VM* vm) {
    int number = 500;
    float pi = 3.14f;
    short littleNum = 120;
    char test[] = "test data :)";
    Data data = { 255, 0xdeadbeaf, 18 };
    Data2 data2 = { 1, &data, 2, 3, 4, 5, 6, 7, 8, 9 };
    Data3 data3 = { 1, &data, 2, 3, 4, 5, 6, 7 };

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(pi), &pi);
    HeapObj* obj3 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj4 = createObject(vm, sizeof(test), &test);
    HeapObj* obj5 = createObject(vm, sizeof(data), &data);
    HeapObj* obj6 = createObject(vm, sizeof(data), &data);
    data.test1 += 245;
    HeapObj* obj7 = createObject(vm, sizeof(data), &data);
    HeapObj* obj8 = createObject(vm, sizeof(data2), &data2);
    HeapObj* obj9 = createObject(vm, sizeof(data3), &data3);

    printf("obj1: %p\n", (void*)obj1->data);
    printf("obj1: %d\n", *(int*)(obj1->data));
    printf("obj1: %zu\n\n", obj1->objectSize);

    printf("obj2: %p\n", (void*)obj2->data);
    printf("obj2: %f\n", *(float *)(obj2->data));
    printf("obj2: %zu\n\n", obj2->objectSize);

    printf("obj3: %p\n", (void*)obj3->data);
    printf("obj3: %d\n", *(short*)(obj3->data));
    printf("obj3: %zu\n\n", obj3->objectSize);

    printf("obj4: %p\n", (void*)obj4->data);
    printf("obj4: %s\n", (char*)(obj4->data));
    printf("obj4: %zu\n\n", obj4->objectSize);

    printf("obj5: %p\n", (void*)obj5->data);
    printf("obj5: %d\n", ((Data*)(obj5->data))->test1);
    printf("obj5: %lx\n", ((Data*)(obj5->data))->test2);
    printf("obj5: %d\n", ((Data*)(obj5->data))->test3);
    printf("obj5: %zu\n\n", obj5->objectSize);

    printf("obj6: %p\n", (void*)obj6->data);
    printf("obj6: %d\n", ((Data*)(obj6->data))->test1);
    printf("obj6: %lx\n", ((Data*)(obj6->data))->test2);
    printf("obj6: %d\n", ((Data*)(obj6->data))->test3);
    printf("obj6: %zu\n\n", obj6->objectSize);

    printf("obj7: %p\n", (void*)obj7->data);
    printf("obj7: %d\n", ((Data*)(obj7->data))->test1);
    printf("obj7: %lx\n", ((Data*)(obj7->data))->test2);
    printf("obj7: %d\n", ((Data*)(obj7->data))->test3);
    printf("obj7: %zu\n\n", obj7->objectSize);

    printf("obj8: %p\n", (void*)obj8->data);
    printf("obj8: %d\n", ((Data2*)(obj8->data))->orderNum);
    printf("obj8: %d\n", ((Data*)((Data2*)(obj8->data))->data)->test1);
    printf("obj8: %d\n", ((Data*)((Data2*)(obj8->data))->data)->test3);
    data.test1 += 1000;
    data.test3 += 82;
    printf("obj8: %d\n", ((Data*)((Data2*)(obj8->data))->data)->test1);
    printf("obj8: %d\n", ((Data*)((Data2*)(obj8->data))->data)->test3);
    printf("obj8: %zu\n\n", obj8->objectSize);

    printf("obj9: %p\n", (void*)obj9->data);
    printf("obj9: %d\n", ((Data2*)(obj9->data))->orderNum);
    printf("obj9: %d\n", ((Data*)((Data2*)(obj9->data))->data)->test1);
    printf("obj9: %d\n", ((Data*)((Data2*)(obj9->data))->data)->test3);
    printf("obj9: %zu\n\n", obj9->objectSize);
}
