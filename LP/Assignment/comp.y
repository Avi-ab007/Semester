%{
	#include <bits/stdc++.h>
	using namespace std;
	extern int yyparse();
	extern FILE *yyin;

	struct exprType {
		char *place;
		char *code;
	};

	void yyerror(char *args);
	int yylex(void);
	char *concat(char *a, char *b, char c);
	char *newVar();
	char *newLab();
	char *toStr(int x);
	void replace(char *origCode, char *oldLabel, char *newLabel);
	exprType *operate(exprType *e1, exprType *e2, char optr);
	exprType *assignOperate(char *e1, exprType *e2, char optr);

	int nVar = 0, nLab = 0;
	char *s;
	struct exprType *ret_exp;

%}
%expect 14
%start begin
%union {
	int ival;
	float fval;
	char *sval;
	struct exprType *expVal;
}
%token<ival>    DIGIT
%token<fval>    FLOAT
%token<sval>    ID IF ELSE WHILE BREAK TYPES REL_OPT OR AND NOT TRUE FALSE PE CASE SWITCH INCR DECR BOR BAND BXOR
%token<sval>    '+' '-' '*' '/' '^' '%' '\n' '=' ';' 
%type<sval>     list identifier number construct block dec prog begin boolean caseList 
%type<expVal>   expr stmt

%left   OR
%left   AND
%left   NOT
%left   REL_OPT
%left   BOR
%left   BAND
%left   BXOR
%right  PE ME IE DE
%right  '='
%left   '+' '-'
%left   '*' '/' '%'
%right  '^'
%right  '@'
%%

begin:  prog
		{
			char *s1 = $1;
			char *tmpLab = newLab();
			replace(s1, "NEXT", tmpLab);
			char *s = s1;
			printf("Three address code:\n%s\n", s);
			$$ = s;
		}
	;

prog:   prog construct
		{
			char *s1 = $1;
			char *s2 = $2;
			char *tmpLab = newLab();
			replace(s1, "NEXT", tmpLab);
			char *s = concat(s1, tmpLab, '\n');
			s = concat(s, s2, ':');
			$$ = s;
		}
	|
		construct
		{
			$$ = $1;
		}
	;

construct:  block
			{
				$$ = $1;
			}
		|
			IF '(' boolean ')' block
			{
				char *tmpLab = newLab();
				char *s1 = $3;
				replace(s1, "TRUE", tmpLab);
				replace(s1, "FAIL", "NEXT");
				char *s = concat($3, tmpLab, '\n');
				s = concat(s, $5, ':');
				$$ = s;
			}
		|
			WHILE '(' boolean ')' block
			{
				char *s1 = $3;
				char *s2 = $5;
				char *beg = newLab();
				char *tmp = newLab();
				replace(s1, "TRUE", tmp);
				replace(s1, "FAIL", "NEXT");
				replace(s2, "NEXT", beg);
				char *s = concat(beg, s1, ':');
				s = concat(s, tmp, '\n');
				s = concat(s, s2, ':');
				s = concat(s, "JUMP", '\n');
				s = concat(s, beg, ' ');
				$$ = s;
			}
		|
			IF '(' boolean ')' block ELSE block
			{
				char *b1 = $3;
				char *lab1 = newLab();
				replace(b1, "TRUE", lab1);
				char *lab2 = newLab();
				replace(b1, "FAIL", lab2);
				char *s = concat(b1, lab1, '\n');
				s = concat(s, $5, ':');
				s = concat(s, "JUMP NEXT", '\n');
				char *tmp = concat(lab2, $7, ':');
				strcat(s, "\n");
				strcat(s, tmp);
				$$ = s;
			}
		|
			SWITCH  '(' expr ')' '{' caseList '}'
			{
				char* s1 = $6;
				replace(s1, "VAR", $3->place);
				char* lab = newLab();
				replace(s1, "NEXT", lab);
				char* tmp;
				tmp = concat(s1, lab, '\n');
				char *s = concat($3->code, tmp, ':');
				$$ = s;
			}
		;

block:  '{' list '}'
		{
			$$ = $2;
		}
	|
		'{' construct '}'
		{
			$$ = $2;
		}
	|
		'{' prog '}'
		{
			$$ = $2;
		}
	|
		list
		{
			$$ = $1;
		}
	;

