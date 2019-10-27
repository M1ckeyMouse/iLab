#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "commands.h"

enum Regs
{
    AX = 0,
    BX = 1,
    CX = 2,
    DX = 3
};

class CPU
{
    public:
        void Add ();
        void Sub ();
        void Mul ();
        void Div ();
        void Sin ();
        void Cos ();
        void Sqrt ();

        void In ();
        void Out ();

        void Jmp ();
        void Ja ();
        void Jae ();
        void Jb ();
        void Jbe ();
        void Je ();
        void Jne ();
        void Call ();
        void Ret ();
        void Dup ();

        void CPU_Dump();
        void To_ram (FILE* task);
        void Transformer ();


        CPU ();
        ~CPU ();

    private:
        Stack s_;
        Stack ret_;
        double* ram_;
        double* reg_;
        int ip_;
};

CPU::CPU ():
    s_ (),
    ret_ (),
    ram_ (new double[100]),
    reg_ (new double[4]),
    ip_ ()
    {}

CPU::~CPU ()
{
    delete[] ram_;
    delete[] reg_;
}

int main()
{
    CPU proc;
    FILE* task = fopen ("machine_inp", "r");
    
    proc.To_ram (task);
    
    proc.Transformer ();
    proc.CPU_Dump ();
    fclose (task);
    return 0;
}

#include "math_funcs.h"
#include "jumps.h"

void CPU::CPU_Dump ()
{
    printf ("Commands Stack\n");
    s_.Dump ();
    printf ("________________________________\n");
    printf ("Return Stack\n");
    ret_.Dump ();
    printf ("________________________________\n");
    printf ("Registers\n");
    printf ("\trax = %lg [%p]\n", reg_[AX], &reg_[AX]);
    printf ("\trbx = %lg [%p]\n", reg_[BX], &reg_[BX]);
    printf ("\trcx = %lg [%p]\n", reg_[CX], &reg_[CX]);
    printf ("\trdx = %lg [%p]\n", reg_[DX], &reg_[DX]);
}

void CPU::In ()
{
    double a = 0;

    printf ("Type a number from a keyboard: ");
    scanf ("%lg", &a);
    s_.Push (a);
}

void CPU::Out ()
{
    printf ("OUT: %lg\n", s_.Pop());
}

void CPU::To_ram (FILE* task)
{
    for (int i = 0; i < 100; i++)
        fscanf (task, "%lg", &ram_[i]);
    printf ("\n");
}

void CPU::Dup ()
{
    double x = 0;
    x = s_.Pop ();
    s_.Push (x);
    s_.Push (x);
}

void CPU::Transformer ()
{

    while (ram_[ip_] != HLT)
    {
        if (ram_[ip_] == PUSH)
            s_.Push (ram_[++ip_]);

        else if (ram_[ip_] == POP)
            s_.Pop ();
        
        else if (ram_[ip_] == PUSHAX)
            s_.Push (reg_[AX]);
        
        else if (ram_[ip_] == PUSHBX)
            s_.Push (reg_[BX]);
        
        else if (ram_[ip_] == PUSHCX)
            s_.Push (reg_[CX]);
        
        else if (ram_[ip_] == PUSHDX)
            s_.Push (reg_[DX]);

        else if (ram_[ip_] == POPAX)
            reg_[AX] = s_.Pop ();
        
        else if (ram_[ip_] == POPBX)
            reg_[BX] = s_.Pop ();
        
        else if (ram_[ip_] == POPCX)
            reg_[CX] = s_.Pop ();
        
        else if (ram_[ip_] == POPDX)
            reg_[DX] = s_.Pop ();

        else if (ram_[ip_] == ADD)
            Add ();

        else if (ram_[ip_] == SUB)
            Sub ();

        else if (ram_[ip_] == MUL)
            Mul ();

        else if (ram_[ip_] == DIV)
            Div ();

        else if (ram_[ip_] == SIN)
            Sin ();

        else if (ram_[ip_] == COS)
            Cos ();

        else if (ram_[ip_] == SQRT)
            Sqrt ();

        else if (ram_[ip_] == IN)
            In();

        else if (ram_[ip_] == OUT)
            Out();
        
        else if (ram_[ip_] == JMP)
            Jmp ();

        else if (ram_[ip_] == JA)
            Ja ();

        else if (ram_[ip_] == JAE)
            Jae ();

        else if (ram_[ip_] == JB)
            Jb ();

        else if (ram_[ip_] == JBE)
            Jbe ();

        else if (ram_[ip_] == JE)
            Je();

        else if (ram_[ip_] == JNE)
            Jne ();

        else if (ram_[ip_] == CALL)
            Call ();

        else if (ram_[ip_] == RET)
            Ret ();
        
        else if (ram_[ip_] == DUP)
            Dup ();

        ip_++;
    }
}