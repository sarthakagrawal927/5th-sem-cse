#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// NEVER DO ++row and col =1 in between

#define SZ 20

struct token
{
	int is_keyword,is_datatype,is_id,is_func;
	char lexeme[SZ],tok_type[SZ];
	int idx;
	unsigned int row,col; //row number, column number
	int sz;
};

//------------------------------------------------------------------------------------------------------------------------


struct ListElement{
  struct token tok;
  struct ListElement *next;
};
struct ListElement *TABLE[SZ];
int val=-1,TableLength = 0;

int SEARCH(struct token tk){
    //printf("s\n");
    struct ListElement * cur;
    for(int i=0;i<=val;i++){
      cur = TABLE[i];
     if(cur&&strcmp(tk.tok_type,"func")==0){
           if(strcmp((cur->tok).lexeme,tk.lexeme)==0){
            return 1;
         }
      }
     else{
       while(cur){
         if(strcmp((cur->tok).lexeme,tk.lexeme)==0&&strcmp((cur->tok).tok_type,tk.tok_type)==0&&(cur->tok).idx==tk.idx){
         return 1;
       }
       cur=cur->next;
      }
    }
   }
    return 0;
}

void INSERT(struct token tk){
  if(strcmp(tk.tok_type,"func")!=0&&SEARCH(tk)==1){
     return;
   }

  struct ListElement* cur = malloc(sizeof(struct ListElement));
  cur->tok = tk;
  cur->next = NULL;

  if(TABLE[val]==NULL){
     TABLE[val] = cur; // No collosion.
  }
  else{
    struct ListElement * ele= TABLE[val];
    while(ele->next!=NULL){
       ele = ele->next; // Add the element at the End in the case of a collision.
    }
    ele->next = cur;
  }
}

void Initialize(){
  for(int i=0;i<SZ;i++){
      TABLE[i] = NULL;
  }
}

void Display(){
//iterate through the linked list and display
 for(int i=0;i<=val;i++){
    struct ListElement * cur = TABLE[i];
    printf("%d %s %s\n\n",i+1,(cur->tok).lexeme,(cur->tok).tok_type);
    cur=cur->next;
    while(cur){
        printf("%s   %s   %d\n",(cur->tok).lexeme, (cur->tok).tok_type,(cur->tok).sz);
        cur=cur->next;
    }
    printf("*******************\n");
 }
}

//------------------------------------------------------------------------------------------------------------------------

int row,col;
bool FILE_NOT_ENDED = true;

void print_lexeme(struct token s){
   printf("<%s,%d,%ld>",s.lexeme,s.row,s.col);
   return;
}

void print_func(struct token s){
   printf("<%s,%d,%d,%d,%s>",s.lexeme,s.row,s.col,s.sz,s.tok_type);
   return;
}

void print_token(struct token s){
   printf("<%s,%d,%d>",s.tok_type,s.row,s.col);
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
	"auto","int","struct","break","else","long",
      "switch","case","enum","register","typedef","char",
      "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
      "goto","sizeof","voltile","do","if","static","while","printf","scanf","bool"
};


int isKeyword(char* word){
	for(int i = 0; i < 34; i++){
		if(strcmp(key[i], word) == 0) {
			return 1;
		}
	}
	return 0;
}

char * datatype[] = {
	"int","float","char","double"
};

int SIZEinBytes[] = {
	4,4,1,8
};

int is_datatype(char * dbuff){
	for(int i = 0; i < 4; i++){
		if(strncmp(datatype[i], dbuff,strlen(datatype[i])) == 0) {
			return i;
		}
	}
	return -1;
}

// refactored

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

void skip_space_tab(FILE *fa,char ca){
	// skip blankspaces and tabs
	if(ca==' '||ca=='\t'){

		//->
	    ca=fgetc(fa); ++col; 

		while(ca==' '||ca=='\t'){
			ca=fgetc(fa); ++col; 
		}
	    fseek(fa,-1,SEEK_CUR); --col;
	    //<-

	}
}