caseList:   caseList CASE expr ':' block
			{
				char *s1 = $1;
				char *lab = newLab();
				replace(s1, "NEXT", lab);
				char *str = $3->place;
				char *s = concat(s1, lab, '\n');
				s = concat(s, " if (", '\n');
				s = concat(s, "VAR", ' ');
				s = concat(s, " != ", ' ');
				strcat(s, str);
				strcat(s, ") ");
				s = concat(s, "JUMP NEXT", ' ');
				s = concat(s, $5, '\n');
				$$ = s;
			}
		|
			CASE expr ':' block
			{
				char *s;
				s = concat("if (", "VAR", ' ');
				s = concat(s, " != ", ' ');
				strcat(s, $2->place);
				strcat(s, ")");
				s = concat(s, "JUMP NEXT", ' ');
				s = concat(s, $4, '\n');
				$$ = concat($2->code, s, '\n');
			}
		;

list:   stmt
		{
			$$ = $1->code;
		}
	|
		list stmt
		{
			char *s1 = $1;
			char *s2 = $2->code;
			$$ = concat(s1, s2, '\n');
		}
	|
		list error '\n'
		{
			yyerrok;
		}
	;

stmt:   ';'
		{
			ret_exp = new exprType();
			ret_exp->place = $1;
			ret_exp->code = new char[20];
			ret_exp->code[0] = 0;
			$$ = ret_exp;
		}
	|
		expr ';'
		{
			$$ = $1;
		}
	|
		dec ';'
		{
			ret_exp = new exprType();
			ret_exp->place = $1;
			ret_exp->code = new char[20];
			ret_exp->code[0] = 0;
			$$ = ret_exp;
		}
	|
		identifier '=' expr ';'
		{
			ret_exp = new exprType();
			ret_exp->place =  newVar();
			char *tp = concat($1, $3->place, '=');

			char *s = concat($3->code, tp, '\n');
			ret_exp->code = s;
			$$ = ret_exp;
		}
	|
		dec '=' expr ';'						
		{
			ret_exp = new exprType();
			ret_exp->place =  newVar();
			char *tp = concat($1, $3->place, '=');
			char *s = concat($3->code, tp, '\n');
			ret_exp->code = s;
			$$ = ret_exp;
		} 
	|
		identifier PE expr ';'
		{
			$$ = assignOperate($1, $3, '+');        
		}
	|
		identifier ME expr ';'
		{
			$$ = assignOperate($1, $3, '-');
		}
	|
		identifier IE expr ';'
		{
			$$ = assignOperate($1, $3, '*');
		}
	|
		identifier DE expr ';'
		{
			$$ = assignOperate($1, $3, '/');
		}
	|
		identifier INCR ';'
		{
			ret_exp = new exprType();
			ret_exp->place = newVar();
			char* tp = concat(ret_exp->place, $1, '=');
			tp = concat(tp, "1", '+');
			strcat(tp, "\n");
			char* stp;
			stp = concat(" ", tp, '\n');
			s = concat($1, ret_exp->place, '=');
			strcat(stp, s);
			ret_exp->code = stp;       
			$$ = ret_exp;
		}
	|
		identifier DECR ';'
		{
			ret_exp = new exprType();
			ret_exp->place = newVar();
			char* tp = concat(ret_exp->place, $1, '=');
			tp = concat(tp, "1", '-');
			strcat(tp, "\n");
			char* stp;
			stp = concat(" ", tp, '\n');
			s = concat($1, ret_exp->place, '=');
			strcat(stp, s);
			ret_exp->code = stp;       
			$$ = ret_exp;  
		}
	;

dec:    TYPES identifier 
		{
			$$ = $2;
		}
	;

boolean:   expr REL_OPT expr
		{
			char *tp;
			tp = concat("if (", $1->place, ' ');
			tp = concat(tp, $2, ' ');
			tp = concat(tp, $3->place, ' ');
			tp = concat(tp, ") JUMP TRUE \n JUMP FAIL", ' ');
			char *st;
			st = concat($1->code, $3->code, '\n');
			st = concat(st, tp, '\n');
			$$ = st;
		}
	|
		boolean OR boolean
		{
			char *tp;
			char *s1 = $1;
			char *s2 = $3;
			char *lab = newLab();
			replace(s1, "FAIL", lab);
			tp = concat(s1, lab, '\n');
			tp = concat(tp, s2, ':');
			$$ = tp;
		}
	|
		boolean AND boolean
		{
			char *tp;
			char *s1 = $1;
			char *s2 = $3;
			char *lab = newLab();
			replace(s1, "TRUE", lab);
			tp = concat(s1, lab, '\n');
			tp = concat(tp, s2, ':');
			$$ = tp;
		}
	;

