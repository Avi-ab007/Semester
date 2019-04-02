#include<bits/stdc++.h>
using namespace std;
void subset(int i, vector<int> &subs, vector<vector<int> > &ans, vector<int> &A){
	if(i == A.size()){
		if(subs.size() == 2)
			ans.push_back(subs);
		return;
	}
	subset(i+1, subs, ans, A);
	subs.push_back(A[i]);
	subset(i+1, subs, ans, A);
	subs.pop_back();
}
int main(){
	ifstream fin;
	vector<int> present;
	vector<int> item;
	int c2cnt[6][6];
	memset(c2cnt, 0, sizeof(c2cnt));
	string cur, tmp = "";
	int it ;
	/*fin.open("L1.txt");
	getline(fin, cur);
	while(getline(fin, cur)){
		for(int i=0; cur[i]; i++){
			if(cur[i] == 'I'){
				i++;
				tmp = "";
				while(isdigit(cur[i])){
					tmp += cur[i];
					i++;
				}
				it = atoi(tmp.c_str());
				present.push_back(it);
			}
			else
				continue;
		}
	}
	fin.close();
	fin.open("data.txt");
	getline(fin, cur);
	while(getline(fin, cur)){
		for(int i=0; cur[i]; i++){
			if(cur[i] == 'I') {
				i++;
				tmp = "";
				while(isdigit(cur[i])){
					tmp += cur[i];
					i++;
				}
				it = atoi(tmp.c_str());
				if(find(present.begin(), present.end(), it) != present.end())
					item.push_back(it);
			}
			else
				continue;
		}
		for(int i=0; i<item.size(); i++){
			for(int j=i+1; j<item.size(); j++)
				c2cnt[item[i]][item[j]]++;
		}
		item.clear();
	}
	fin.close();
	ofstream fout, out;
	fout.open("C2.txt");
	out.open("L2.txt");
	fout<<"Itemset\t\t\tSup Count\n";
	out<<"Itemset\t\t\tSup Count\n";
	int cnt = 0;
	cout<<"Enter the threshold support count: "; cin>>cnt;
	for(int i=0; i<present.size(); i++){
		for(int j=i+1; j<present.size(); j++){
			fout<<"I"<<present[i]<<" "<<"I"<<present[j]<<"\t\t\t"<<c2cnt[present[i]][present[j]]<<endl;
			if(c2cnt[present[i]][present[j]] >= cnt)
				out<<"I"<<present[i]<<" "<<"I"<<present[j]<<"\t\t\t"<<c2cnt[present[i]][present[j]]<<endl;
		}
	}
	fout.close(); out.close();*/
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fin.open("L2.txt");
	vector<vector<int> > table;
	item.clear();
	getline(fin, cur);
	while(getline(fin, cur)){
		for(int i=0; cur[i]; i++){
			if(cur[i] == 'I'){
				i++;
				tmp = "";
				while(isdigit(cur[i])){
					tmp += cur[i];
					i++;
				}
				it = atoi(tmp.c_str());
				item.push_back(it);
			}
		}
		table.push_back(item);
		item.clear();
	}
	vector<vector<int> > c3;
	vector<int> subs;
	vector<vector<int> > supers;
	for(int i=0; i<table.size() - 1; i++){
		for(int j=i+1; j<table.size(); j++){
			if(table[i][0] == table[j][0]){
				item.clear();
				item.push_back(table[i][0]);
				item.push_back(table[i][1]);
				item.push_back(table[j][1]);
				subset(0, subs, supers, item);
				bool flag = true;
				for(int k=0; k<supers.size(); k++){
					if(find(table.begin(), table.end(), supers[k]) == table.end()){
						flag = false;
						break;
					}
				}
				if(flag){
					c3.push_back(item);
					subs.clear(), supers.clear();
				}
			}
		}
	}
	
}
