# YAU - 8 bit Assembly Language

## Binary Format
    0bXXXXYYYY 
    X - Opcode
    Y - Argument

## Registers
    A, B, Z, SP, IP
    A, B = General Purpose 
    C    = Comparison Flag
    SP   = Stack Pointer
    IP   = Instruction Pointer

    All registers are 8 bit


## Opcodes

    STOP   = 00000000 (0x00) 
    - Stops the program execution
    MOVA X = 0001XXXX (0x1X)
    - Move a value into register A
    MOVB X = 0010XXXX (0x2X)
    - Move a value into register B
    PUSHA  = 00110000 (0x30)
    - Push the value in register A into the stack
    PUSHB  = 01000000 (0x40)
    - Push the value in register B into the stack
    POPA   = 01010000 (0x50)
    - Pop the value in the stack to register A
    POPB   = 01100000 (0x60)
    - Pop the value in the stack to register B
    INCA   = 01110000 (0x70)
    - Increment the value in register A by 1
    INCB   = 10000000 (0x80)
    - Increment the value in register B by 1
    CMPAB  = 10001111 (0x8F)
    - Compare the value in register A with the value in register B
    CMPA X = 1001XXXX (0x9X)
    - Compare the value in register A with the argument
    CMPB X = 1010XXXX (0xAX)
    - Compare the value in register B with the argument
    JE X   = 1011XXXX (0xBX)
    - Jump relatively to the argument (-8; 7) if compared values are equal 
    JNE X  = 1100XXXX (0xCX)
    - Jump relatively to the argument (-8; 7) if compared values are not equal
    OUTA   = 11010000 (0xD0)
    - Output the value in register A
    OUTB   = 11100000 (0xE0)
    - Output the value in register B
    NOP    = 11110000 (0xF0)
    - No operation
    DMP    = 11111111 (0xFF)
    - Dump the contents of the registers


## Misc.
    # = Begin a comment (ends with the end-of-line)