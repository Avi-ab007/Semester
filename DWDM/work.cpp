#include<bits/stdc++.h>
using namespace std;

string createFile(string nm, int file){
	char x[3];
	itoa(23, x, 10);
	//cout<<x<<endl;
	nm = nm+x + ".txt";
	char temp[10];
	int i;
	for(i=0; i<nm.length(); i++)
		temp[i] = nm[i];
	temp[i] = '\0';
	ofstream fout;
	fout.open(temp);
	fout.close();
	return temp;
}

void getfirstc(istream &in,vector<pair<vector<int>,int> > &c){
	int imax=0;
	map<int,int> m;
	while(!in.eof()){
		char s[100];
		in.getline(s,100,'\n');
		//cout<<"s="<<s<<endl;
		if(!in.eof())
		{
			int i;
			for(i=0;i<strlen(s);i++)
			{
				if(s[i]=='I')
				{
					break;
				}
			}
			int sum=0,j;
			for(j=i;j<strlen(s);j++)
			{
				if(s[j]=='I')
				{
				//	cout<<"note="<<sum<<endl;
					if(sum>imax) imax=sum;
					//ans[sum]++;
					if(m.find(sum)==m.end())
					{
						m[sum]=0;
					}
					m[sum]++;
					sum=0;
				}
				else if(s[j]>='0'&&s[j]<='9')
				{
					sum=sum*10+(s[j]-'0');
				}
				else
				{
					continue;
				}
				//cout<<"sum="<<sum<<endl;
			}
			if(sum>imax) imax=sum;
			if(m.find(sum)==m.end())
			{
				m[sum]=0;
			}
			m[sum]++;
			
		}
	}
	for(int i=1;i<=imax;i++)
	{
		int count=0;
		if(m.find(i)==m.end())
		{
			count=0;
		}
		else
		{
			count=m[i];
		}
	//	cout<<i<<"   "<<count<<endl;
	vector<int> temp;temp.push_back(i);
		c.push_back(make_pair(temp,count));
	}
}
void printc(vector<pair<vector<int>,int> > c,int i)
{
	cout<<"PRINTING C"<<i<<endl;
	for(int i=0;i<c.size();i++)
	{
		if(c[i].second == 0)
				continue;
		for(int j=0;j<c[i].first.size();j++)
		{
			
			cout<<"I"<<c[i].first[j];
			if(j!=c[i].first.size())
			{
				cout<<" ";
			}
		}
		cout<<"   "<<c[i].second<<endl;
	}
}
string toString(int i){
	string s = "";
	while(i>0){
		s += i%10 + '0';
		i = i/10;
	}
	int b=0, j = s.length() - 1;
	while(b <= j)
		swap(s[b++], s[j--]);
	return s;
}
void printl(vector<pair<vector<int>,int> > c,int i, int thval) {
	//cout<<"PRINTING L"<<i<<endl;
	char x[3];
	itoa(i, x, 10);
	string nm = "l";
	//cout<<x<<endl;
	nm = nm+x + ".txt";
	char temp[10];
	for(i=0; i<nm.length(); i++)
		temp[i] = nm[i];
	temp[i] = '\0';
	ofstream fout;
	fout.open(temp);
	cout<<temp<<endl;
	//cout<<name<<endl;
	if(!fout)
		cout<<"No file\n";
	for(int i=0;i<c.size();i++)
	{
		for(int j=0;j<c[i].first.size();j++)
		{
			fout<<"I"<<c[i].first[j];
			if(j!=c[i].first.size())
			{
				fout<<" ";
			}
		}
		fout<<"\t"<<c[i].second<<endl;
	}
}
void change(vector<pair<vector<int>,int> > c,vector<pair<vector<int>,int> > &l,int thval)
{
	l.clear();
	for(int i=0;i<c.size();i++)
	{
		if(c[i].second >= thval)
		{
			l.push_back(c[i]);
		}
	}
}
bool check(vector<int> v1,vector<int> v2)
{
//	cout<<"v1size="<<v1.size()<<" first="<<v1[0]<<" second="<<v2[0]<<endl;
	if(v1.size()==1)
	{
		//cout<<"return true"<<endl;
		return true;
	}
	int i=0,j=0;
	while(i<v1.size()-1)
	{
		if(v1[i]!=v2[j])
		{
			return false;
		}
		i++;j++;
	}
	return true;
}

bool find(vector<int> hs,vector<int> n)
{
	for(int i=0;i<n.size();i++)
	{
		int j;
		for(j=0;j<hs.size();j++)
		{
			if(n[i]==hs[j])
			{
				break;
			}
		}
		if(j==hs.size()) {
			return false;
		}
	}
//	cout<<"true"<<endl;
	return true;
}

