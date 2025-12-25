## Operation codes for virtual machine

### Arithmetic operations
1. `OP_ADD` - addition. opStack[top-1] = opStack[top-1] + opStack[top], pop opStack[top]
2. `OP_SUB` - subtraction
3. `MUL` - multiplication
4. `DIV` - division

### Stack operations
1. `OP_PUSH val` - put val (number) to callStack
2. `OP_POP` - remove top element from callStack
3. `OP_DUP` - duplicate a top element

### Conditions & loops operations
1. `OP_JMP addr` - unconditional jump
2. `OP_JZ addr` - jump to addr if opStack[top] == 0
3. `OP_JNZ addr` - jump to addr if opStack[top] != 0
4. `OP_JEQ addr` - jump to addr if opStack[top-1] == opStack[top]; pop; pop
5. `OP_JNE addr` - jump to addr if opStack[top-1] != opStack[top]; pop; pop
6. `OP_JLT addr` - jump to addr if opStack[top-1] < opStack[top]; pop; pop
7. `OP_JGT addr` - jump to addr if opStack[top-1] > opStack[top]; pop; pop
8. `OP_JLE addr` - jump to addr if opStack[top-1] <= opStack[top]; pop; pop
9. `OP_JGE addr` - jump to addr if opStack[top-1] >= opStack[top]; pop; pop
10. `OP_CMP_EQ` - opStack[top-1] == opStack[top]; pop; pop; push
11. `OP_CMP_NEQ` - opStack[top-1] != opStack[top]; pop; pop; push
12. `OP_CMP_LT` - opStack[top-1] < opStack[top]; pop; pop; push
13. `OP_CMP_GT` - opStack[top-1] > opStack[top]; pop; pop; push
14. `OP_CMP_LTE` - opStack[top-1] <= opStack[top]; pop; pop; push
15. `OP_CMP_GTE` - opStack[top-1] >= opStack[top]; pop; pop; push
16. `OP_CALL addr args_count localsCount` - functions call, puts the return address to callStack; copies arguments from operation stack to locals of stack frame
17. `OP_RET` - destroys current call stack frame and returns to the previous one

### Operations on variables
1. `LOAD var_idx` - move call stack frame locals[var_idx] to opStack[top]
2. `STORE var_idx` - move opStack[top] to call stack frame locals[var_idx]

### Classes and objects
1. `NEW class_id` - create instance of class_id
2. `GET_FIELD obj, field_id` - get locals of object's variable
3. `SET_FIELD obj, field_id, val` - set locals to object's variable

### I/O
1. `OP_PRINT` - top callStack element to stdout
2. `READ` - read input from stdin

### VM internal
1. `OP_HALT` - stop virtual machine
