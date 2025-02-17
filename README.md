## Operation codes for virtual machine

### Arithmetic operations
1. `ADD` - addition. stack[top-1] = stack[top-1] + stack[top], pop stack[top]
2. `SUB` - subtraction
3. `MUL` - multiplication
4. `DIV` - division

### Stack operations
1. `PUSH val` - put val (number) to stack
2. `POP` - remove top element from stack
3. `DUP` - duplicate a top element

### Conditions & loops operations
1. `JMP addr` - unconditional jump
2. `JZ addr` - jump to addr if stack[top] == 0
3. `JNS addr` - jump to addr if stack[top] != 0
4. `CALL addr` - functions call, puts the return address to stack
5. `RET` - returns execution to caller function

### Operations on variables
1. `LOAD var_idx` - loads variable to stack
2. `STORE var_idx` - stores top stack element to variable

### Classes and objects
1. `NEW class_id` - create instance of class_id
2. `GET_FIELD obj, field_id` - get value of object's variable
3. `SET_FIELD obj, field_id, val` - set value to object's variable

### I/O
1. `PRINT` - top stack element to stdout
2. `READ` - read input from stdin
