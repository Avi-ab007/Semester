#include<bits/stdc++.h>
using namespace std;

void getFreq(){
	ifstream fin;
	fin.open("trans.txt");
	if(!fin)
		cout<<"No file";
	string arr, tmp = "";
	vector<int> freq(30, 0);
	int num;
	getline(fin, arr);
	arr = "";
	while(getline(fin, arr)){
		for(int i=0; arr[i]; i++){
			if(arr[i] == 'I'){
				i++;
				tmp = "";
				while(arr[i] >= '0' and arr[i] <= '9')
					tmp += arr[i++];
				if(tmp.length() > 0){
					num = atoi(tmp.c_str());
					freq[num]++;
				}
			}
		}
	}
	for(int i=0; i<=20; i++){
		if(freq[i] > 0)
			cout<<"Frequency of Item "<<i<<": "<<freq[i]<<"\n";
	}
}
int main(){
	ofstream out;
	out.open("trans.txt");
	int n;
	cout<<"Number of transactions: "; cin>>n;
	int it;
	cout<<"Enter number of items: "; cin>>it;
	//out<<"TID"<<"     "<<"List of item_IDs\n";
	
	for(int i=0; i<n; i++){
		int no_items = rand()%it + 1;
		int items[no_items];
		bool rep[it+1];
		memset(rep, false, sizeof(rep));
		for(int j=0; j<no_items; j++){
			int x = rand()%(it)+1;
			if(rep[x])
				j--;
			else{
				items[j] = x;
				rep[x] = true;
			}
		}
		sort(items, items+no_items);
		out<<"T"<<(i+1)*100<<"\t";
		for(int j=0; j<no_items; j++){
			out<<"I"<<items[j];
			if(j < no_items-1)
				out<<",";
		}
		out<<"\n";
	}
	out.close();
	//getFreq();
}
