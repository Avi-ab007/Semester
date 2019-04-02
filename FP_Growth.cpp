#include<bits/stdc++.h>
#define noOfItems 5
using namespace std;
typedef
struct fpnode{
	int item_id, tr_cnt;
	int c_cnt;
	fpnode *cds[noOfItems+1], *par, *next;
	//map<int, int> pos;
	fpnode(int id, int cnt){
		item_id = id;
		tr_cnt = cnt;
		c_cnt = 0;
		par = next = NULL;
		for(int i=0; i<=noOfItems; i++)
			cds[i] = NULL;
	}
}*fptr;
fptr nextptr[noOfItems+1];
struct items {
	int item_id, sup_cnt;
	fptr strt;
	items(int id, int cnt){
		item_id = id;
		sup_cnt = cnt;
	}
};

vector<items> table;
map<int, int> mstr;

bool comp2(const int &a, const int &b){
	return mstr[a] < mstr[b];
}
bool compare(const items &i1, const items &i2){
	return i1.sup_cnt > i2.sup_cnt;
}

void getTable(vector<items> &c){
	ifstream in;
	in.open("trans.txt");
	int it;
	string buf;
	int freq[noOfItems + 1];
	memset(freq, 0, sizeof(freq));
	while(in){
		getline(in, buf);
		stringstream ss;
		ss<<buf;
		ss>>it;
		while(ss>>it)
			freq[it]++;
		if(in.eof())
			break;
	}
	for(int i=1; i<= noOfItems; i++){
		items x(i, freq[i]);
		c.push_back(x);
	}
	in.close();
}

/*void generateFile(){
	ofstream out;
	out.open("trans.txt");
	int n;
	cout<<"Number of transactions: "; cin>>n;
	int it;
	cout<<"Enter number of items: "; cin>>it;
	//out<<"TID"<<"     "<<"List of item_IDs\n";
	noOfItems = it;
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
		out<<(i+1)*100<<"\t";
		for(int j=0; j<no_items; j++) {
			out<<items[j]<<" ";
		}
		out<<"\n";
	}
	out.close();
}*/

void insert(fptr &root, vector<int> &tr, int i){
	if(i == tr.size())
		return;
	cout<<"Insert "<<tr[i]<<endl;
	if(root->cds[tr[i]] == NULL){
		cout<<"Not Present\n";
		root->c_cnt++;
		root->cds[tr[i]] = new fpnode(tr[i], 1);
		root->cds[tr[i]]->par = root;
		if(nextptr[tr[i]] == NULL){
			nextptr[tr[i]] = root->cds[tr[i]];
			int ind;
			for(int j=0; j<table.size(); j++){
				if(table[j].item_id == tr[i]){
					ind = j;
					break;
				}
			}
			table[ind].strt = root->cds[tr[i]];
		}
		else{
			nextptr[tr[i]]->next = root->cds[tr[i]];
			nextptr[tr[i]] = root->cds[tr[i]];
		}
	}
	
	else{
		cout<<"Present\n";
		root->cds[tr[i]]->tr_cnt++;
	}
	insert(root->cds[tr[i]], tr, i+1);
}
void generateTree(fptr &root, vector<items> &table){
	ifstream in;
	in.open("trans.txt");
	vector<int> tr;
	while(!in.eof()){
		tr.clear();
		string buf;
		getline(in, buf);
		stringstream ss;
		ss<<buf;
		int x;
		ss>>x;
		while(ss>>x){
			if(find(tr.begin(), tr.end(), x) == tr.end())
				tr.push_back(x);
		}
		cout<<"Adding: ";
		sort(tr.begin(), tr.end(), comp2);
		insert(root, tr, 0);
		cout<<endl;
	}
}
void mapTable(vector<items> &table){
	for(int i=0; i<table.size(); i++){
		cout<<table[i].item_id<<" "<<table[i].sup_cnt<<endl;
		mstr[table[i].item_id] = i;
	}
}

void printTree(fptr head){
	if(!head)
		return;
	cout<<head->item_id<<":"<<head->tr_cnt<<" ";
	for(int i=1; i<=noOfItems; i++){
		printTree(head->cds[i]);
	}
}

void levelPrint(fptr p){
	if(!p)
		return;
	queue<fptr> q;
	fptr tmp;
	q.push(p);
	q.push(NULL);
	while(q.size() > 1){
		tmp=q.front();
		q.pop();
		if(tmp==NULL){
			q.push(NULL);
			cout<<endl;
		}
		else{
			cout<<tmp->item_id<<":"<<tmp->tr_cnt<<" ";
			for(int i=1; i<=noOfItems; i++){
				if(tmp->cds[i])
					q.push(tmp->cds[i]);
			}
		}
	}
}

vector<pair<int,vector<pair<vector<int>,int> > > >PatternBase;
pair<vector<int>,int> storePath(fptr temp){
	vector<int> nm;
	fptr jh=temp;
	if(!temp->par){
		cout<<"Nop\n";
		return make_pair(nm, 0);
	}
	temp=temp->par;
	while(temp->par){
		nm.push_back(temp->item_id);
		temp=temp->par;
	}
	return make_pair(nm,jh->tr_cnt);
}

void createPB(){
	int i;
	fptr temp;
	for(i=table.size()-1;i>=0;i--){
		temp=table[i].strt;
		vector<pair<vector<int>,int> >  nop;
		while(temp)
		{
			pair<vector<int>,int> ach=storePath(temp);
			if(ach.first.size()>0)
			nop.push_back(ach);
			temp=temp->next;
		}
		if(nop.size())
		PatternBase.push_back(make_pair(table[i].item_id,nop));
	}
}


void printPatternBase(){
	for(int i=0;i<PatternBase.size();i++)
	{
		
		cout<<PatternBase[i].first<<" "<<endl;
		vector<pair<vector<int>,int> > temp=PatternBase[i].second;
		for(int j=0;j<temp.size();j++){
		vector<int> t=temp[j].first;
		for(int k=0;k<t.size();k++)
			cout<<t[k]<<" ";
			cout<<": ";
			cout<<temp[j].second<<endl;
		}
	}
}
int main(){
	//generateFile();
	//noOfItems = 5;
	for(int i=0; i<=noOfItems; i++)
		nextptr[i] = NULL;
	
	fptr root = NULL ;
	root = new fpnode(-1, 0);
	getTable(table);
	sort(table.begin(), table.end(), compare);
	mapTable(table);
	generateTree(root, table);
	//printTree(root);
	levelPrint(root);
	cout<<endl;
	createPB();
	printPatternBase();
}
