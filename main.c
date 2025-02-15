#include <stdio.h>
#include <string.h>
#include "virtual_machine.h"
#include "vm_object.h"

typedef struct CustomType {
    int test1;
    long test2;
    short test3;
} Data;

typedef struct CustomType2 {
    int orderNum;
    Data* data;
} Data2;

void test1(VM* vm);

int main() {
    VM* vm = createVirtualMachine();

    test1(vm);

    return 0;
}

void test1(VM* vm) {
    int number = 500;
    float pi = 3.14f;
    short littleNum = 120;
    char test[] = "test data :)";
    Data data = { 255, 0xdeadbeaf, 18 };
    Data2 data2 = { 1, &data };

    HeapObj* obj1 = createObject(vm, sizeof(number), &number);
    HeapObj* obj2 = createObject(vm, sizeof(pi), &pi);
    HeapObj* obj3 = createObject(vm, sizeof(littleNum), &littleNum);
    HeapObj* obj4 = createObject(vm, sizeof(test), &test);
    HeapObj* obj5 = createObject(vm, sizeof(data), &data);
    HeapObj* obj6 = createObject(vm, sizeof(data), &data);
    data.test1 += 245;
    HeapObj* obj7 = createObject(vm, sizeof(data), &data);
    HeapObj* obj8 = createObject(vm, sizeof(data2), &data2);

    printf("obj1: %p\n", (void*)obj1->data);
    printf("obj1: %d\n", *(int*)(obj1->data));

    printf("obj2: %p\n", (void*)obj2->data);
    printf("obj2: %f\n", *(float *)(obj2->data));

    printf("obj3: %p\n", (void*)obj3->data);
    printf("obj3: %d\n", *(short*)(obj3->data));

    printf("obj4: %p\n", (void*)obj4->data);
    printf("obj4: %s\n\n", (char*)(obj4->data));

    printf("obj5: %p\n", (void*)obj5->data);
    printf("obj5: %d\n", ((Data*)(obj5->data))->test1);
    printf("obj5: %lx\n", ((Data*)(obj5->data))->test2);
    printf("obj5: %d\n\n", ((Data*)(obj5->data))->test3);

    printf("obj6: %p\n", (void*)obj6->data);
    printf("obj6: %d\n", ((Data*)(obj6->data))->test1);
    printf("obj6: %lx\n", ((Data*)(obj6->data))->test2);
    printf("obj6: %d\n\n", ((Data*)(obj6->data))->test3);

    printf("obj7: %p\n", (void*)obj7->data);
    printf("obj7: %d\n", ((Data*)(obj7->data))->test1);
    printf("obj7: %lx\n", ((Data*)(obj7->data))->test2);
    printf("obj7: %d\n\n", ((Data*)(obj7->data))->test3);

    printf("obj8: %p\n", (void*)obj8->data);
    printf("obj8: %d\n", ((Data2*)(obj8->data))->orderNum);
    printf("obj8: %d\n", ((Data*)((Data2*)(obj8->data))->data)->test1);
    printf("obj8: %d\n", ((Data*)((Data2*)(obj8->data))->data)->test3);
    data.test1 += 1000;
    data.test3 += 82;
    printf("obj8: %d\n", ((Data*)((Data2*)(obj8->data))->data)->test1);
    printf("obj8: %d\n", ((Data*)((Data2*)(obj8->data))->data)->test3);
}
