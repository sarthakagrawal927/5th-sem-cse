// 1 question - 40marks

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void removeSpacesAndLines()
{
    FILE *f1, *f2;
    f1 = fopen("q1out.c", "r");
    f2 = fopen("q2out.c", "w+");
    char ca = getc(f1);
    while (ca != EOF)
    {
        if (ca == '\n')
        {
            putc(ca, f2);
            while (ca == '\n')
                ca = getc(f1);
        }
        if (ca == ' ')
        {
            putc(ca, f2);
            while (ca == ' ')
                ca = getc(f1);
        }
        putc(ca, f2);
        ca = getc(f1);
    }
    fclose(f1);
    fclose(f2);
}

void removeShit()
{
    FILE *f1, *f2;
    f1 = fopen("q1in.c", "r");
    f2 = fopen("q1out.c", "w+");
    char ca = getc(f1);
    while (ca != EOF)
    {
        if (ca == '#')
        {
            while (ca != '\n')
                ca = getc(f1);
        }
        if (ca == '/')
        {
            ca = getc(f1);
            if (ca == '/')
            {
                while (ca != '\n')
                    ca = getc(f1);
            }
            else if (ca == '*')
            {
                while (ca != '/')
                    ca = getc(f1);
                ca = getc(f1);
            }
            else
            {
                putc('/', f2);
                putc(ca, f2);
            }
        }
        putc(ca, f2);
        ca = getc(f1);
    }
    fclose(f1);
    fclose(f2);
    removeSpacesAndLines();
}

int main(int argc, char const *argv[])
{
    removeShit();
    return 0;
}
