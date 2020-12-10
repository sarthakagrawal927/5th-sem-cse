#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum tokenType { EOFILE=-1, LESS_THAN,
LESS_THAN_OR_EQUAL,GREATER_THAN,GREATER_THAN_OR_EQUAL,
EQUAL,NOT_EQUAL};

struct token
{
  char lexeme[20];
  int index;
  unsigned int row,col; //row number, column number.
  enum tokenType type;
  int sz;
};

int row,col;
char ca,temp[20];
bool FILE_NOT_ENDED = true;

void print_token(struct token s){
   printf("<%s,%d,%d>",(s.lexeme),s.row,s.col);
   return;
}

bool is_include(char* temp){
	if(strstr(temp,"#include")!=NULL){
			return true;
		}
	return false;
}

bool is_define(char *temp){
	if(strstr(temp,"#define")!=NULL){
			return true;
		}
	return false;
}




char* key[] = {
	"auto","double","int","struct","break","else","long",
      "switch","case","enum","register","typedef","char",
      "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
      "goto","sizeof","voltile","do","if","static","while"
};


int isKeyword(char* word){
	// printf(" word in func %s\n",word );
	for(int i = 0; i < 32; i++){
		// printf(" key in func %s\n",key[i] );
		if(strcmp(key[i], word) == 0) {
			// printf("%s\n", "Keyworh hai ");
			return 1;
		}
		// printf(" strcmp %d\n",strcmp(key[i], word)  );
	}
	return 0;
}

//Following functions have been copied

bool isDelimiter(char ch)
{
    if (ch == ' ' || ch == ',' || ch == ';'  || ch=='='||
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
        ch == '/' )
        return true;
    return false;
}


bool isRealNumber(char* str)
{
    int i, len = strlen(str);
    bool hasDecimal = false;

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' ||
            (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return hasDecimal;
}


bool isInteger(char* str)
{
    int i, len = strlen(str);

    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'
            && str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9'|| str[i]=='.' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}


struct token getNextToken(FILE *fa){
	char cb;
	char word[20], num[20];
	int i = 0;
	num[0]='\0';

	while(ca != EOF){
         struct token s;
		// line break
		if(ca == '\n'){
			row++;
			col = 1;
			printf("\n");
		}
        else if(ca=='#'){
			int x=0;
			while(ca!='\n'){
				temp[x++] = ca;
				ca = getc(fa);
				col++;
			}
			temp[x] = '\0';
			if(!(is_define(temp)||is_include(temp))){
				strcpy((s.lexeme),temp);
				s.row=row;
				s.col=col-strlen(temp);
				col=1;
                return s;
			}
			col=1;
		}

		// remove comments , blankspaces
		else if(ca==' '||ca=='\t'){
            ca=fgetc(fa);
			while(ca==' '||ca=='\t'){
				ca=fgetc(fa);
			}
            fseek(fa,-1,SEEK_CUR);
		}
		else if (ca=='/'){
			cb = getc(fa);
			if (cb == '/'){
				while(ca != '\n')
					ca = getc(fa);
				col=0;
			}
			else if (cb == '*'){
				do{
					while(ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				}while (ca != '/');;
			}
			else{
				fseek(fa, -2, SEEK_CUR);
			}
		}
		// check string
		else if(ca == '"'){
			// printf(" 5 \n");
			strcpy(s.lexeme,"string literal");
			s.row=row;
			s.col=col;
			print_token(s);
			ca = getc(fa);
			while(ca != '"'){
				col++;
				ca = getc(fa);
			}
			col++;
		}

		// is a word ->  keyword / variable
		else if(isalpha(ca)) {
			i=0;
			while(isalpha(ca) || isdigit(ca) || ca == '_'){
				word[i++] = ca;
				ca = getc(fa);
				col++;
			}
			word[i]='\0';
			fseek(fa,-1,SEEK_CUR);
			col--;
			// printf(" word hai %s\n",word );
			if(isKeyword(word)){
					strcpy(s.lexeme,word);
					s.row=row;
					s.col=col-(int)(strlen(word))+1;
					return s;
		   }
			else{
				    strcpy(s.lexeme,"id");
					s.row=row;
					s.col=col-(int)(strlen(word))+1;
					return s;
			}
			
		}

		// is an Delimeter
		else if(isDelimiter(ca)){
			       char  c[10]; 
					c[0]=ca;
					c[1]='\0';
					strcpy(s.lexeme,c);
					s.row=row;
					s.col=col;
					col++;
					return s;
		}
        // is a relational op
        else if(isRelational_operator(ca)){
                    char  c[10]; 
					c[0]=ca;
					c[1]='\0';
					strcpy(s.lexeme,c);
					ca=getc(fa);
					col++;
					s.row=row;
					if(ca=='=')
						s.col=col-1;
					else{
						s.col=col;
						fseek(fa,-1,SEEK_CUR);
					}
					return s;
        }
        else if(isArithmetic_operator(ca)){
        	        char  c[10]; 
					c[0]=ca;
					c[1]='\0';
					strcpy(s.lexeme,c);
					s.col=col;
					s.row=row;
					return s;

        }
		// is a number of any sort
		else if(isdigit(ca)){
			i=0;
			num[i++] = ca;
			while(isdigit(ca)|| ca == '.'){
				num[i++] = ca;
				ca = getc(fa);
				col++;
			}
			num[i]='\0';
			if(isRealNumber(num) || isInteger(num)){
					strcpy(s.lexeme,"num");
					s.row=row;
					s.col=col- (int)(strlen(num))+1;
					return s;
		    }
			i = 0;
			num[0]='\0';
			continue;
		}

		//col++;
		ca = getc(fa);

	}
	FILE_NOT_ENDED = false;
	struct token s;
	strcpy(s.lexeme,"null");
	s.row=-1;
	s.col=-1;
	return s;
}

int main(int argc, char const *argv[])
{
	FILE *fa=fopen("inputg.txt","r");
	struct token s;
	row=1;
	col=1;
	ca=fgetc(fa);
	while(FILE_NOT_ENDED&&ca!=EOF){
		s=getNextToken(fa);
		//col++;
		ca=fgetc(fa);
		// printf(" after call and +1 ptr at - %c \n",ca );
        print_token(s);
	}
	printf("\n");
	fclose(fa);
	return 0;
}
