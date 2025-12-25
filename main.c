#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "virtual_machine.h"

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

void test1(VM* vm);

void testSuite();
int testCase11();
int testCase12();
int testCase13();
int testCase14();
int testCase15();
int testCase16();
int testCase17();
int testCase18();
int testCase19();
int testCase20();
int testCase21();
int testCase22();
int testCase23();
int testCase24();
int testCase25();

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
    testCase11();
    testCase12();
    testCase13();
    testCase14();
    testCase15();
    testCase16();
    testCase17();
    testCase18();
    testCase19();
    testCase20();
    testCase21();
    testCase22();
    testCase23();
    testCase24();
    testCase25();
}

int testCase11_helperFunction_passed = 1;
void testCase11_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 10) {
        testCase11_helperFunction_passed = 0;
    }
    if (instructionPointer == 4 && stackTopValue != 40) {
        testCase11_helperFunction_passed = 0;
    }
    if (instructionPointer == 5 && stackTopValue != 50) {
        testCase11_helperFunction_passed = 0;
    }
    if (instructionPointer == 6) {
        testCase11_helperFunction_passed = 0;
    }
    if (instructionPointer == 7) {
        testCase11_helperFunction_passed = 0;
    }
    if (instructionPointer == 8) {
        testCase11_helperFunction_passed = 0;
    }
    if (instructionPointer == 9) {
        testCase11_helperFunction_passed = 0;
    }
    if (instructionPointer == 10 && stackTopValue != 50) {
        testCase11_helperFunction_passed = 0;
    }
}

int testCase11() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

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

    executeBytecode(vm, bytecode, NULL, testCase11_helperFunction);

    passed = testCase11_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase11' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase11' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase12_helperFunction_passed = 1;
void testCase12_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 5 && stackTopValue != 50) {
        testCase12_helperFunction_passed = 0;
    }
    if (instructionPointer == 8 && stackTopValue != 30) {
        testCase12_helperFunction_passed = 0;
    }
}

int testCase12() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

    int32_t bytecode[] = {
            OP_PUSH, 10,
            OP_PUSH, 40,
            OP_ADD,
            OP_PUSH, 20,
            OP_SUB,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, NULL, testCase12_helperFunction);

    passed = testCase12_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase12' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase12' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase13_helperFunction_passed = 1;
void testCase13_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 7 && stackTopValue != 0) {
        testCase13_helperFunction_passed = 0;
    }
    if (instructionPointer == 17 && stackTopValue != 21) {
        testCase13_helperFunction_passed = 0;
    }
}

int testCase13() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

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

    executeBytecode(vm, bytecode, NULL, testCase13_helperFunction);

    passed = testCase13_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase13' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase13' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase14_helperFunction_passed = 1;
void testCase14_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 7 && stackTopValue != 9) {
        testCase14_helperFunction_passed = 0;
    }
    if (instructionPointer == 17 && stackTopValue != 21) {
        testCase14_helperFunction_passed = 0;
    }
}

int testCase14() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

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

    executeBytecode(vm, bytecode, NULL, testCase14_helperFunction);

    passed = testCase14_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase14' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase14' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase15_helperFunction_passed = 1;
void testCase15_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 15) {
        testCase15_helperFunction_passed = 0;
    }
    if (instructionPointer == 4 && stackTopValue != 15) {
        testCase15_helperFunction_passed = 0;
    }
    if (instructionPointer == 12 && stackTopValue != 77) {
        testCase15_helperFunction_passed = 0;
    }
}

int testCase15() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

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

    executeBytecode(vm, bytecode, NULL, testCase15_helperFunction);

    passed = testCase15_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase15' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase15' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase16_helperFunction_passed = 1;
void testCase16_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 15) {
        testCase16_helperFunction_passed = 0;
    }
    if (instructionPointer == 4 && stackTopValue != 11) {
        testCase16_helperFunction_passed = 0;
    }
    if (instructionPointer == 8 && stackTopValue != 33) {
        testCase16_helperFunction_passed = 0;
    }
}

int testCase16() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

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

    executeBytecode(vm, bytecode, NULL, testCase16_helperFunction);

    passed = testCase16_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase16' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase16' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase17_helperFunction_passed = 1;