char num[SZ],temp[SZ],buff[SZ],dbuff[SZ];

struct token getNextToken(FILE *fa){
	
	char ca,cb;
    int i=0,j,mul=0,is_func=0,is_array=0;

    struct token s; s.is_datatype=0,s.is_keyword=0,s.is_id=0;

    // // // //->
    ca=fgetc(fa); ++col;

    while(ca != EOF){

        // newline
		if(ca == '\n'){
			row++;
			// printf("row in while -> %d\n",row );
			col = 0;
			printf("\n");
		}


		// skip blankspaces and tabs
		else if(ca==' '||ca=='\t'){

			//->
		    ca=fgetc(fa); ++col; 

			while(ca==' '||ca=='\t'){
				ca=fgetc(fa); ++col; 
			}
		    fseek(fa,-1,SEEK_CUR); --col;
		    //<-

		}

		//comments
        else if(ca=='/'){

        	// //->
        	cb=fgetc(fa); ++col;
        	if(cb=='/'){
        		i=0;
        		//->
                while(ca!='\n'){
                	
                	ca=fgetc(fa);
                	temp[i++] = ca;
                }
                temp[i] = '\0';
                fseek(fa,-1,SEEK_CUR); 
                //<-

                // printf("comment -> %s\n",temp );
                return s; // return imp to handle row
        	}

        	// handle this
        	else if(cb=='*'){
                do{
                	while(ca!='*')
                		ca = fgetc(fa);
                	ca = fgetc(fa);
                }while(ca!='/');
        	}
        	
        	fseek(fa,-1,SEEK_CUR); --col;
            // //<-

        	// for / operator
            i=0;
			temp[i++]=ca;
			temp[i]='\0';
		
			strcpy(s.lexeme,temp);
			s.row=row;
			s.col=col;
			return s;

            // printf("col12 -> %d, ca = %c\n", col,ca);
        }

        // preprocessor
		else if(ca=='#'){
			i=0;

			//->
			while(ca!='\n'){
				temp[i++] = ca;
				ca = fgetc(fa); col++;
			}
			temp[i] = '\0';
			fseek(fa,-1,SEEK_CUR); --col;
			//<-

			// printf("preprocessor -> %s\n",temp );

			if(!(is_define(temp)||is_include(temp))){
				// strcpy((s.lexeme),temp);
				strcpy(s.tok_type,"unknown");
				s.row=row;
				s.col=col-strlen(temp)+1;
                return s;
			}
		}

		// keyword , datatype , id , func
		else if(isalpha(ca)) {

			// printf("col1 -> %d, ca = %c\n", col,ca);

			i=0;

			//->
			while(isalpha(ca) || isdigit(ca) || ca == '_'){
				buff[i++] = ca;
				ca = fgetc(fa); col++;
			}
			buff[i]='\0';
			fseek(fa,-1,SEEK_CUR); --col;
			//<-


			// printf("buff -> %s\n",buff );
			// printf("col2 -> %d\n", col);


			// //->
			cb=fgetc(fa); ++col;
			if(cb=='(' && !isKeyword(buff)){
				is_func=1;
			}
			else if(cb=='['){
				is_array=1;
				int col2=0;
				while(cb!=']'){
					cb=fgetc(fa); ++col2;
					mul = mul*10;
					mul += (int)(cb-'0');
				}
				fseek(fa,-col2,SEEK_CUR); 
			}
			fseek(fa,-1,SEEK_CUR); --col;
			// //<-

			// if(is_datatype(buff)>0){
			// 	strcpy(dbuff,buff);
			// }

			if(is_func){
				s.is_func=1;
				strcpy(s.lexeme,buff);
				strcpy(s.tok_type,"func");
				s.row=row;
				s.col=col-(int)(strlen(buff))+1;
				s.sz=-1;
				return s;
			}
			else if(is_array){

				// printf("col4 -> %d\n", col);

				strcpy(s.lexeme,buff);
				strcpy(s.tok_type,dbuff);
				s.row=row;
				s.col=col-(int)(strlen(buff))+1;
				s.sz= mul*SIZEinBytes[ is_datatype(dbuff) ];
				return s;
			}
			else if(is_datatype(buff)>0){

				// printf("col3 -> %d\n", col);

				strcpy(dbuff,buff); // store the datatype

				s.is_datatype=1;
				strcpy(s.tok_type,buff);
				s.row=row;
				s.col=col-(int)(strlen(buff))+1;
				return s;
			}
			else if(isKeyword(buff)){

				// printf("col6 -> %d\n", col);

				s.is_keyword=1;
				strcpy(s.lexeme,buff);
				s.row=row;
				s.col=col-(int)(strlen(buff))+1;
				return s;
		    }
			else{

				// printf("col5 -> %d\n", col);
				
				s.is_id=1;
				strcpy(s.lexeme,buff);
                strcpy(s.tok_type,"id");
				s.row=row;
				s.col=col-strlen(buff)+1;
				return s;
        	}
		}

		//relational operator
        else if(ca=='='||ca=='>'||ca=='<'||ca=='!'){

        	//->
        	cb=fgetc(fa); ++col;
        	i=0;
        	temp[i++]=ca;
        	if(cb=='='){
				temp[i++] = cb;
				temp[i] = '\0';
				strcpy(s.lexeme,temp);
				s.row=row;
				s.col=col;
				return s;
        	}
        	fseek(fa,-1,SEEK_CUR); --col;
            //<-
	
            temp[i]='\0';
            strcpy(s.lexeme,temp);
         	s.row=row;
         	s.col=col;
            
         	return s;
        }
        //string
        else if(ca=='"'){
        	i=0;

            do{
				i++;
				ca=fgetc(fa); ++col;
            }while(ca!='"');
            
			strcpy(s.lexeme,"string literal");
			s.row=row;
			s.col=col-i;
			return s;
        }
        //delimiters
        else if(isDelimiter(ca)){

			i=0;
			temp[i++]=ca;
			temp[i]='\0';
			strcpy(s.lexeme,temp);
			s.row=row;
			s.col=col;
			return s;
        }
        //numeric constants
        else if(isdigit(ca)){
        	i=0;

        	//->
        	while(isdigit(ca)){
        		i++;
        		ca=fgetc(fa); ++col;
        	}
        	fseek(fa,-1,SEEK_CUR); --col;
        	//<-

        	strcpy(s.lexeme,"num");
         	s.row=row;
         	s.col=col-i+1;
         	return s;
        }
        //arithmetic op
        else if(isArithmetic_operator(ca)){
			i=0;
			temp[i++]=ca;
			temp[i]='\0';
		
			strcpy(s.lexeme,temp);
			s.row=row;
			s.col=col;
			return s;
        }



        //->
		ca = getc(fa); ++col;

		// printf("col10 -> %d, ca = %c\n", col,ca);
	}
	FILE_NOT_ENDED = false;
	return s;
}

int main(int argc, char const *argv[])
{
	FILE *fa=fopen("HelloWorld.c","r");
	if(fa==NULL){
	   perror("fopen");
	   exit(1);
	}
	Initialize();
	struct token s;

	row=1;
	col=0;
	int start = 1;

	//->
	char ca=fgetc(fa); ++col;
	
	while(FILE_NOT_ENDED && ca!=EOF){ 
		if(start){
			fseek(fa,-1,SEEK_CUR); --col;
			//<-
			start=0;
		}
		
		s=getNextToken(fa);
		// printf("gnt call ,row -> %d\n",row );
		if(s.is_id==1 || s.is_func==1){
			INSERT(s);
		}
		if(s.is_id){
			print_token(s);
	
		}else if(!strcmp(s.tok_type,"func")){
			print_func(s);

		}else{
			print_lexeme(s);
		} 
        // printf("after call to gettoken ca is = %c",ca);
	}
	
	fclose(fa);
	printf("\n SYMBOL TABLE\n");
    Display();
	return 0;
}
