all:
	yacc -d comp.y
	flex comp.l
	g++ -std=c++14 -Wno-write-strings lex.yy.c y.tab.c -ll -o comp