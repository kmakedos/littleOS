## ASSEMBLY TUTORIAL

### Assembly program design

* data section: Used for declaring initialized data or constants. Does not change at runtime.
* bss section: Section for variables
* text section: Code section

An assembly program at minimum shoud have:
```
segment .text
    global _start
    _start:
       mov eax,1
       int 80
```

### Memory Segments 
A model of memory segmentation is used to divide memory in groups of independent segments referenced by pointers
located in segment registers.
Each segment contains a specific type of data.

* Data segment: It is represented by .data and .bss section. The .data section is used to declare memory region where
data elements are stored for the program. This section cannot be expanded after data elements are declared, and it remains static
throughout the program. The .bss section contains buffers for data to be declared later in the program. It is zero-filled.
* Code segment: It is represented by .text section. This defines an area in memory that stores instruction codes.
* Stack: This segment contains data values passed to functions and procedures.


### Registers
There are ten 32-bit and six 16-bit processor registers in IA-32. (TODO: add 64bit info)

* General Registers
* Control Registers
* Segment Registers

General Registers can further be divided into:

- Data Registers
- Pointer Registers
- Index Registers


#### Data Registers

Four 32 bit data registers are used for arithmetic, logical and other operations.
```
32 bit  |   16 bit  |   8 bit   |   Usage
---------------------------------------------------
EAX     |   AX      |   AH/L      |   Accumulator   :   Primary Accumulator, I/O and most arithmetic
EBX     |   BX      |   BH/L      |   Base          :   Base Register for indexed addressing
ECX     |   CX      |   CH/L      |   Counter       :   Count Register, loop counter
EDX     |   DX      |   DH/L      |   Datao         :   I/O, also for large multiply and divide operations
```

#### Pointer Registers
* Instruction Pointer (IP) - This 16-bit register stores the offset addresss of the next instruction to be executed. In association with
CS register (CS:IP) gives the complete address of the current instruction in the code segment.
* Stack Pointer (SP) - This 16 bit register provides the offset value within the program stack. In association with SS register refers to current
position of data or address within the program stack.
* Base Pointer (BP) - This 16-bit register helps in referencing the parameter variables passed to a subroutine. The address in SS register is combined with
offset in BP to get the location of the parameter. BP can also be combined with DI/SI as base register for special addressing.

#### Index Registers
The 32-bit index registers, ESI and EDI and their 16-bit rightmost portions, SI and DI are used for indexed addressing and sometimes used in addition and subtraction.

* Source Index (SI): Used as source index for string operations
* Destination Index(DI): Used as destination index for string operations


#### Control Registers
Instruction Pointer (IP) and Flags Register are considered control registers.
When comparisons or other mathematical calculations change the status of flags of Flags Register:

- Overflow Flag (OF) : Overflow of high bit of data
- Direction Flag (DF) : 0 left-to-right, 1 right-to-left
- Interrupt Flag (IF): Enables interrupts when is 1
- Trap Flag (TF): Enables debug mode setting processor in single-step mode
- Sign Flag (SF): Positive == 0, Negative == 1
- Zero Flag (ZF): Nonzero == 0, Zero == 1
- Auxiliary Carry Flag (AF): It contains the carry from bit 3 to 4. It is used when a 1-byte arithmetic operation causes a carry from bit-3 to bit-4.
- Parity Flag (PF): It indicates total number of bites in the result from an arithmetic operation. Even number == 0, Odd number == 1
- Carry Flag (CF): It contains the carry 0 or 1 from high order bit operation. It also contains the bit from a shift or rotate operation

Flags Register
Flag:                        O   D  I   T   S   Z       A       P       C
Bit no:     15  14  13  12  11  10  9   8   7   6   5   4   3   2   1   0


#### Segment Registers
Segments are specific areas defined in a program for containing data, code and stack.
- Code Segment: All instructions to be executed. CS register stores the starting address of code segment.
- Data Segment: All data, constants and work areas. DS registers stores starting address of data segment.
- Stack Segment: It contains data and return addresses of procedures or subroutines. It is implemented as a 'stack' data structure. 
SS register stores the startinf address of the stack.
- Extra Segment: ES register, additional register for program
- FS, GS: Additional registers.


