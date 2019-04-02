#include<bits/stdc++.h>
using namespace std;

int main(){
	vector<vector<int> > list(30);
	vector<int> tmp;
	ifstream fin;
	fin.open("transactions.txt");
	if(!fin)
		cout<<"No File!";
	string buf;
	getline(fin, buf);
	int cur;
	string t = ""; int num;
	while(getline(fin, buf)){
		for(int i=0; buf[i]; i++){
			if(buf[i] == 'T'){
				i++;
				while(buf[i] >= '0' and buf[i] <= '9')
					t += buf[i++];
				if(t.length() > 0){
					num = atoi(t.c_str());
					cur = num;
				}	
				t = "";
			}
			else if(buf[i] == 'I'){
				i++;
				while(buf[i] >= '0' and buf[i] <= '9')
					t += buf[i++];
				if(t.length() > 0){
					num = atoi(t.c_str());
				}
				t = "";
				list[num].push_back(cur);
			}
		}
	}
	ofstream fout;
	fout.open("Items.txt");
	fout<<"Items\t\tTransactions\n\n";
	for(int i=0; i<list.size(); i++){
		if(list[i].size() <= 0)
			continue;
		fout<<"I"<<i<<"\t\t\t";
		for(int j=0; j<list[i].size(); j++){
			fout<<"T"<<list[i][j];
			if(j < list[i].size() -1)
				fout<<",";
		}
		fout<<endl;
	}
}
