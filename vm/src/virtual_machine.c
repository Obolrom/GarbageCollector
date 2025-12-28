#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "virtual_machine.h"
#include "config.h"

VM *createVirtualMachine(uint32_t vmHeapSize, uint32_t vmHeapBlockSize, VmMetaspace *vmMetaspace) {
#ifdef VM_LOGS_ENABLED
    printf("VM init...\n");
#endif
    VM* virtualMachine = malloc(sizeof(struct VirtualMachine));
    virtualMachine->heapSize = vmHeapSize;
    virtualMachine->heapBlockSize = vmHeapBlockSize;
    virtualMachine->stackPointer = -1;
    virtualMachine->heap = createVmHeap(virtualMachine);
    virtualMachine->callStack = malloc(sizeof(VmStackFrame));
    virtualMachine->metaspace = vmMetaspace;
#ifdef VM_LOGS_ENABLED
    printf("VM initialized\n");
#endif

    return virtualMachine;
}

void executeBytecode(VM *vm, const int8_t *bytecode, VmDebug *vmDebug) {
    for (int i = 0; i < OPERATION_STACK_SIZE; ++i) {
        vm->stack[i] = -1;
    }
#ifdef VM_INTERPRETER_LOGS_ENABLED
    printf("VM bytecode execution started\n");
#endif

    for (int32_t ip = 0; ;) {
        int8_t instruction = bytecode[ip++];

        if (vmDebug != NULL) {
            // TODO: replace with hashmap logic
            for (int i = 0; i < vmDebug->ipCount; ++i) {
                if (vmDebug->pointers[i] == ip - 1) {
                    if (vmDebug->output == NULL) {
                        vmDebug->output = calloc(vmDebug->ipCount, sizeof(VmValue*));
                    }
                    VmValue* debugValue = malloc(sizeof(VmValue));
                    debugValue->type = TYPE_I8;
                    debugValue->intVal = vm->stack[vm->stackPointer];
                    vmDebug->output[i] = debugValue;
                }
            }
        }

        switch (instruction) {
            case OP_PUSH_I8: {
                vm->stack[++vm->stackPointer] = (int32_t) bytecode[ip++];
                break;
            }
            case OP_PUSH_I16: {
                int8_t left = bytecode[ip++];
                uint8_t right = bytecode[ip++];
                vm->stack[++vm->stackPointer] = (int32_t) ((left << 8) + right);
                break;
            }
            case OP_POP: {
                vm->stack[vm->stackPointer--] = -1;
                break;
            }
            case OP_ADD: {
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t right = vm->stack[vm->stackPointer--];
                vm->stack[++vm->stackPointer] = left + right;
                break;
            }
            case OP_SUB: {
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t right = vm->stack[vm->stackPointer--];
                vm->stack[++vm->stackPointer] = right - left;
                break;
            }
            case OP_MUL: {
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t right = vm->stack[vm->stackPointer--];
                vm->stack[++vm->stackPointer] = right * left;
                break;
            }
            case OP_JMP: {
                int32_t jumpInstructionPointer = (int32_t) bytecode[ip];
                ip = jumpInstructionPointer;
                break;
            }
            case OP_JZ: {
                if (vm->stack[vm->stackPointer] == 0) {
                    ip = (int32_t) bytecode[ip];
                } else {
                    ip++;
                }
                vm->stack[vm->stackPointer--] = -1;
                break;
            }
            case OP_JNZ: {
                if (vm->stack[vm->stackPointer] != 0) {
                    ip = (int32_t) bytecode[ip];
                } else {
                    ip++;
                }
                vm->stack[vm->stackPointer--] = -1;
                break;
            }
            case OP_JEQ: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left == right) {
                    ip = (int32_t) bytecode[ip];
                } else {
                    ip++;
                }
                break;
            }
            case OP_JNE: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left != right) {
                    ip = (int32_t) bytecode[ip];
                } else {
                    ip++;
                }
                break;
            }
            case OP_JLT: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left < right) {
                    ip = (int32_t) bytecode[ip];
                } else {
                    ip++;
                }
                break;
            }
            case OP_JGT: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left > right) {
                    ip = (int32_t) bytecode[ip];
                } else {
                    ip++;
                }
                break;
            }
            case OP_JLE: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left <= right) {
                    ip = (int32_t) bytecode[ip];
                } else {
                    ip++;
                }
                break;
            }
            case OP_JGE: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left <= right) {
                    ip = (int32_t) bytecode[ip];
                } else {
                    ip++;
                }
                break;
            }
            case OP_CMP_EQ: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left == right) {
                    vm->stack[++vm->stackPointer] = 1;
                } else {
                    vm->stack[++vm->stackPointer] = 0;
                }
                break;
            }
            case OP_CMP_NEQ: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left != right) {
                    vm->stack[++vm->stackPointer] = 1;
                } else {
                    vm->stack[++vm->stackPointer] = 0;
                }
                break;
            }
            case OP_CMP_LT: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left < right) {
                    vm->stack[++vm->stackPointer] = 1;
                } else {
                    vm->stack[++vm->stackPointer] = 0;
                }
                break;
            }
            case OP_CMP_GT: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left > right) {
                    vm->stack[++vm->stackPointer] = 1;
                } else {
                    vm->stack[++vm->stackPointer] = 0;
                }
                break;
            }
            case OP_CMP_LTE: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left <= right) {
                    vm->stack[++vm->stackPointer] = 1;
                } else {
                    vm->stack[++vm->stackPointer] = 0;
                }
                break;
            }
            case OP_CMP_GTE: {
                int32_t right = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                int32_t left = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
                if (left >= right) {
                    vm->stack[++vm->stackPointer] = 1;
                } else {
                    vm->stack[++vm->stackPointer] = 0;
                }
                break;
            }
            case OP_CALL: {
                VmStackFrame* prevFrame = vm->callStack;
                int32_t callAddress = (int32_t) bytecode[ip++];
                int32_t argsCount = (int32_t) bytecode[ip++];
                int32_t localsCount = (int32_t) bytecode[ip++];

                VmStackFrame *currentFrame = malloc(sizeof(VmStackFrame));
                vm->callStack = currentFrame;
                currentFrame->prevFrame = prevFrame;
                currentFrame->argsCount = argsCount;
                currentFrame->localsCount = localsCount;
                currentFrame->returnInstructionPointer = ip;
                currentFrame->locals = calloc(argsCount + localsCount, sizeof(VmValue));

                ip = callAddress;
                break;
            }
            case OP_STORE: {
                VmStackFrame* currentFrame = vm->callStack;
                int32_t varIndex = (int32_t) bytecode[ip++];
                int32_t value = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;

                currentFrame->locals[varIndex].type = TYPE_I8;
                currentFrame->locals[varIndex].intVal = value;

                break;
            }
            case OP_LOAD: {
                VmStackFrame* currentFrame = vm->callStack;
                int32_t varIndex = (int32_t) bytecode[ip++];
                vm->stack[++vm->stackPointer] = currentFrame->locals[varIndex].intVal;

                break;
            }
            case OP_RET: {
                VmStackFrame* currentFrame = vm->callStack;
                ip = currentFrame->returnInstructionPointer;
                free(currentFrame->locals);
                vm->callStack = currentFrame->prevFrame;
                if (currentFrame->prevFrame != NULL) {
                    free(currentFrame);
                }

                break;
            }
            case OP_NEW: {
                uint8_t metadataIndexLeft = bytecode[ip++];
                uint8_t metadataIndexRight = bytecode[ip++];
                uint16_t metadataIndex = (metadataIndexLeft << 8) + metadataIndexRight;

                uint8_t localVarIndexLeft = bytecode[ip++];
                uint8_t localVarIndexRight = bytecode[ip++];
                uint16_t localVarIndex = (localVarIndexLeft << 8) + localVarIndexRight;

                VmDataType *dataType = vm->metaspace->types[metadataIndex];
                size_t dataTypeSize = getVmDataTypeSize(dataType);

                HeapObj* object = createObject(vm, dataTypeSize, NULL);

                VmStackFrame* currentFrame = vm->callStack;
                currentFrame->locals[localVarIndex].type = TYPE_OBJECT;
                currentFrame->locals[localVarIndex].objectVal = object;

                break;
            }
            case OP_SET_FIELD: {
                // TODO: refactor with OP_GET_FIELD; a lot of duplicated lines
                uint8_t metadataIndexLeft = bytecode[ip++];
                uint8_t metadataIndexRight = bytecode[ip++];
                uint16_t metadataIndex = (metadataIndexLeft << 8) + metadataIndexRight;

                uint8_t localVarIndexLeft = bytecode[ip++];
                uint8_t localVarIndexRight = bytecode[ip++];
                uint16_t localVarIndex = (localVarIndexLeft << 8) + localVarIndexRight;

                uint8_t fieldIndexLeft = bytecode[ip++];
                uint8_t fieldIndexRight = bytecode[ip++];
                uint16_t fieldVarIndex = (fieldIndexLeft << 8) + fieldIndexRight;

                VmDataType *dataType = vm->metaspace->types[metadataIndex];
                VmDataTypeField *dataTypeField = dataType->fields[fieldVarIndex];

                VmStackFrame* currentFrame = vm->callStack;
                HeapObj *object = currentFrame->locals[localVarIndex].objectVal;

                int32_t offset = 0;
                for (int32_t i = 0; i < fieldVarIndex; ++i) {
                    offset += getVmDataTypeFieldSize(dataType->fields[i]);
                }
                void* regionToWrite = (uint8_t*) object->data + offset;

                size_t fieldSize = getVmDataTypeFieldSize(dataTypeField);

                memcpy(regionToWrite, &vm->stack[vm->stackPointer], fieldSize);

                break;
            }
            case OP_GET_FIELD: {
                uint8_t metadataIndexLeft = bytecode[ip++];
                uint8_t metadataIndexRight = bytecode[ip++];
                uint16_t metadataIndex = (metadataIndexLeft << 8) + metadataIndexRight;

                uint8_t localVarIndexLeft = bytecode[ip++];
                uint8_t localVarIndexRight = bytecode[ip++];
                uint16_t localVarIndex = (localVarIndexLeft << 8) + localVarIndexRight;

                uint8_t fieldIndexLeft = bytecode[ip++];
                uint8_t fieldIndexRight = bytecode[ip++];
                uint16_t fieldVarIndex = (fieldIndexLeft << 8) + fieldIndexRight;

                VmDataType *dataType = vm->metaspace->types[metadataIndex];
                VmDataTypeField *dataTypeField = dataType->fields[fieldVarIndex];

                VmStackFrame* currentFrame = vm->callStack;
                HeapObj *object = currentFrame->locals[localVarIndex].objectVal;

                int32_t offset = 0;
                for (int32_t i = 0; i < fieldVarIndex; ++i) {
                    offset += getVmDataTypeFieldSize(dataType->fields[i]);
                }
                void* regionToRead = (uint8_t*) object->data + offset;
                size_t fieldSize = getVmDataTypeFieldSize(dataTypeField);
                int32_t data;

                int8_t t1 = 0;
                int16_t t2 = 0;
                int32_t t3 = 0;
                switch (dataTypeField->type) {
                    case TYPE_I8:
                        memcpy(&t1, regionToRead, fieldSize);
                        data = (int32_t) t1;
                        break;
                    case TYPE_I16:
                        memcpy(&t2, regionToRead, fieldSize);
                        data = (int32_t) t2;
                        break;
                    case TYPE_I32:
                    case TYPE_OBJECT:
                        memcpy(&t3, regionToRead, fieldSize);
                        data = (int32_t) t3;
                        break;
                }

                vm->stack[++vm->stackPointer] = data;

                break;
            }
            case OP_PRINT: {
                if (vm->stackPointer == -1) {
#ifdef VM_INTERPRETER_LOGS_ENABLED
                    printf("\x1B[31mVM OP_PRINT error, operational stack is empty\x1B[0m\n");
#endif
                }
                int32_t output = vm->stack[vm->stackPointer];
                vm->stack[vm->stackPointer--] = -1;
#ifdef VM_INTERPRETER_STDOUT_ENABLED
                printf("Bytecode stdout: %d\n", output);
#endif
                break;
            }
            case OP_HALT: {
#ifdef VM_INTERPRETER_LOGS_ENABLED
                printf("VM HALT\n");
#endif
                return;
            }
            default: {
#ifdef VM_INTERPRETER_LOGS_ENABLED
                printf("\x1B[31mVM bytecode instruction: %d is not defined\x1B[0m\n", instruction);
#endif
            }
        }
    }
}

