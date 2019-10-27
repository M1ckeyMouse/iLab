#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "commands.h"

class Asm
{
    public:
        void Convert_first_run (FILE* fin);
        void Convert_second_run (FILE* fin, FILE* fout);
        inline void To_machine (double command, FILE* fin, FILE* fout);
        inline void Jumps (double command, FILE* fin, FILE* fout);

        Asm ();
        ~Asm ();
    
    private:
       int* labels_;
       bool* labels_map_;
       char* buf_; 
};

Asm::Asm ():
    labels_ (new int[10]),
    labels_map_ (new bool[10]),
    buf_ (new char[20])
    {}

Asm::~Asm ()
{
    delete[] labels_;
    delete[] labels_map_;
    delete[] buf_;
}

int main()
{
    Asm asmb;

    FILE* fin = fopen ("asm_inp", "r");
    FILE* fout = fopen ("machine_inp", "w");

    asmb.Convert_first_run (fin);
    fclose (fin);
    fin = fopen ("asm_inp", "r");
    asmb.Convert_second_run (fin, fout);

    fclose (fin);
    fclose (fout);
    return 0;
}



void Asm::Convert_first_run (FILE* fin)
{
    int pos = 0;

    while (fscanf (fin, "%s", buf_) != EOF)
    {   
        if (strcmp ("ax", buf_) == 0)
            pos--;

        if (*(buf_ + strlen(buf_) -  1) == ':')
        {
            labels_[atoi(buf_)] = pos;
            labels_map_[atoi(buf_)] = 1;
            pos--;
        }

        else if (strcmp ("jmp", buf_) == 0 || strcmp ("ja", buf_) == 0 || strcmp ("jae", buf_) == 0 ||
                 strcmp ("jb", buf_) == 0 || strcmp ("jbe", buf_) == 0 || strcmp ("je", buf_) == 0 ||
                 strcmp ("jne", buf_) == 0 || strcmp ("call", buf_) == 0)
        {
            fscanf (fin, "%s", buf_);
            pos++;
        }
        pos++;
    }
}


void Asm::Convert_second_run (FILE* fin, FILE* fout)
{
    while (fscanf (fin, "%s", buf_) != EOF)
    {
        if (strcmp ("hlt", buf_) == 0)
            fprintf (fout, "%lg ", (double)HLT);

        else if (strcmp ("push", buf_) == 0)
            To_machine (PUSH, fin, fout);

        else if (strcmp ("pop", buf_) == 0)
            To_machine (POP, fin, fout);

        else if (strcmp ("add", buf_) == 0)
            To_machine (ADD, fin, fout);

        else if (strcmp ("sub", buf_) == 0)
            To_machine (SUB, fin, fout);

        else if (strcmp ("mul", buf_) == 0)
            To_machine (MUL, fin, fout);

        else if (strcmp ("div", buf_) == 0)
            To_machine (DIV, fin, fout);

        else if (strcmp ("sin", buf_) == 0)
            To_machine (SIN, fin, fout);

        else if (strcmp ("cos", buf_) == 0)
            To_machine (COS, fin, fout);

        else if (strcmp ("sqrt", buf_) == 0)
            To_machine (SQRT, fin, fout);

        else if (strcmp ("in", buf_) == 0)
            fprintf (fout, "%lg ", (double)IN);

        else if (strcmp ("out", buf_) == 0)
            fprintf (fout, "%lg ", (double)OUT);
            

        
        else if (strcmp ("jmp", buf_) == 0)
            Jumps (JMP, fin, fout);

        else if (strcmp ("ja", buf_) == 0)
            Jumps (JA, fin, fout);

        else if (strcmp ("jae", buf_) == 0)
            Jumps (JAE, fin, fout);

        else if (strcmp ("jb", buf_) == 0)
            Jumps (JB, fin, fout);

        else if (strcmp ("jbe", buf_) == 0)
            Jumps (JBE, fin, fout);

        else if (strcmp ("je", buf_) == 0)
            Jumps (JE, fin, fout);

        else if (strcmp ("jne", buf_) == 0)
            Jumps (JNE, fin, fout);

        else if (strcmp ("call", buf_) == 0)
            Jumps (CALL, fin, fout);

        else if (strcmp ("ret", buf_) == 0)
            fprintf (fout, "%lg ", (double)RET);
        
        else if (strcmp ("dup", buf_) == 0)
            fprintf (fout, "%lg ", (double)DUP);

        else 
            assert (!"Unknown command");
    }
}

inline void Asm::To_machine (double command, FILE* fin, FILE* fout)
{
    double val = 0;
    fpos_t ptr;

    if (command == PUSH)
    {
        fscanf (fin, "%s", buf_);

        if (strcmp ("ax", buf_) == 0)
        {
            command = PUSHAX;
            fscanf (fin, "%s", buf_);    
        }
        else if (strcmp ("bx", buf_) == 0)
        {
            command = PUSHBX;
            fscanf (fin, "%s", buf_);
        }
        else if (strcmp ("cx", buf_) == 0)
        {
            command = PUSHCX;
            fscanf (fin, "%s", buf_);
        }
        else if (strcmp ("dx", buf_) == 0)
        {
            command = PUSHDX;
            fscanf (fin, "%s", buf_);
        }
        else
        {
            fprintf (fout, "%lg ", command);
            val = atoi (buf_);
            fprintf (fout, "%lg ", val);
        }
        
    }
    else if (command == POP)
    {
        fgetpos (fin, &ptr);
        fscanf (fin, "%s", buf_);

        if (strcmp ("ax", buf_) == 0)
            command = POPAX;

        else if (strcmp ("bx", buf_) == 0)
            command = POPBX;

        else if (strcmp ("cx", buf_) == 0)
            command = POPCX;

        else if (strcmp ("dx", buf_) == 0)
            command = POPDX;
        else
            fsetpos (fin, &ptr);
            
        fprintf (fout, "%lg ", command);
    }
    else
        fprintf (fout, "%lg ", command);

}

inline void Asm::Jumps (double command, FILE* fin, FILE* fout)
{
    int lbl;

    fprintf (fout, "%lg ", command);
    fscanf (fin, "%s", buf_);
    lbl = atoi (buf_);

    assert (labels_map_[lbl] != 0 && "Jump on a nonexistent label!");

    fprintf (fout, "%lg ", (double)labels_[lbl]);
}