%{
	#include <stdio.h>
	#include <ctype.h>
	#include <math.h>
	#define YYSTYPE double
	double exponent(double,double);
%}

%token num

%left '+' '-'
%left '*' '/'
%right '^'

%%

S : 
	| E '\n' {
							printf("answer: %g\n ", $$ );
							return 0;
					 }
	;
E :num
 	| E '+' E { $$=$1+$3; printf("%g + %g = %g \n",$1,$3,$$); }
	| E '-' E { $$=$1-$3; printf("%g - %g = %g \n",$1,$3,$$);}
	| E '/' E { $$=$1/$3; printf("%g / %g = %g \n",$1,$3,$$);}
	| E '*' E { $$=$1*$3; printf("%g * %g = %g \n",$1,$3,$$);}
	| E '^' E { $$=exponent($1,$3); printf("%g ^ %g = %g\n",$1,$3,$$);}
	;

%%

#include "lex.yy.c"

int main()
{
printf("Enter the expression: ");
yyparse();
return 0;
}
double exponent (double a, double b)
{
	double result=1;
	while(b!=0)
	{
		result*=a;
		--b;
	}
	return result;
}
yyerror(char *s)
{
fprintf(stderr, "error: %s\n", s);
}