VmHeap* createVmHeap(VM* vm) {
#ifdef VM_LOGS_ENABLED
    printf("VM heap init...\n");
#endif
    VmHeap* vmHeap = malloc(sizeof(VmHeap));
    uint32_t blockAmount = vm->heapSize / vm->heapBlockSize;

    vmHeap->memory = malloc(vm->heapSize * sizeof(uint8_t));
    vmHeap->blockAmount = blockAmount;
    vmHeap->blocks = malloc(blockAmount * sizeof(VmHeapMemBlock));
    for (uint32_t i = 0; i < blockAmount; ++i) {
        VmHeapMemBlock* block = malloc(sizeof(VmHeapMemBlock));
        block->position = i;
        block->busyIndicator = BI_GREEN;
        vmHeap->blocks[i] = block;
    }

#ifdef VM_LOGS_ENABLED
    printf("VM heap initialized; Blocks: %d; Block size: %d\n", blockAmount, vm->heapBlockSize);
#endif

    return vmHeap;
}

void destroyVirtualMachine(VM* vm) {
#ifdef VM_LOGS_ENABLED
    printf("VM destroying...\n");
#endif
    destroyVmMetaspace(vm->metaspace);
    destroyVmHeap(vm->heap);
    free(vm->callStack);
    free(vm);

#ifdef VM_LOGS_ENABLED
    printf("VM destroyed\n");
#endif
}

