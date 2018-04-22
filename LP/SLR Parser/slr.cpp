#include <bits/stdc++.h>
#include <unistd.h>
#define itr1 map<string, vector<string> > :: iterator
#define itr2 map<string, set<string> > :: iterator
#define itr3 set<string> :: iterator
#define itr4 set<pair<string, vector<string> > > :: iterator
#define prod map<string, vector<string> >
#define itemset set<pair<string, vector<string> > >
#define stateptr struct state*
using namespace std;

string eps = "\u03B5";
prod Prod;
map<string, set<string> > First;
map<string, set<string> > Follow;
set<string> terminals;
set<string> nonTerminals;
void computeFollow(string);
void computeFirst(string );

struct state{
	itemset items;
	int stateNo;
	map<char, stateptr> moveOnSym;
};

bool isTerminal(string x){
	return ((!(x[0] >= 'A' && x[0] <= 'Z')) || x == eps);
}

string minusPrefix(string s1,string s2){
	int l = s2.size();

	return s1.substr(l);
}

string toStr(char x) {
	string s = "";
	s += x;
	return s;
}

int beginSame(string &s1,string &s2){
	int l =s2.length();
	int i=0;
	while(i<l){
		if(s1[i]!=s2[i])
			return 0;
		i++;
	}

	return 1;
}

void addTerminals(string s) {
	if (s == eps) {
		First[eps].insert(eps);
		return;
	}
	for (int i = 0; i < s.length(); i++) {
		if (isTerminal(toStr(s[i]))) {
			terminals.insert(toStr(s[i]));
			First[toStr(s[i])].insert(toStr(s[i]));
		}
	}
}

void inputProductions(){
	terminals.insert("$");
	string left, right;
	cout<<"Enter the rules 0 to exit\n";
	while (true) {
		cin>>left;
		nonTerminals.insert(left);
		if(left == "0")
			break;
		cin>>right;
		addTerminals(right);
		Prod[left].push_back(right);
	}
}

void printProductions(prod oldProd) {
	itr1 it = oldProd.begin();
	while (it != oldProd.end()) {
		cout<<it->first<<" --> ";
		std::vector<string> v = it->second;
		for (int i = 0; i < v.size(); i++) {
			if (v[i].length() > eps.length() and beginSame(v[i], eps))
				cout<<v[i].substr(eps.length())<<"|";
			else
				cout<<v[i]<<"|";
		}
		it++;
		cout<<endl;
	}
}

void addFirst(string S, string left) {
	if (S == eps) {
		First[left].insert(eps);
		return;
	}
	for (int i = 0; i < S.length(); i++) {
		string tmp = toStr(S[i]);
		if (isTerminal(tmp)) {
			First[left].insert(tmp);
			return;
		} else {
			computeFirst(tmp);
			itr3 it = First[tmp].begin();
			bool flag = false;
			while (it != First[tmp].end()) {
				if ((*it) == eps)
					flag = true;
				else
					First[left].insert((*it));
				it++;
			}
			if (!flag)
				return;
		}
	}
	First[left].insert(eps);
}

void computeFirst(string var) {
	if (First.find(var) != First.end())
		return;

	if (isTerminal(var)) {
		First[var].insert(var);
		return;
	} else {
		std::vector<string> right = Prod[var];
		for (int i = 0; i < right.size(); i++) {
			string y = right[i];
			addFirst(y, var);
		}
	}
}

void computeFirstWrapper() {
	itr1 it = Prod.begin();
	while (it != Prod.end()) {
		computeFirst(it->first);
		it++;
	}
}

void printSet(set<string> &S){
	itr3 it = S.begin();

	while (it!=S.end()) {
		cout<<(*it)<<" ";
		it++;
	}
}

void printSetMap(map<string,set<string> > &m){
	itr2 it = m.begin();

	while (it != m.end()) {
		 if(it->first == eps || isTerminal(it->first)) {
			it++;
			continue;
		}
		cout<<it->first<<"==>> ";
		printSet(it->second);
		cout<<endl;
		it++;
	}
}

set<string> getFirst(string s) {
	set<string> ans;
	for (int i = 0; i < s.length(); i++) {
		set<string> st = First[toStr(s[i])];
		itr3 it = st.begin();
		bool flag = false;
		while (it != st.end()) {
			if ((*it) == eps)
				flag = true;
			else
				ans.insert((*it));
			it++;
		}
		if (!flag)
			return ans;
	}
	ans.insert(eps);
}

void addFollow(string s1, string s2, itr1 it) {
	if (s1 == eps)
		return;
	int i;
	for (i = 0; i < s1.length() - 1; i++) {
		if (toStr(s1[i]) == s2) {
			string str = s1.substr(i + 1);
			set<string> ans = getFirst(str);

			itr3 sit = ans.begin();
			bool flag = false;
			while (sit != ans.end()) {
				if ((*sit) == eps)
					flag = true;
				else
					Follow[s2].insert((*sit));
				sit++;
			}
			if (flag) {
				if (it->first != toStr(s1[i])) {
					computeFollow(it->first);
					Follow[s2].insert(Follow[it->first].begin(), Follow[it->first].end());
				}
			}
		}
	}

	if (toStr(s1[i]) == s2) {
		if (it->first != toStr(s1[i])) {
			computeFollow(it->first);
			Follow[s2].insert(Follow[it->first].begin(), Follow[it->first].end());
		}
	}
}

void computeFollow(string var) {
	itr1 it = Prod.begin();
	while (it != Prod.end()) {
		vector<string> right = it->second;
		for (int i = 0; i < right.size(); i++) 
			addFollow(right[i], var, it);
		it++;
	}
}

void computeFollowWrapper() {
	Follow[toStr('S')].insert("$");
	itr1 it = Prod.begin();

	while (it != Prod.end()) {
		computeFollow(it->first);
		it++;
	}
}

void addItems(stateptr ptr) {
	itr1 it = Prod.begin();
	while (it != Prod.end()) {
		std::vector<string> v = it->second;
		for (int i = 0; i < v.size(); i++) {
			string tmp = v[i];
			tmp.insert(0, ".");
			ptr->items.insert(make_pair(it->first, ));
		}
		it++;
	}
}

void printState(stateptr ptr) {
	printProductions(ptr->items);
}

void constructDfa(stateptr ptr) {
	prod prods = ptr->items;

}

int main() {
	cout<<"Enter the productions\n";
	inputProductions();
	printProductions(Prod);

	cout<<"Computing First\n";
	computeFirstWrapper();
	//printSetMap(First);

	cout<<"Computing Follow\n";
	computeFollowWrapper();
	//printSetMap(Follow);

	Prod["S"].push_back("E");

	stateptr I0 = new state;
	I0->stateNo = 0;
	addItems(I0);
	constructDfa(I0);
}