#ifndef COMMANDS_H
#define COMMANDS_H

enum Commands_CPU
{
    HLT = 0,
    PUSH = 1,
    POP = 2,
    PUSHAX = 3,
    PUSHBX = 4,
    PUSHCX = 5,
    PUSHDX = 6,
    POPAX = 7,
    POPBX = 8,
    POPCX = 9,
    POPDX = 10,
    ADD = 11,
    SUB = 12,
    MUL = 13,
    DIV = 14,
    SIN = 15,
    COS = 16,
    SQRT = 17,
    IN = 18,
    OUT = 19
};

enum Commands_Jumps
{
    JMP = 20,
    JA = 21,
    JAE = 22,
    JB = 23,
    JBE = 24,
    JE = 25,
    JNE = 26,
    CALL = 27,
    RET = 28
};

enum Other_Commands
{
    DUP = 29
};

#endif