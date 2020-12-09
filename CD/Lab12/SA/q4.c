#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
void removeComments()
{
	FILE *fa, *fb;
	int ca, cb;

	fa = fopen("q1in.c", "r");
	if (fa == NULL)
	{
		printf("Cannot open\n");
		return;
	}
	fb = fopen("q1out.c", "w");
	ca = getc(fa);
	while (ca != EOF)
	{
		if (ca == ' ')
		{
			putc(ca, fb);
			while (ca == ' ')
				ca = getc(fa);
		}
		if (ca == '/')
		{
			cb = getc(fa);
			if (cb == '/')
			{
				while (ca != '\n')
					ca = getc(fa);
				putc(ca, fb);
			}
			else if (cb == '*')
			{
				do
				{
					while (ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				} while (ca != '/');
			}
			else
			{
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else
			putc(ca, fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
}

void removeDirectives()
{
	FILE *fa, *fb;
	int ca, cb;
	removeComments();

	fa = fopen("q1out.c", "r");
	if (fa == NULL)
	{
		printf("Cannot open\n");
		return;
	}
	fb = fopen("q2tempout.c", "w");
	ca = getc(fa);
	while (ca != EOF)
	{
		if (ca == '#')
		{
			do
			{
				ca = getc(fa);
			} while (ca != '\n');
		}
		putc(ca, fb);
		ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);

	fa = fopen("q2tempout.c", "r");
	if (fa == NULL)
	{
		printf("Cannot open\n");
		return;
	}
	fb = fopen("q2out.c", "w");
	ca = getc(fa);
	while (ca == '\n')
	{
		ca = getc(fa);
	}
	while (ca != EOF)
	{

		putc(ca, fb);
		ca = getc(fa);
	}

	fclose(fa);
	fclose(fb);

	if (remove("q2tempout.c") != 0)
		printf("Error\n");
}

char key[32][10] = {
	"auto", "double", "int", "struct", "break", "else", "long",
	"switch", "case", "enum", "register", "typedef", "char",
	"extern", "return", "union", "const", "float", "short",
	"unsigned", "continue", "for", "signed", "void", "default",
	"goto", "sizeof", "voltile", "do", "if", "static", "while"};

int isKeyword(char *word)
{
	// printf("%s\n",word );
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(key[i], word) == 0)
			return 1;
	}
	return 0;
}

//Following functions have been copied
// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}')
		return (true);
	return (false);
}

// Returns 'true' if the string is a REAL NUMBER.
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
	return (hasDecimal);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isInteger(char *str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// Copied Till here

int main(int argc, char const *argv[])
{
	FILE *fa, *fb;
	int ca, cb;
	removeDirectives(); // remove commments is called there

	fa = fopen("q2out.c", "r");
	if (fa == NULL)
	{
		printf("Cannot open\n");
		return 0;
	}
	char word[20], num[20];
	int i = 0;
	for (size_t i = 0; i < 20; ++i)
		num[i] = 0;
	ca = getc(fa);
	int row = 1, col = 0;
	while (ca != EOF)
	{

		// line break
		if (ca == '\n')
		{
			row++;
			col = 0;
			printf("\n");
		}

		// check string
		else if (ca == '"')
		{
			printf("<String, %d,%d>\n", row, col);
			ca = getc(fa);
			while (ca != '"')
			{
				col++;
				ca = getc(fa);
			}
		}

		else if (ca == ' ')
		{
			ca = getc(fa);
			continue;
		}

		// is a word ->  keyword / variable
		else if (isalpha(ca) != 0)
		{
			word[i++] = ca;
			while (isalpha(ca) != 0 || isdigit(ca) != 0 || ca == '_')
			{
				ca = getc(fa);
				if (isalpha(ca) != 0 || isdigit(ca) != 0 || ca == '_')
					word[i++] = ca;
				col++;
			}
			if (isKeyword(word))
				printf("<%s,%d,%d>\n", word, row, col - (int)(strlen(word)) + 1);
			else
				printf("<id_%s,%d,%d>\n", word, row, col - (int)(strlen(word)) + 1);
			i = 0;
			for (size_t i = 0; i < sizeof word; ++i)
				word[i] = 0;
			continue;
		}

		// is an Delimeter
		else if (isDelimiter(ca))
		{
			printf("<%c,%d,%d>\n", ca, row, col + 1);
		}

		// is a number of any sort
		else if (isdigit(ca) != 0)
		{
			num[i++] = ca;
			while (isdigit(ca) != 0 || ca == '.')
			{
				ca = getc(fa);
				if (isdigit(ca) != 0 || ca == '.')
					num[i++] = ca;
				col++;
			}
			if (isRealNumber(num) || isInteger(num))
				printf("<%s,%d,%d>\n", num, row, col - (int)(strlen(num)) + 1);
			i = 0;
			for (size_t i = 0; i < sizeof num; ++i)
				num[i] = 0;
			continue;
		}

		col++;
		ca = getc(fa);
	}
	fclose(fa);
	return 0;
}