void testCase17_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 21) {
        testCase17_helperFunction_passed = 0;
    }
    if (instructionPointer == 4 && stackTopValue != -10) {
        testCase17_helperFunction_passed = 0;
    }
    if (instructionPointer == 6 && stackTopValue != 10) {
        testCase17_helperFunction_passed = 0;
    }
    if (instructionPointer == 7 && stackTopValue != 0) {
        testCase17_helperFunction_passed = 0;
    }
    if (instructionPointer == 9 && stackTopValue != 21) {
        testCase17_helperFunction_passed = 0;
    }
    if (instructionPointer == 11 && stackTopValue != 100) {
        testCase17_helperFunction_passed = 0;
    }
    if (instructionPointer == 13 && stackTopValue != 200) {
        testCase17_helperFunction_passed = 0;
    }
    if (instructionPointer == 15 && stackTopValue != 300) {
        testCase17_helperFunction_passed = 0;
    }
}

int testCase17() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

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

    executeBytecode(vm, bytecode, NULL, testCase17_helperFunction);

    passed = testCase17_helperFunction_passed;
    for (int i = 1; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stack[0] != 21) {
        passed = 0;
    }
    if (vm->stackPointer != 0) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase17' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase17' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase18_helperFunction_passed = 1;
void testCase18_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 15) {
        testCase18_helperFunction_passed = 0;
    }
    if (instructionPointer == 4 && stackTopValue != 11) {
        testCase18_helperFunction_passed = 0;
    }
    if (instructionPointer == 14 && stackTopValue != 77) {
        testCase18_helperFunction_passed = 0;
    }
}

int testCase18() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

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

    executeBytecode(vm, bytecode, NULL, testCase18_helperFunction);

    passed = testCase18_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase18' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase18' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase19_helperFunction_passed = 1;
void testCase19_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 5) {
        testCase19_helperFunction_passed = 0;
    }
    if (instructionPointer == 4 && stackTopValue != 7) {
        testCase19_helperFunction_passed = 0;
    }
    if (instructionPointer == 14 && stackTopValue != 77) {
        testCase19_helperFunction_passed = 0;
    }
}

int testCase19() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

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

    executeBytecode(vm, bytecode, NULL, testCase19_helperFunction);

    passed = testCase19_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase19' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase19' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase20_helperFunction_passed = 1;
void testCase20_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 5) {
        testCase20_helperFunction_passed = 0;
    }
    if (instructionPointer == 4 && stackTopValue != 5) {
        testCase20_helperFunction_passed = 0;
    }
    if (instructionPointer == 5 && stackTopValue != 1) {
        testCase20_helperFunction_passed = 0;
    }
}

int testCase20() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

    // should print 1 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 5,
            OP_PUSH, 5,
            OP_CMP_EQ,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, NULL, testCase20_helperFunction);

    passed = testCase20_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase20' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase20' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase21_helperFunction_passed = 1;
void testCase21_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 5) {
        testCase21_helperFunction_passed = 0;
    }
    if (instructionPointer == 4 && stackTopValue != 5) {
        testCase21_helperFunction_passed = 0;
    }
    if (instructionPointer == 5 && stackTopValue != 0) {
        testCase21_helperFunction_passed = 0;
    }
}

int testCase21() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

    // should print 0 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 5,
            OP_PUSH, 5,
            OP_CMP_NEQ,
            OP_PRINT,
            OP_HALT,
    };

    executeBytecode(vm, bytecode, NULL, testCase21_helperFunction);

    passed = testCase21_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase21' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase21' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase22_helperFunction_passed = 1;
void testCase22_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 2 && stackTopValue != 5) {
        testCase22_helperFunction_passed = 0;
    }
    if (instructionPointer == 8 && stackTopValue != 15) {
        testCase22_helperFunction_passed = 0;
    }
    if (instructionPointer == 19 && stackTopValue != 15) {
        testCase22_helperFunction_passed = 0;
    }
}

int testCase22() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

    // should print 15 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 5,
            OP_PUSH, 10,
            OP_CALL, 10, 2, 0,
            OP_PRINT,
            OP_HALT,

            // function
            OP_STORE, 0,
            OP_STORE, 1,
            OP_LOAD, 0,
            OP_LOAD, 1,
            OP_ADD,
            OP_RET
    };

    executeBytecode(vm, bytecode, NULL, testCase22_helperFunction);

    passed = testCase22_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }
    if (vm->callStack == NULL) {
        passed = 0;
    }
    if (vm->callStack->prevFrame != NULL) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase22' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase22' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase23_helperFunction_passed = 1;
void testCase23_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 8 && stackTopValue != 7) {
        testCase23_helperFunction_passed = 0;
    }
    if (instructionPointer == 19 && stackTopValue != 15) {
        testCase23_helperFunction_passed = 0;
    }
    if (instructionPointer == 30 && stackTopValue != 7) {
        testCase23_helperFunction_passed = 0;
    }
}

