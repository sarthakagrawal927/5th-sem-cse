#include "lex.h"
FILE *f1;
struct token tkn;

void program()
{
    tkn = getNextToken(f1);
    if (strcmp(tkn.lexeme, "(") == 0)
    {
        tkn = getNextToken(f1);
        if (strcmp(tkn.lexeme, ")") == 0)
        {
            tkn = getNextToken(f1);
            if (strcmp(tkn.lexeme, "{") == 0)
            {
                tkn = getNextToken(f1);
                declarations();
                statements();
            }
        }
    }
}

void declarations()
{
    datatype(); // check for datatype
    isdlist();  // check for variable
    if (strcmp(tkn.lexeme, ";") == 0)
    {
        tkn = getNextToken(f1);
        declarations();
    }
    else
    {
        printf("; missing at row=%d col=%d", tkn.row, tkn.col);
        exit(1);
    }
}

int main(int argc, char const *argv[])
{
    f1 = fopen("q2out.c", "r");
    while ((tkn = getNextToken(f1)).row != -1)
    {
        if (strcmp(tkn.lexeme, "int") == 0)
        {
            tkn = getNextToken(f1);
            if (strcmp(tkn.lexeme, "main") == 0)
            {
                program();
                break;
            }
        }
        printf("Compiled successfully\n");
        fclose(f1);
    }
    return 0;
}
