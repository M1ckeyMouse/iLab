#ifndef JUMPS_H
#define JUMPS_H

void CPU::Jmp ()
{
    ip_ = ram_[++ip_];
    ip_--;
}

void CPU::Ja ()
{
    double x = 0, y = 0;

    x = s_.Pop ();
    y = s_.Pop ();

    if (x > y)
        Jmp ();
    else
        ip_++;

    s_.Push (y);
    s_.Push (x);
}

void CPU::Jae ()
{
    double x = 0, y = 0;

    x = s_.Pop ();
    y = s_.Pop ();

    if (x >= y)
        Jmp ();
    else
        ip_++;

    s_.Push (y);
    s_.Push (x);
}

void CPU::Jb ()
{
    double x = 0, y = 0;

    x = s_.Pop ();
    y = s_.Pop ();

    if (x < y)
        Jmp ();
    else
        ip_++;

    s_.Push (y);
    s_.Push (x);
}

void CPU::Jbe ()
{
    double x = 0, y = 0;

    x = s_.Pop ();
    y = s_.Pop ();
    
    if (x <= y)
        Jmp ();
    else
        ip_++;

   s_.Push (y);
   s_.Push (x);
}

void CPU::Je ()
{
    double x = 0, y = 0;

    x = s_.Pop ();
    y = s_.Pop ();

    if (x == y)
        Jmp ();
    else
        ip_++;

    s_.Push (y);
    s_.Push (x);
}

void CPU::Jne ()
{
    double x = 0, y = 0;

    x = s_.Pop ();
    y = s_.Pop ();

    if (x != y)
        Jmp ();
    else
        ip_++;

    s_.Push (y);
    s_.Push (x);
}

void CPU::Call ()
{
    ret_.Push (ip_ + 1);
    Jmp ();
}

void CPU::Ret ()
{
    if (ret_.Empty () == 0)
        ip_ = ret_.Pop();
}
#endif