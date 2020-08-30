#include <stdio.h>
#include <assert.h>

//-----------------------------------------------------------------------------

void Filling_data (int mass[], const int size);

void Sort_data (int mass[], const int size);

void Swap (int* val1, int* val2);

void Print_data (const int mass[], int size, const char name_mas[]);

//-----------------------------------------------------------------------------

int main()
{
    printf ("#Data sorting 2020\n\n");

    const int size = 10;

    int mass[size] = {};

    Filling_data (mass, size);

    Sort_data (mass, size);

    Print_data (mass, size, "mass");
}

//-----------------------------------------------------------------------------

void Filling_data (int mass[], const int size)
{
    const char file_name[] = "Data_s.txt";
    FILE* file_data = fopen (file_name, "r");

    assert (file_data != NULL);

    for (int i = 0; i < size; i++)
        fscanf (file_data, "%d", &mass[i]);

    fclose (file_data);

    return;
}

//-----------------------------------------------------------------------------

void Sort_data (int mass[], const int size)
{
    for (int i = size-1; i >= 0; i--)
    {
        int max  = mass[i],
            nmax = i;

        for (int j = 0; j < i; j++)
        {
            if (max < mass[j])
            {
                max  = mass[j];
                nmax = j;
            }
        }

        Swap (&mass[nmax], &mass[i]);
    }

    return;
}

//-----------------------------------------------------------------------------

void Swap (int* val1, int* val2)
{
    int temp = *val1;
    *val1    = *val2;
    *val2    = temp;
}

//-----------------------------------------------------------------------------

void Print_data (const int mass[], const int size, const char name_mas[])
{
    const char file_name[] = "Data_f.txt";
    FILE* file_data = fopen (file_name, "w");

    assert (file_data != NULL);

    for (int i = 0; i < size; i++)
        fprintf (file_data, "%s [%d] = %d\n", name_mas, i, mass[i]);

    fclose (file_data);

    return;
}