bool match(vector<int> a, vector<int> b){
	//cout<<a.size()<<" "<<b.size()<<endl;
	int i = 0;
	while(i < a.size()){
		//cout<<a[i]<<" "<<b[i]<<endl;
		if(a[i] != b[i])
			return false;
		i++;
	}
	return true;
}

void getSubs(int i, vector<int> &subs, vector<vector<int> > &ans, vector<int> &A, int size){
	/*if(i == A.size()){
		if(subs.size() == size) 
			ans.push_back(subs);
		return;
	}
	getSubs(i+1, subs, ans, A, size);
	subs.push_back(A[i]);
	getSubs(i+1, subs, ans, A, size);
	subs.pop_back();*/
	ans.clear();
	for(int i=0; i<A.size(); i++){
		subs.clear();
		for(int j = 0; j<A.size(); j++){
			if(i != j)
				subs.push_back(A[j]);
		}
		ans.push_back(subs);
	}
}

bool prune(vector<int> temp, vector<pair<vector<int>,int> > &l, int size) {
	vector<vector<int> > subs; 
	vector<int> sets;
	getSubs(0, sets, subs, temp, size);
	/*cout<<"Prune at size "<<size<<endl;
	for(int i=0; i<subs.size(); i++){
		for(int j=0; j<subs[i].size(); j++)
			cout<<subs[i][j]<<" ";
		cout<<endl;
	}*/
	int cnt = 0;
	for(int i=0; i<subs.size(); i++) {
		for(int j=0; j < l.size(); j++) {
			if(match(subs[i], l[j].first)) {
				cnt++;
				break;
			}
		}
	}
	return cnt == subs.size();
}
void join(vector<vector<int> > &v,vector<pair<vector<int>,int> > &l, int rep) {
	v.clear();
	for(int i=0;i<l.size();i++) {
		vector<int> temp1=l[i].first;
		for(int j=i+1;j<l.size();j++) {
			vector<int> temp2=l[j].first;
			if(check(temp1,temp2)) {
				vector<int> temp3=temp1;
				temp3.push_back(temp2[temp2.size()-1]);
				if(prune(temp3, l, rep-1))
					v.push_back(temp3);
			}
		}
	}
}

vector<pair<vector<int>,int> > getcount(istream &in,vector<vector<int> > v)
{
	vector<pair<vector<int>,int> > c;
	for(int i=0;i<v.size();i++)
	{
		c.push_back(make_pair(v[i],0));
	}
	while(!in.eof()) {
		vector<int> temp;
		char s[100];
		in.getline(s,100,'\n');
		int i;
		for(i=0;i<strlen(s);i++){
		if(s[i]=='I')
			{
				break;
			}
		}
		int sum=0,j;
		for(j=i;j<strlen(s);j++){
			if(s[j]=='I'){
				temp.push_back(sum);
				sum=0;
			}
			else if(s[j]>='0'&&s[j]<='9'){
				sum=sum*10+(s[j]-'0');
			}
			else{
				continue;
			}
			//cout<<"sum="<<sum<<endl;
		}
		temp.push_back(sum);
		for(i=0;i<v.size();i++)
		{
			if(find(temp,v[i]))
			{
				c[i].second++;
			}
		}
	}
	return c;
}

void printv(vector<vector<int> > v,int i, int thval) {
	cout<<"PRINTING V"<<i<<endl;
	for(int i=0;i<v.size();i++) {
		for(int j=0;j<v[i].size();j++) {
			cout<<"I"<<v[i][j];
			if(j!=v[i].size()-1) {
				cout<<" ";
			}
		}
		cout<<endl;
	}
}

void generateFile(){
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
		for(int j=0; j<no_items; j++) {
			out<<"I"<<items[j];
			if(j < no_items-1)
				out<<",";
		}
		out<<"\n";
	}
	out.close();
}

int main() {
	int thval;
	generateFile();
	cout<<"Enter the threshold value: ";
	cin>>thval;
	ifstream in;in.open("trans.txt");
	vector<pair<vector<int>,int> > c,l;
	int rep=1;
	getfirstc(in,c);
	//printc(c,rep);
	change(c,l,thval);
	printl(l,rep, thval);
	vector<vector<int> > v;
	while(l.size()!=0) {
		rep++;
		join(v, l, rep);
		if(v.size()==0){
			break;
		}
		ifstream in1;
		in1.open("trans.txt");
		c=getcount(in1,v);
		in1.close();
		//printc(c,rep);
		change(c,l,thval);
		printl(l,rep, thval);
	}
	in.close();
	return 0;
}
