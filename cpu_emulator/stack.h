#ifndef STACK_H
#define STACK_H
#define MAXSIZE 10

class Stack
{
    public:
        bool Empty ();
        double Pop ();
        void Print ();
        void Push (double value);
        int Size ();

        Stack ();
        ~Stack ();

        bool Ok ();
        void Dump ();

    private:
        double* data_;
        int size_;
        int capacity_;
};

Stack::Stack ():
    data_ (new double[MAXSIZE]),
    size_ (0),
    capacity_ (MAXSIZE)
    {}

Stack::~Stack ()
{
    delete[] data_;
}

bool Stack::Empty ()
{
    return size_ == 0;
}

double Stack::Pop ()
{
    double value;

    assert (Empty () == 0 && "Stack is already empty!");
    
    value = data_[--size_];
    data_[size_] = 0;
    return value;

}

void Stack::Push (double value)
{
    if (size_ < capacity_)
    {
        data_[size_] = value;
        size_++;
    }
    else
    {
        size_ += 100;   
        data_ = (double*) realloc (data_, sizeof(double) * size_);
    }
}

void Stack::Print ()
{
    printf ("Stack: ");
    for (int i = 0; i < size_; i++)
        printf ("%lg ", data_[i]);

    printf ("\n");
}

int Stack::Size ()
{
    return size_;
}

bool Stack::Ok ()
{
    return (size_>=0 && capacity_ && size_ <= capacity_);
}

void Stack::Dump ()
{
    int i = 0;

    printf ("DUMP:\t");

    if (Ok ())
        printf ("OK\n");
    else
        printf ("ERROR!\n");

    printf ("\tdata =  %p\n", data_);
    printf ("\tsize =  %d\n", size_);
    printf ("\tcapacity = %d\n", capacity_);
    printf ("\n");
    for (i = 0; i < capacity_; i++)
    {
        printf ("\tdata[%d] = %lg [%p]\n", i, data_[i], &data_[i]);
    }
}
#endif