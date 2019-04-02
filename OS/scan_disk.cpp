#include<bits/stdc++.h>
using namespace std;
int main()
{
	int head,n;
	string dir;
	cout<<"enter head postion: ";
	cin>>head;
	cout<<"enter direction: ";
	cin>>dir;
	cout<<"number of requests: ";
	cin>>n;
	int rq[n+2];
	cout<<"enter requests:\n";
	rq[0]=0;
	for(int i=1;i<=n;i++) cin>>rq[i];
	rq[n+1]=199;
	int hm=0,check[n+2],cnt=0;
	for(int i=0;i<(n+2);i++) check[i]=0;
	while(cnt<n)
	{
		int minm=1000,ind;
		for(int i=0;i<(n+2);i++)
		{
			if(!check[i]){	
				if(((!dir.compare("left"))&&rq[i]<head) || ((!dir.compare("right"))&&rq[i]>head))
				{
					if(abs(rq[i]-head)<minm) { minm=abs(rq[i]-head);ind=i;}
				}
			}
		}
		hm+=abs(rq[ind]-head);
		check[ind]=1;
		head=rq[ind];
		cout<<head<<" ";
		if(head==0) dir="right";
		if(head==199) dir="left";
		if(head!=0 && head!=199)cnt++;
	}
	cout<<"\nNumber of head movements: "<<hm;
}
