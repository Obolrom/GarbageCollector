#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "virtual_machine.h"

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

int main() {
    VM* vm = createVirtualMachine(4000, 32);

    printShortHeapStats(vm->heap);
    printFullHeapStats(vm->heap);

    test1(vm);

    printShortHeapStats(vm->heap);
    printFullHeapStats(vm->heap);

    walkThroughHeap(vm);

    return 0;
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