expr:   '(' expr ')'
		{
			$$ = $2;
		}
	|
		expr '+' expr
		{
			$$ = operate($1, $3, '+');
		}
	|
		expr '-' expr
		{
			$$ = operate($1, $3, '-');
		}
	|
		expr '*' expr
		{
			$$ = operate($1, $3, '*');
		}
	|
		expr '/' expr
		{
			$$ = operate($1, $3, '/');
		}
	|
		expr '%' expr
		{
			$$ = operate($1, $3, '%');
		}
	|
		expr '@' expr
		{
			$$ = operate($1, $3, '@');
		}
	|
		expr BOR expr
		{
			$$ = operate($1, $3, '|');
		}
	|
		expr BAND expr
		{
			$$ = operate($1, $3, '&');
		}
	|
		expr BXOR expr
		{
			$$ = operate($1, $3, '^');
		}
	|
		identifier
		{
			ret_exp = new exprType();
			ret_exp->place = $1;
			ret_exp->code = new char[2];
			ret_exp->code[0] = 0;
			$$ = ret_exp;
		}
	|
		number
		{
			ret_exp = new exprType();
			ret_exp->place = $1;
			ret_exp->code = new char[2];
			ret_exp->code[0] = 0;
			$$ = ret_exp;
		}
	;

identifier:	ID
		{
			$$ = $1;
		}
	;

number:	DIGIT
		{
			char *s = new char[20];
			snprintf(s, 10, "%d", $1);
			$$ = s;
		}
	|
		FLOAT
		{
			char *s = new char[20];
			snprintf(s, 10, "%f", $1);
			$$ = s;
		}
	;
%%

char *concat(char *a, char *b, char c) {							//Concat 'a' + 'c' + 'b'
	char *s = new char[strlen(a) + strlen(b) + 10];
	s[0] = 0;
	string str = "";
	str += c;
	if (a[0]) {
		strcat(s, a);
		strcat(s, str.c_str());
	}
	if (b[0]) 
		strcat(s, b);
	return s;
}

char *newVar() {													//Generate a new variable ti everytime it is called
	s = new char[10];
	s[0] = 0;
	strcat(s, "t");
	strcat(s, toStr(nVar));
	nVar++;
	return s;
}

char *newLab() {												//Generate a new lable Li everytime it is called
	char *s = new char[10];
	s[0] = 0;
	strcat(s, "L");
	strcat(s, toStr(nLab));
	nLab++;
	return s;
}

void yyerror(char *s) {
	printf("Parsing error.  Message: %s \n",s);
	exit(-1);
}

char *toStr(int x) {											//Convert integer to char array
	char* arr = new char[5];
	string sp = "";
	sp += to_string(x);
	arr[0] = 0;
	strcat(arr,sp.c_str());
	return arr;
}

void replace(char* og,char* oldS,char* newS){					//Replace occurence of oldS with newS in og
	char* pos = strstr(og,oldS);
	int l =strlen(newS);
	while(pos){
		strncpy (pos,newS,l);
		strncpy (pos+strlen(newS),"    ",max(4-l,0));			//oldS and newS may differ in lengths so add white spaces
		pos = strstr(og,oldS);
	}
}

exprType* operate(exprType* e1,exprType* e2,char oprt)			//Build the expression e1->place + 'oprt' + e1->place
{
	exprType* tmp;
	tmp = new exprType();
	tmp->place=newVar();
	char* sl;
	sl=concat(tmp->place,e1->place,'=');
	sl=concat(sl,e2->place,oprt);
	char *tp = concat(e1->code,e2->code,'\n');
	tp = concat(tp,sl,'\n');
	tmp->code=tp;
	/*printf("place: %s\n", tmp->place);
	printf("code: %s\n", tmp->code);*/
	return tmp; 	
}

exprType* assignOperate(char* e1,exprType* e2,char oprt){		//Same as operate only with assignment operators
	exprType* tmp;
	tmp = new exprType();
	tmp->place=newVar();
	char* tp =concat(tmp->place,e1,'=');
	tp=concat(tp,e2->place,oprt);
	strcat(tp,"\n");
	char* stp;
	// stp=concat($3->code,$1,'\n');
	stp=concat(e2->code,tp,'\n');
	s=concat(e1,tmp->place,'=');
	strcat(stp,s);
	tmp->code=stp;
	/*printf("place: %s\n", tmp->place);
	printf("code: %s\n", tmp->code);*/
	return tmp;
}

int main() {
	FILE *myfile = fopen("input.txt", "r");
	if (!myfile) {
		printf("File not open");
		return -1;
	}
	yyin = myfile;
	yyparse();
	/*do {
		yyparse();
	} while (!feof(yyin));	*/
}