### Linux System Calls
Steps to use a Linux System Call:
- Put the system call number in the EAX
- Store the arguments to EBX, ECX
- Call relevant interrupt (80h)
- Result is usually in EAX

Consecutive arguments can be stored in EBX,ECX,EDX,ESI,EDI,EBP.

All system calls are listed in /usr/include/asm/unistd.h and their numbers.


### Addressing modes
Most assembly instructions need operands to be processed. An operand address provides the lcoatio where data to be processed is stored.
When an instruction requires two operands, first operand is the destination and second operand is the source.
Source contains either the data to be delivered (immediate addressing) or the address (in register or memory) of the data.
Three modes of addressing are available:
* Register addressing
* Immediate addressing
* Memory addressing

#### Register addressing
A register contains the operand.
MOV DX,TAX_RATE
MOV AX,BX

#### Immediate addressing
An immediate addressing has a constant value or expression:
BYTE_VALUE DB 150
ADD BYTE_VALUE,AX
WORD_VALUE DW 300
MOV AX,45H

#### Direct Memory addressing
When operands are specified in memory addressing mode, direct access to main memory, usually to data segment is required.
This way of addressing is slower.

#### Direct-Offset addressing
This addressing mode uses arithmetic operators to modify an address.
Example:
BYTE_TABLE DB 13,15,22

MOV CL,BYTE_TABLE[2]        ; Gets 3rd element of BYTE_TABLE
MOV CL,BYTE_TABLE + 2       ; Gets 3rd element of BYTE_TABLE

#### InDirect Memory Addressing
This addressing mode utilizes the Segment:Offset addressing.
The Base Registers (EBX,EBP) and Index Registers (DI,SI) coded within square brackets for memory references are used.
Indirect addressing is generally used for variables containing several elements like arrays.
Example:

MY_TABLE TIMES 10 DW 0      ; Allocation 10 words 2bytes each initialized to 0
MOV EBX,[MY_TABLE]          ; Effective address of MY_TABLE In EBX
MOV [EBX],110               ; MY_TABLE[0] = 110
ADD EBX,2                   ; EBX = EBX + 2

#### MOV Instruction
MOV instruction copies values from source to destination. Syntax:
MOV DEST,SRC
Forms:
    - register,register
    - register,immediate
    - memory,immediate
    - register,memory
    - memory,register

Notes:
    - Both operands must be same size
    - Source is unaffected

MOV [EBX],123               ; MY_TABLE[1] = 123


### Allocating Storage Space for Initialized Data
Syntax for storage allocation for initialized data is:
```
[variable-name]     define-directive    initial-value   [,initial-value]
```
Define directives are:

Directive       Purpose             Storage Space
----------------------------------------------------
DB              Define Byte         allocates 1 byte
DW              Define Word         allocates 2 bytes
DD              Define DoubleWord   allocates 4 bytes
DQ              Define QuadWord     allocates 8 bytes
DT              Define Ten Bytes    allocates 10 bytes

### Allocating Storage Space for Uninitialized Data
Syntax for storage allocation for uninitialized data is similar:
```
[variable-name]     define-directive    initial-value   [,initial-value]
```
Define directives are:

Directive       Purpose             Storage Space
----------------------------------------------------
RESB              Define Byte         allocates 1 byte
RESW              Define Word         allocates 2 bytes
RESD              Define DoubleWord   allocates 4 bytes
RESQ              Define QuadWord     allocates 8 bytes
REST              Define Ten Bytes    allocates 10 bytes


### Multiple Initializations

Array named matrix with 10 values zeroed:

matrix  TIMES 10    dw 0


### Arithmetic instructions

#### INC,DEC
Increase or Decrease operand

#### ADD,SUB
Add or subtract between
- Register - register
- Memory - register
- Resigter - memory
- Register - constant
- Memory - constant
No memory-memory operands can be added or subtracted

#### 

