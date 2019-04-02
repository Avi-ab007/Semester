#include<bits/stdc++.h>
using namespace std;

void threshold(int t){
	ifstream fin;
	fin.open("data.txt");
	if(!fin)
		cout<<"No file";
	string arr, tmp = "";
	vector<int> freq(30, 0);
	int num;
	getline(fin, arr);
	arr = "";
	int cnt = 0;
	while(getline(fin, arr)){
		num = 0;
		for(int i=0; arr[i]; i++){
			if(arr[i] == 'I'){
				i++;
				tmp = "";
				while(arr[i] >= '0' and arr[i] <= '9')
					tmp += arr[i++];
				if(tmp.length() > 0){
					num = atoi(tmp.c_str());
					freq[num]++;
					cnt++;
				}
			}
		}
		fin>>tmp;
		tmp = "";
	}
	ofstream fout, out;
	fout.open("L1.txt");
	out.open("C1.txt");
	fout<<"ItemSet\t\tSup. count\n\n";
	out<<"ItemSet\t\tSup. count\n\n";
	for(int i=0; i<=cnt; i++){
		if(freq[i] )
		out<<"I"<<i<<"\t\t\t"<<freq[i]<<"\n";
		if(freq[i] >= t)
			fout<<"I"<<i<<"\t\t\t"<<freq[i]<<"\n";
	}
}

int main(){
	int t;
	cout<<"Enter the threshold amount: "; cin>>t;
	threshold(t);
}
