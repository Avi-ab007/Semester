digit	[0-9]
%{
	#include <bits/stdc++.h>
	#include <stdlib.h>	
	using namespace std;
	

	void foundWord(char *);
	std::set<string> keywords;
%}

%%
([a-zA-Z]+[0-9]*)+										{foundWord(yytext);}
({digit}+\.?{digit}*)|({digit}*\.{digit}+)				{printf("number");}
.														{printf("%s", yytext);}
%%

bool isKeyword(string s) {
	if (keywords.find(s) != keywords.end())
		return true;
	return false;
}

void setKeywords() {
	keywords.insert("if");
	keywords.insert("else");
	keywords.insert("break");
	keywords.insert("for");
	keywords.insert("while");
	keywords.insert("int");
	keywords.insert("float");
	keywords.insert("double");
	keywords.insert("string");
	keywords.insert("stringstream");
	keywords.insert("char");
	keywords.insert("printf");
	keywords.insert("cout");
	keywords.insert("main");
	keywords.insert("void");
	keywords.insert("return");
	keywords.insert("true");
	keywords.insert("false");
}

void foundWord(char *s) {
	string text(s);
	if (isKeyword(text)) 
		printf("keyword");
	else
		printf("identifier");
}

int main() {
	setKeywords();
	yylex();
	return 0;
}