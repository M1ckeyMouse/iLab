#ifndef MATH_FUNCS_H
#define MATH_FUNCS_H

void CPU::Add ()
{
    double a = 0, b = 0, res = 0;

    a = s_.Pop ();
    b = s_.Pop ();
    res = a + b;
    s_.Push (res);
}

void CPU::Sub ()
{
    double a = 0, b = 0, res = 0;
    
    a = s_.Pop ();
    b = s_.Pop ();
    res = a - b;
    s_.Push (res);
}

void CPU::Mul ()
{
    double a = 0, b = 0, res = 0;

    a = s_.Pop ();
    b = s_.Pop ();
    res = a * b;
    s_.Push (res);
}

void CPU::Div ()
{
    double a = 0, b = 0, res = 0;

    a = s_.Pop ();
    b = s_.Pop ();

    assert (b != 0 && "Division by zero!");

    res = a / b;
    s_.Push (res);
}

void CPU::Sin ()
{
    double a = 0, res = 0;

    a = s_.Pop ();
    res = sin (a);
    s_.Push (res); 
}

void CPU::Cos ()
{
    double a = 0, res = 0;

    a = s_.Pop ();
    res = cos (a);
    s_.Push (res);
}

void CPU::Sqrt ()
{
    double a = 0, res = 0;

    a = s_.Pop ();

    assert (a >= 0 && "Square root of a negative number!");

    res = sqrt (a);
    s_.Push (res);
}
#endif