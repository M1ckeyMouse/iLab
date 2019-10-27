#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXSIZE 50

class Leaf
{
    public:
        void treeWrite (FILE* fout);
        void treeCreate (char* data);
        void leafReg_l (Leaf* leaf);
        void leafReg_r (Leaf* leaf);
        void leafAdd ();
        void treeRun ();

        Leaf ();
        ~Leaf ();

    private:
        char* val_;
        Leaf* leftChild_;
        Leaf* rightChild_;
};

Leaf::Leaf ():
    val_ (new char[MAXSIZE]),
    leftChild_ (NULL),
    rightChild_ (NULL)
    {}

Leaf::~Leaf ()
{
    delete[] val_;
}

char* treeRead (FILE* fin);

int main()
{
    Leaf* root (new Leaf[1]);
    char* ans (new char[4]);
    char* data = NULL;
    size_t game = 1;

    FILE* fin = fopen ("tree_database", "r");

    data = treeRead (fin);
    root->treeCreate (data);
    printf ("Hello! This is an algoritm that can guess your smth, here is my first question:\n");
    while (game)
    {
        root->treeRun ();

        printf ("Do you want to play again?\nYour answer: ");
        scanf ("%s", ans);
        if (strcmp ("no", ans) == 0)
        {
            game = 0;
            printf ("\nSee you next time!\n");
        }
    }
    fin = fopen ("tree_database", "w+");
    root->treeWrite (fin);

    fclose (fin);
    delete[] ans;
    return 0;
}

void Leaf::leafReg_l (Leaf* leaf)
{
    leftChild_ = leaf;
}

void Leaf::leafReg_r (Leaf* leaf)
{
    rightChild_ = leaf;
}


void Leaf::treeWrite (FILE* fout)
{   
    fprintf (fout, "( \"%s\" ", val_);

    if (leftChild_ != NULL)
        leftChild_ -> treeWrite (fout);
    else
        fprintf (fout, "N ");

    if (rightChild_ != NULL)
        rightChild_ -> treeWrite (fout);
    else
        fprintf (fout, "N ");

    fprintf (fout, ") ");
}

char* treeRead (FILE* fin)
{
    int file_tail;

    fseek (fin, 0, SEEK_END);
    file_tail = ftell (fin);
    char* data (new char[file_tail]);

    rewind (fin);

    fgets (data, file_tail, fin);

    return data;
}

void Leaf::treeRun ()
{
    char* ans (new char[4]);
    printf ("\n%s\nYour answer: ", val_);
    scanf ("%s", ans);

    if (strcmp ("yes", ans) == 0)
    {
        if (leftChild_ != NULL)
            leftChild_->treeRun ();
        else
        {
            printf ("\nIt was easy!\n\n");
        }
    }
    else if (strcmp ("no", ans) == 0)
    {
        if (rightChild_ != NULL)
            rightChild_->treeRun ();
        else
            leafAdd ();
    }
    else
    {
        printf ("\nThe answer can be only 'yes' or 'no'!\n");
        printf ("Please try again!\n");
        treeRun();
    }
    delete[] ans;
}

void Leaf::leafAdd ()
{
    int len = 0;
    char* buf (new char[MAXSIZE]);
    char* buf_left (new char[MAXSIZE]);

    Leaf* right = (new Leaf[1]);
    Leaf* left = (new Leaf[1]);

    leafReg_r (right);
    leafReg_l (left);

    strcpy(right->val_, val_);
    printf ("\nWho(What) is it?\n");
    fgets (buf_left, MAXSIZE, stdin);
    fgets (buf_left, MAXSIZE, stdin);
    len = strlen (buf_left);
    strncpy (left->val_, buf_left, len - 1);
    delete[] buf_left;

    printf ("\nWhat is the difference btw your character and mine?\n");
    fgets (buf, MAXSIZE, stdin);
    len = strlen (buf);
    strncpy (val_, buf, len - 1);
    strncat (val_, "?", 1);
    delete[] buf;

    printf ("\nThank you!\n\n");
}

void Leaf::treeCreate (char* data)
{
    static size_t i = 0;
           size_t j = 0;

    if (data[i] == '(')
    {
        i += 2;
        if (data[i] == '"')
        {
            i++;
            while (data[i] != '"')
            {
                val_[j] = data[i];
                i++;
                j++;
            }
        }
        else
            assert (!"Неверный вопрос!");

        i += 2;

        if (data[i] == '(')
        {
            Leaf* left = (new Leaf[1]);
            leafReg_l (left);
            left->treeCreate (data);
        }
        else if (data[i] == 'N')
            i += 2;
        else
            assert (!"Отсутствует левый лист!");

        if (data[i] == '(')
        {
            Leaf* right = (new Leaf[1]);
            leafReg_r (right);
            right->treeCreate (data);
        }
        else if (data[i] == 'N')
            i +=2 ;
        else
            assert (!"Отсутствует правый лист!"); 

        if (data[i] == ')')
            i += 2;
        else
            assert (!"Отсутствует закрывающаяся скобка!");
    }
    else
    {
        assert (!"Отсутствует открывающаяся скобка!");
    }
}