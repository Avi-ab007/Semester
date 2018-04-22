letter		[a-zA-Z]
digit		[0-9]

%{
	#include <bits/stdc++.h>
	#include <stdlib.h>
	using namespace std;

	
	void oprd(char[], int);
	void optr(char[], int);
	float evaluate();
	string decToHex(float );

	stack<char> stk;
	vector<string> output;

	union ulf {
		unsigned long ul;
		float f;
	};
%}

%%
[a-zA-Z0-9]+							oprd(yytext, yyleng);
['+''-''*''/''('')''|''&''^']			optr(yytext, yyleng);
%%

void oprd(char text[], int len) {		//Converts the operand to decimal and pushes it to stack
	string tmp(text);
	float num;
	ulf u;
	stringstream ss;
	//cout<<s<<" hai "<<endl;
	ss<<tmp;
	ss>>hex>>u.ul;						//Stringstream acts as the intermediary converter
	num = u.f;
	output.push_back(to_string(num));
}

bool checkTop() {
	if (stk.top() != '+' || stk.top() != '-' || stk.top() != '%' ||
		stk.top() != '&' || stk.top() != '|' || stk.top() != '^') 
		return true;
	return false;
}

void optr(char text[], int len) {		//Convert infix to postfix
	char opr = text[0];
	string toPush = "";
	switch (opr) {							
		case '(' :
			stk.push(opr);
			break;
		case '/' :
			stk.push(opr);
			break;
		case '*' :
			if (stk.top() != '/')
				stk.push(opr);
			else {
				while (checkTop() && stk.size() > 0) {
					toPush = "";
					toPush += stk.top();
					output.push_back(toPush);
					stk.pop();
				}
				stk.push(opr);
			}
			break;
		case ')' :
			while (stk.top() != '(' && stk.size() > 0) {	//Pop all the contents of the stack untill 
				toPush = "";								//opening brace is not found
				toPush += stk.top();
				output.push_back(toPush);
				stk.pop();
			}
			stk.pop();
			break;
		default :
			while (stk.size() > 0) {
				toPush = "";
				toPush += stk.top();
				output.push_back(toPush);
				stk.pop();
			}
			stk.push(opr);
			break;
	}
}

bool checkInt(float x) {
	return (ceil(x) == x);
}

float evaluate() {				//Evaluate the postfix expression
	stack<float> ans;
	float left = 0, right = 0;
	for (int i = 0; i < output.size(); i++) {
		if (output[i] == "+") {
			right = ans.top();
			ans.pop();
			left  = ans.top();
			ans.pop();
			ans.push(left + right);
		} else if (output[i] == "-") {
			right = ans.top();
			ans.pop();
			left  = ans.top();
			ans.pop();
			ans.push(left - right);
		} else if (output[i] == "*") {
			right = ans.top();
			ans.pop();
			left  = ans.top();
			ans.pop();
			ans.push(left * right);
		} else if (output[i] == "/") {
			right = ans.top();
			ans.pop();
			left  = ans.top();
			ans.pop();
			ans.push(left / right);
		} else if (output[i] == "&") {		//Bitwise operation can be performed only on integers
			right = ans.top();
			ans.pop();
			left  = ans.top();
			ans.pop();
			if (checkInt(right) && checkInt(left)) {
				int l, r;
				l = (int) left;
				r = (int) right;
				ans.push(l & r);
			} else {
				printf("Bitwise operation can be performed only on integers\n");
				return 0;
			}
			
		} else if (output[i] == "|") {
			right = ans.top();
			ans.pop();
			left  = ans.top();
			ans.pop();
			if (checkInt(right) && checkInt(left)) {
				int l, r;
				l = (int) left;
				r = (int) right;
				ans.push(l | r);
			} else {
				printf("Bitwise operation can be performed only on integers\n");
				return 0;
			}
		} else if (output[i] == "^") {
			right = ans.top();
			ans.pop();
			left  = ans.top();
			ans.pop();
			if (checkInt(right) && checkInt(left)) {
				int l, r;
				l = (int) left;
				r = (int) right;
				ans.push(l ^ r);
			} else {
				printf("Bitwise operation can be performed only on integers\n");
				return 0;
			}
		} else if (output[i] == "%") {
			right = ans.top();
			ans.pop();
			left  = ans.top();
			ans.pop();
			if (checkInt(right) && checkInt(left)) {
				int l, r;
				l = (int) left;
				r = (int) right;
				ans.push(l % r);
			} else {
				printf("Bitwise operation can be performed only on integers\n");
				return 0;
			}
		} else {
			ans.push(atof(output[i].c_str()));
		}
	}
	if (ans.size() > 0)
		return ans.top();
	return right;
}

int main() {
	yylex();
	string toPush = "";
	while (stk.size() > 0) {
		toPush = "";
		toPush += stk.top();
		output.push_back(toPush);
		stk.pop();
	}
	for (int i = 0; i < output.size(); i++)
		printf("%s ", output[i].c_str());

	float res = evaluate();

	std::stringstream stream;					//Convert float to hexadecimal
	stream << std::hex << res;
	std::string result( stream.str() );
	std::cout <<showbase<< std::hex <<res<<endl; 
	printf("hex is  0x%x\n", *(unsigned int*)&res);
	
}