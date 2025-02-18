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
4. `OP_JEQ addr` - - jump to addr if opStack[top-1] == opStack[top]; pop; pop
5. `CALL addr` - functions call, puts the return address to callStack
6. `RET` - returns execution to caller function

### Operations on variables
1. `LOAD var_idx` - loads variable to callStack
2. `STORE var_idx` - stores top callStack element to variable

### Classes and objects
1. `NEW class_id` - create instance of class_id
2. `GET_FIELD obj, field_id` - get value of object's variable
3. `SET_FIELD obj, field_id, val` - set value to object's variable

### I/O
1. `OP_PRINT` - top callStack element to stdout
2. `READ` - read input from stdin

### VM internal
1. `OP_HALT` - stop virtual machine