int testCase23() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

    // should print 7 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 5,
            OP_PUSH, 10,
            OP_CALL, 10, 2, 0,
            OP_PRINT,
            OP_HALT,

            // function 1
            OP_STORE, 0,
            OP_STORE, 1,
            OP_LOAD, 0,
            OP_LOAD, 1,
            OP_ADD,
            OP_CALL, 22, 1,
            OP_RET,

            // function 2
            OP_STORE, 0,
            OP_LOAD, 0,
            OP_PUSH, 8,
            OP_SUB,
            OP_RET,
    };

    executeBytecode(vm, bytecode, NULL, testCase23_helperFunction);

    passed = testCase23_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }
    if (vm->callStack == NULL) {
        passed = 0;
    }
    if (vm->callStack->prevFrame != NULL) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase23' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase23' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase24_helperFunction_passed = 1;
void testCase24_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 8 && stackTopValue != 100) {
        testCase24_helperFunction_passed = 0;
    }
    if (instructionPointer == 39 && stackTopValue != 20) {
        testCase24_helperFunction_passed = 0;
    }
    if (instructionPointer == 41 && stackTopValue != 100) {
        testCase24_helperFunction_passed = 0;
    }
}

int testCase24() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

    // should print 20 and 100 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    int32_t bytecode[] = {
            OP_PUSH, 0, // sum
            OP_PUSH, 0, // i
            OP_CALL, 10, 0, 2,
            OP_PRINT,
            OP_HALT,

            // function
            OP_STORE, 0, // sum
            OP_STORE, 1, // i
            OP_LOAD, 1,
            OP_PUSH, 20,
            OP_CMP_LT,
            OP_JZ, 37,   // jump to end of loop
            OP_LOAD, 0,
            OP_PUSH, 5,
            OP_ADD,
            OP_STORE, 0,
            OP_LOAD, 1,
            OP_PUSH, 1,
            OP_ADD,
            OP_STORE, 1,
            OP_JMP, 14,
            OP_LOAD, 1,
            OP_PRINT,    // print `i`
            OP_LOAD, 0,  // put sum to op. stack
            OP_RET
    };

    executeBytecode(vm, bytecode, NULL, testCase24_helperFunction);

    passed = testCase24_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }
    if (vm->callStack == NULL) {
        passed = 0;
    }
    if (vm->callStack->prevFrame != NULL) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase24' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase24' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

    return passed;
}

int testCase25_helperFunction_passed = 1;
void testCase25_helperFunction(int32_t instructionPointer, int32_t stackTopValue) {
    if (instructionPointer == 6 && stackTopValue != 5040) {
        testCase25_helperFunction_passed = 0;
    }
}

int testCase25() {
    int passed = 1;
    VM* vm = createVirtualMachine(240, 48);

    // should print 5040 in stdout if VM_INTERPRETER_STDOUT_ENABLED
    /*
        int factorial(int n) {
            if (n == 1) {
                return 1;
            }
            return n * factorial(n - 1);
        }
     */
    int32_t bytecode[] = {
            OP_PUSH, 7,
            OP_CALL, 8, 1, 0,
            OP_PRINT,
            OP_HALT,

            // factorial function
            OP_STORE, 0,
            OP_LOAD, 0,
            OP_PUSH, 1,
            OP_CMP_EQ,
            OP_JNZ, 30,

            OP_LOAD, 0,
            OP_PUSH, 1,
            OP_SUB,
            OP_CALL, 8, 1, 0, // recursion call
            OP_LOAD, 0,
            OP_MUL,
            OP_RET,

            // base case
            OP_PUSH, 1,
            OP_RET
    };

    executeBytecode(vm, bytecode, NULL, testCase25_helperFunction);

    passed = testCase25_helperFunction_passed;
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        if (vm->stack[i] != -1) {
            passed = 0;
        }
    }
    if (vm->stackPointer != -1) {
        passed = 0;
    }
    if (vm->callStack == NULL) {
        passed = 0;
    }
    if (vm->callStack->prevFrame != NULL) {
        passed = 0;
    }

#ifdef TEST_OUTPUT_ENABLED
    if (passed == 1) {
        printf(GREEN "Test 'testCase25' passed\n" RESET);
    }
    else {
        printf(RED "Test 'testCase25' FAILED\n" RESET);
    }
#endif

    destroyVirtualMachine(vm);

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
