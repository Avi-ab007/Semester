#include<bits/stdc++.h>
using namespace std;
int main()
{
	int head,n;
	cout<<"enter head postion: ";
	cin>>head;
	cout<<"number of requests: ";
	cin>>n;
	int rq[n];
	cout<<"enter requests:\n";
	for(int i=0;i<n;i++) cin>>rq[i];
	int hm=0,check[n],cnt=0;
	for(int i=0;i<n;i++) check[i]=0;
	while(cnt<n)
	{
		int minm=1000,ind;
		for(int i=0;i<n;i++)
		{
			if(!check[i]){	
			if(abs(rq[i]-head)<minm) { minm=abs(rq[i]-head);
			ind=i;}
			}
		}
		hm+=abs(rq[ind]-head);
		check[ind]=1;
		head=rq[ind];
		cout<<head<<" ";
		cnt++;
	}
	cout<<"\nNumber of head movements: "<<hm;
}
