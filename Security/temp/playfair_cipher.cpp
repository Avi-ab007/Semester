#include <bits/stdc++.h>
#include <gmp.h>
using namespace std;
vector<int>checkalpha(26,0);
char matrix[5][5];
map <char,pair<int,int> > indices;
string encrypt(string ip){
	string s="";
	for(int i=0;i<ip.length();i++){
		s+=ip[i];
		if(i<ip.length()-1 and ip[i]==ip[i+1]){
			s+='x';
		}
	}
	if(s.length()%2)
		s+='x';
		
	string ans="";
	for(int i=0;i<s.length();i+=2){
		
		int r1=indices[s[i]].first;
		int c1=indices[s[i]].second;
		int r2=indices[s[i+1]].first;
		int c2=indices[s[i+1]].second;
		if(r1==r2){
			ans+=matrix[r1][(c1+1)%5];
			ans+=matrix[r1][(c2+1)%5];
		}
		else if(c1==c2){
			ans+=matrix[(r1+1)%5][c1];
			ans+=matrix[(r2+1)%5][c1];
		}
		else{
			ans+=matrix[r1][c2];
			ans+=matrix[r2][c1];
		}
	}
	return ans;
}
string decrypt(string s){
	string ans="";
	for(int i=0;i<s.length();i+=2){
		int r1=indices[s[i]].first;
		int c1=indices[s[i]].second;
		int r2=indices[s[i+1]].first;
		int c2=indices[s[i+1]].second;
		if(r1==r2){
			ans+=matrix[r1][(c1-1)%5];
			ans+=matrix[r1][(c2-1)%5];
		}
		else if(c1==c2){
			ans+=matrix[(r1-1)%5][c1];
			ans+=matrix[(r2-1)%5][c1];
		}
		else{
			ans+=matrix[r1][c2];
			ans+=matrix[r2][c1];
		}
	}
	string ret="";
	ret+=ans[0];
	for(int i=1;i<ans.length();i++){
		if(ans[i]=='x'){
			if(i+1<ans.length() and ans[i-1] == ans[i+1])
				continue;
			else if(i+1==ans.length())
				continue;
		}
		ret+=ans[i];
	}

	return ret;
}
int main(){
	cout<<"Enter key word: ";
	string key;
	cin>>key;
	int key_ind=0,i,j,al_ind=0;
	for(i=0;i<5;i++){
		for( j=0;j<5;j++){
			if(key_ind<key.length()){
				while(key_ind<key.length() and checkalpha[key[key_ind]-'a'])
					key_ind++;
				if(key_ind<key.length()){
					matrix[i][j] = key[key_ind];
					checkalpha[key[key_ind]-'a']=1;
				if(key[key_ind]=='j' or key[key_ind]=='i'){
					checkalpha[8]=1;
					checkalpha[9]=1;
					indices['i']=make_pair(i,j);
					indices['j']=make_pair(i,j);
					key_ind++;
					continue;				
					//ind =10;
				}
				indices[key[key_ind]] = make_pair(i,j);
				key_ind++;
				}
				else{
					key_ind++;
					j--;
				}
				
			}
			else{
				while(al_ind<26 and checkalpha[al_ind])
					al_ind++;
				if(al_ind>=26)
					break;
				checkalpha[al_ind]=1;
				matrix[i][j] = 'a'+al_ind;
				indices['a'+al_ind] = make_pair(i,j);
				if(al_ind == 8 or al_ind ==9){
					indices['i']=make_pair(i,j);
					indices['j']=make_pair(i,j);
					al_ind=10;
				
				}
				else
					al_ind++;
			}
		}
	}
	map <char,pair<int,int> > :: iterator it;
	for(it=indices.begin();it!=indices.end();it++){
		cout<<it->first<<" : "<<it->second.first<<" , "<<it->second.second<<endl;
	}

	cout<<"The matrix generated is \n";
	for(i=0;i<5;i++){
		for(j=0;j<5;j++)
			cout<<matrix[i][j]<<" ";
		cout<<endl;
	}

string input;
	cout<<"enter word to be encrpyted ";
	cin>>input;
	cout<<"encrypted word is: ";
	string enc = encrypt(input);
	cout<<enc<<endl;
	cout<<"decrypted word is: ";
	cout<<decrypt(enc)<<endl;
	return 0;
}