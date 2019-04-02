#include<bits/stdc++.h>
using namespace std;

struct dtype{
	vector<int> itset;
	int sup;
	dtype(){
		sup = 0;
	}
};

int noOfItems, noOfTrans, minSup;
vector<dtype> table;

void generateFile(){
	ofstream fout;
	fout.open("trans.txt");
	cout<<"Enter number of transactions: "; cin>>noOfTrans;
	cout<<"Enter number of items: "; cin>>noOfItems;
	cout<<"Enter minimum support count: "; cin>>minSup;
	
	for(int i=1; i<=noOfTrans; i++){
		int items = rand()%noOfItems + 1;
		fout<<i*100<<"\t\t";
		for(int j=1; j<=items; j++)
			fout<<j<<" ";
		fout<<endl;
	}
	fout.close();
}

void createFile(int x, char name[]){
	name[0] = 'L';
	char num[3];
	itoa(x, num, 10);
	for(int i=0; num[i]; i++)
		name[i+1] = num[i];
	int i;
	for(i=0; name[i]; i++);
	i--;
	name[i++] = '.';
	name[i++] = 't';
	name[i++] = 'x';
	name[i++] = 't';
	name[i++] = '\0';
	ofstream fout;
	fout.open(name);
	fout.close();
}
void initiate(){
	ifstream fin;
	fin.open("trans.txt");
	stringstream ss;
	int freq[noOfItems+1];
	memset(freq, 0, sizeof(freq));
	while(!fin.eof()){
		ss.str( std::string() );
		ss.clear();	
		string s;
		getline(fin, s);
		ss<<s;
		//cout<<s<<endl;
		int x;
		ss>>x;
		//cout<<x<<endl;
		while(ss>>x)
			freq[x]++;
		if(fin.eof())
			break;
	}
	fin.close();
	char name[10];
	createFile(1, name);
	ofstream fout;
	fout.open(name);
	if(!fout)
		cout<<"No File!\n";
	for(int i=1; i<=noOfItems; i++){
		dtype tmp;
		tmp.itset.push_back(i);
		tmp.sup = freq[i];
		table.push_back(tmp);
		if(freq[i] >= minSup)
			fout<<i<<"\t\t"<<freq[i]<<'\n';
	}
}

void getC(vector<dtype> &tmpc, int iter){
	tmpc.clear();
	for(int i=0; i<table.size(); i++){
		for(int j=i+1; j<table.size(); j++){
			dtype t;
			if(iter == 2){
				t.itset.push_back(i);
				t.itset.push_back(j);
				tmpc.push_back(t);
			}
			else{
				if(table[i].itset[iter-2] == table[j].itset[iter-2]){
					t.itset = table[i].itset;
					t.itset.push_back(table[j].itset[iter-1]);
					tmpc.push_back(t);
				}
			}
		}
	}
}

void count(vector<int> &tr, vector<dtype> &tmpc){
	for(int i=0; i<tmpc.size(); i++){
		if(tmpc[i].itset == tr)
			tmpc[i].sup++;
	}
}
void getCount(vector<dtype> &tmpc, int iter){
	ifstream fin;
	fin.open("trans.txt");
	stringstream ss;
	string s;
	while(!fin.eof()){
		getline(fin, s);
		ss<<s;
		int x;
		ss>>x;
		vector<int> tr;
		while(ss>>x)
			tr.push_back(x);
		for(int i=0; i<tr.size(); i++){
			
			count(tr, tmpc);
		}
	}
}
int main(){
	//generateFile();
	noOfItems = 5;
	initiate();
	/*for(int i=0; i<table.size(); i++){
		cout<<table[i].itset[0]<<" "<<table[i].sup<<endl;
	}*/
	int iter;
	for(iter = 2; table.size() != 0; iter++){
		getC(iter);
	}
}
