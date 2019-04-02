#include<iostream> 
#include<fstream>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include<vector>
using namespace std;

//Prunes the table tab.
void filterTable(vector<pair<vector<string>, int> > &tab, int min_support)
{
	vector<pair<vector<string>, int> >::iterator it = tab.begin();
	for( ; it!=tab.end(); it++)
	{
		if(it->second < min_support)
			{
				tab.erase(it);
				it--;
			}
	}
}

//Checks if two itemsets can be joined.
bool check(vector<string> &v1, vector<string> &v2)
{
	if(v1.size()!=v2.size())
		return false;
	for(int i=0; i<v1.size()-1; i++)
		if(v1[i]!=v2[i])
			return false;
	return true;
}

//Returns the frequency of itemset v.
int getCount(vector<string> &v, vector<string> &table)
{
	int count = 0;
	for(int i=0; i<table.size(); i++)
	{
		bool c = true;
		for(int j=0; j<v.size(); j++)
		{
			if(table[i].find(v[j]) == string::npos)
			{
				c=false; break;
			}
		}
		if(c)
			count++;
	}
	return count;
}

//Prints the contents of tab to FREQUENT_ITEMSET_TABLE.txt file.
void printToFile(fstream &fout, int num, vector<pair<vector<string>, int> > &tab)
{
	vector<pair<vector<string>, int> >::iterator it = tab.begin();
	fout<<"Set of "<<num<<" items."<<endl;
	for( it = tab.begin(); it!=tab.end(); it++)
	{
		vector<string> v = it->first;
		for(int i=0; i<v.size(); i++)
			fout<<v[i]<<" ";
		fout<<it->second<<endl;
	}
	fout<<endl;
}

//Applies join operation on tab.
bool getUnion(vector<pair<vector<string>, int> > &tab, vector<string> &table, int min_support, fstream &fout, int num)
{
	bool needMoreIteration = false;
	vector<pair<vector<string>, int> > newtab;
	vector<string> v;
	for(int i=0; i<tab.size(); i++)
	{
		v.clear();
		for(int j=i+1; j<tab.size(); j++)
		{
			if(check(tab[i].first, tab[j].first))
			{
				vector<string> s = tab[i].first;
				for(int k=0; k<s.size(); k++)
					v.push_back(s[k]);
				v.push_back(tab[j].first[tab[j].first.size() - 1 ]);
				int x = getCount(v, table);
				if(x>=min_support)
				{
					newtab.push_back(pair<vector<string>, int>(v, x));
					needMoreIteration = true;
				}
				v.clear();
			}
			else
				break;
		}
	}
	if(needMoreIteration)
	{
		tab = newtab;
		printToFile(fout, num, tab);
	}
	
	return needMoreIteration;
}



void generateFrequentItemFile(fstream &fin, fstream &fout, int min_support, vector<vector<int> > &table) {
	string s; 
	int num;
	vector<string> vec;
	pair<vector<string>, int> p;
	vector<pair<vector<string>, int> > tab;
	
	//Initialize tab with contents of ITEMS_TRANSACTION_COUNT table.
	while(!fin.eof()) { 
		getline(fin, s, '\t');
		if(fin.eof())
			break;
		vec.push_back(s);
		fin>>num;
		getline(fin, s, '\n');
		tab.push_back(pair<vector<string>, int>(vec, num));
		vec.clear();
	}
	
	//Pruning step. Remove elements having frequency less than minimum support.
	filterTable(tab, min_support);
	
	num=1;
	printToFile(fout, num, tab);
	num++;

	bool iterate = true;
	while(iterate) {
		iterate = getUnion(tab, table, min_support, fout, num);        //Generates new L-Table. Returns true if generated.
		num++;
	}
	
	return;
}

void getTable(fstream &fin, vector<vector<int> > &table)
{
	string s;
	vector<int> tr;
	int it;
	getline(fin, s);
	while(getline(fin, s)){
		string tmp;
		for(int i=0; s[i]; i++){
			if(s[i] == 'I'){
				i++;
				tmp = "";
				while(isdigit(s[i])){
					tmp += s[i];
					i++;
				}
				it = atoi(tmp.c_str());
				//cout<<it<<endl;
				tr.push_back(it);
			}
			else
				continue;
		}
		table.push_back(tr);
		tr.clear();
	}
}

int main()
{
	fstream fin("ITEMS_TRANSACTION_COUNT.txt", ios::in);
	fstream fi("data.txt", ios::in);
	fstream fout("FREQUEBNT_ITEMSET_TABLE.txt", ios::out);
	
	/*int min_support;
	cout<<"Please enter the value of minimum support: ";
	cin>> min_support;*/
	
	//table contains all the entries from TID_TABLE.
	vector<vector<int> > table;
	getTable(fi, table);
	fi.close();
	
	generateFrequentItemFile(fin, fout, min_support, table);
	
	cout<<"\nFrequent Items file generated from ITEMS_TRANSACTION_COUNT.txt with min support value of "<<min_support<<"."<<endl;
	fin.close();
	fout.close();
	return 0;
}