void destroyVmHeap(VmHeap* vmHeap) {
#ifdef VM_LOGS_ENABLED
    printf("VM heap destroying...\n");
#endif
    for (uint32_t i = 0; i < vmHeap->blockAmount; ++i) {
        free(vmHeap->blocks[i]);
    }
    free(vmHeap->blocks);
    free(vmHeap->memory);
    free(vmHeap);

#ifdef VM_LOGS_ENABLED
    printf("VM heap destroyed\n");
#endif
}

void* findFreeBlockAddress(VM* vm, size_t objectSize) {
    VmHeap* heap = vm->heap;
    uint32_t freeMemoryBytes = 0;
    int counter = 0;
    VmHeapMemBlock* freeMemoryStart = NULL;

    for (uint32_t i = 0; i < heap->blockAmount; ++i) {
        VmHeapMemBlock* block = heap->blocks[i];

        if (block->busyIndicator == BI_GREEN) {
            if (counter == 0) {
                freeMemoryStart = block;
            }
            counter++;
            freeMemoryBytes += vm->heapBlockSize;

            if (freeMemoryBytes >= objectSize) {
                for (int j = 0; j < counter; j++) {
                    heap->blocks[i - j]->busyIndicator = BI_RED;
                }
                return (void*)(heap->memory + (freeMemoryStart->position * vm->heapBlockSize));
            }
        }
        else {
            freeMemoryBytes = 0;
            counter = 0;
        }
    }

    return NULL;
}

