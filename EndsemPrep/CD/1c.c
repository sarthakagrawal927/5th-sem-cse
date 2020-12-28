#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct token
{
    char lexeme[20], type[10];
    int index, row, col, sz;
};

int row, col;
char ca, temp[20];

bool FILE_ENDED = false;

void print_token(struct token s)
{
    printf("<%s, %d, %d>", s.lexeme, s.row, s.col);
}

char *key[] = {
    "auto", "double", "int", "struct", "break", "else", "long",
    "switch", "case", "enum", "register", "typedef", "char",
    "extern", "return", "union", "const", "float", "short",
    "unsigned", "continue", "for", "signed", "void", "default",
    "goto", "sizeof", "voltile", "do", "if", "static", "while", "main"};

int isKeyword(char *word)
{
    for (int i = 0; i < 33; i++)
        if (strcmp(key[i], word) == 0)
            return 1;
    return 0;
}

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == ',' || ch == ';' || ch == '=' ||
        ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return true;
    return false;
}

bool isRelational_operator(char ch)
{
    if (ch == '>' || ch == '<' || ch == '!')
        return true;
    return false;
}

bool isArithmetic_operator(char ch)
{
    if (ch == '%' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/')
        return true;
    return false;
}

bool isRealNumber(char *str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return hasDecimal;
}

bool isInteger(char *str)
{
    int i, len = strlen(str);

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++)
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || str[i] == '.' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

struct token getNextToken(FILE *fa)
{
    char cb, word[20], num[20];
    int i = 0;

    while (ca != EOF)
    {
        struct token s;
        if (ca == ' ')
        {
            ca = getc(fa);
            continue;
        }
        else if (ca == '\n')
        {
            row++;
            col = 1;
            printf("\n");
        }

        // string check
        else if (ca == '"')
        {
            strcpy(s.lexeme, "string");
            s.row = row;
            s.col = col;
            ca = getc(fa);
            col++;
            while (ca != '"')
            {
                col++;
                ca = getc(fa);
            }
        }

        // word check
        else if (isalpha(ca))
        {
            i = 0;
            while (isalpha(ca) || isdigit(ca) || ca == '_')
            {
                word[i++] = ca;
                ca = getc(fa);
                col++;
            }
            word[i] = '\0';
            fseek(fa, -1, SEEK_CUR);
            col--;
            if (isKeyword(word))
                strcpy(s.lexeme, word);
            else
                strcpy(s.lexeme, "id");
            s.row = row;
            s.col = col - (int)(strlen(word)) + 1;
            return s;
        }

        else if (isDelimiter(ca) || isRelational_operator(ca) || isArithmetic_operator(ca))
        {
            char c[10];
            c[0] = ca;
            c[1] = '\0';
            strcpy(s.lexeme, c);
            s.row = row;
            s.col = col;
            col++;
            return s;
        }

        else if (isdigit(ca))
        {
            i = 0;
            num[i++] = ca;
            while (isdigit(ca) || ca == '.')
            {
                num[i++] = ca;
                ca = getc(fa);
                col++;
            }
            num[i] = '\0';
            if (isRealNumber(num) || isInteger(num))
            {
                strcpy(s.lexeme, "num");
                s.row = row;
                s.col = col - (int)(strlen(num)) + 1;
                return s;
            }
            i = 0;
            num[0] = '\0';
            continue;
        }
        ca = getc(fa);
    }
    FILE_ENDED = true;
    struct token s;
    strcpy(s.lexeme, "null");
    s.row = -1;
    s.col = -1;
    return s;
}

int main(int argc, char const *argv[])
{
    FILE *fa = fopen("q2out.c", "r");
    struct token s;
    row = 1;
    col = 1;
    ca = fgetc(fa);
    while (!FILE_ENDED && ca != EOF)
    {
        s = getNextToken(fa);
        ca = getc(fa);
        print_token(s);
    }
    printf("\n");
    fclose(fa);
    return 0;
}
