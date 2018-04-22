DIGIT [0-9]+\.?|[0-9]*\.[0-9]+
%option noyywrap
%%
{DIGIT} { yylval=atof(yytext); return num;}
\n|. {return yytext[0];}
%%