uint32_t getOccupiedHeapBlocksAmount(VmHeap* heap) {
    uint32_t occupiedBlocks = 0;
    for (uint32_t i = 0; i < heap->blockAmount; ++i) {
        if (heap->blocks[i]->busyIndicator == BI_RED) {
            ++occupiedBlocks;
        }
    }

    return occupiedBlocks;
}

uint32_t getFreeHeapBlocksAmount(VmHeap* heap) {
    return heap->blockAmount - getOccupiedHeapBlocksAmount(heap);
}

size_t getFreeMemoryAmount(VM* vm) {
    uint32_t freeHeapBlocks = vm->heap->blockAmount - getOccupiedHeapBlocksAmount(vm->heap);
    return freeHeapBlocks * vm->heapBlockSize;
}

void printShortHeapStats(VmHeap* heap) {
    printf("--------------------------------\n");
    printf("Blocks (occupied / all): %d / %d\n", getOccupiedHeapBlocksAmount(heap), heap->blockAmount);
    printf("Free blocks: %d\n", getFreeHeapBlocksAmount(heap));
}

void printFullHeapStats(VmHeap* heap) {
    printf("--------------------------------\n");
    printf("Heap blocks dump\n");
    for (uint32_t i = 0; i < heap->blockAmount; ++i) {
        VmHeapMemBlock* block = heap->blocks[i];
        printf("|Block: %zu\t%d\t", block->position, block->busyIndicator);
        if ((i + 1) % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void walkThroughHeap(VM* vm) {
    VmHeap* heap = vm->heap;
    size_t currentBlockIndex = 0;
    size_t actualOccupiedMemory = 0;
    size_t totalBlocksOccupiedMemory = 0;

    while (currentBlockIndex < heap->blockAmount) {
        VmHeapMemBlock* currentBlock = heap->blocks[currentBlockIndex];
        if (currentBlock == NULL) {
            printf("Error: NULL block at index %zu\n", currentBlockIndex);
            break;
        }

        if (currentBlock->busyIndicator == BI_RED) {
            HeapObj* object = (HeapObj*)
                    ((uint8_t *)heap->memory + (currentBlock->position * vm->heapBlockSize));

            if (object->objectSize == 0 || object->objectSize > vm->heapSize) {
                printf("Error: Invalid objectSize at block %zu\n", currentBlockIndex);
                break;
            }

            actualOccupiedMemory += object->objectSize;

            size_t consumedBlocks = (object->objectSize + vm->heapBlockSize - 1) / vm->heapBlockSize;
            totalBlocksOccupiedMemory += consumedBlocks * vm->heapBlockSize;

            printf("Block BI_RED %zu\tObject size: %zu\tBlocks used: %zu\t%p\n",
                   currentBlock->position, object->objectSize, consumedBlocks, object->data);

            currentBlockIndex += consumedBlocks;
        } else {
            printf("Block %zu is free\n", currentBlock->position);
            currentBlockIndex++;
        }
    }

    printf("Total occupied memory: %zu bytes\n", actualOccupiedMemory);
    printf("Total allocated blocks memory: %zu bytes\n", totalBlocksOccupiedMemory);
    printf("Memory fragmentation: %zu bytes\n", totalBlocksOccupiedMemory - actualOccupiedMemory);
}

size_t getUnusedMemoryAmountForTakenHeapBlocks(VM* vm) {
    VmHeap* heap = vm->heap;
    size_t currentBlockIndex = 0;
    size_t actualOccupiedMemory = 0;
    size_t totalBlocksOccupiedMemory = 0;

    while (currentBlockIndex < heap->blockAmount) {
        VmHeapMemBlock* currentBlock = heap->blocks[currentBlockIndex];
        if (currentBlock == NULL) {
            printf("Error: NULL block at index %zu\n", currentBlockIndex);
            break;
        }

        if (currentBlock->busyIndicator == BI_RED) {
            HeapObj* object = (HeapObj*)
                    ((uint8_t *)heap->memory + (currentBlock->position * vm->heapBlockSize));

            if (object->objectSize == 0 || object->objectSize > vm->heapSize) {
                printf("Error: Invalid objectSize at block %zu\n", currentBlockIndex);
                break;
            }

            actualOccupiedMemory += object->objectSize;

            size_t consumedBlocks = (object->objectSize + vm->heapBlockSize - 1) / vm->heapBlockSize;
            totalBlocksOccupiedMemory += consumedBlocks * vm->heapBlockSize;

            currentBlockIndex += consumedBlocks;
        } else {
            currentBlockIndex++;
        }
    }

    return totalBlocksOccupiedMemory - actualOccupiedMemory;
}

VmDebug* createVmDebug(int32_t ipCount) {
    VmDebug *vmDebug = calloc(1, sizeof(VmDebug));
    vmDebug->ipCount = ipCount;
    vmDebug->pointers = malloc(sizeof(int32_t) * ipCount);
    vmDebug->output = calloc(ipCount, sizeof(VmValue*));

    return vmDebug;
}

void destroyVmDebug(VmDebug* vmDebug) {
    if (vmDebug == NULL) {
        return;
    }

    if (vmDebug->output != NULL) {
        for (int i = 0; i < vmDebug->ipCount; ++i) {
            free(vmDebug->output[i]);
        }
        free(vmDebug->output);
    }
    free(vmDebug->pointers);
    free(vmDebug);
}
