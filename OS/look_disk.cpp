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
	int rq[n];
	cout<<"enter requests:\n";
	for(int i=0;i<n;i++) cin>>rq[i];
	int hm=0,check[n],cnt=0;
	for(int i=0;i<n;i++) check[i]=0;
	int min=rq[0], max=rq[0];
	for(int i=0;i<n;i++){
		if(rq[i]<min) min=rq[i];
		if(rq[i]>max) max=rq[i];
	}
	while(cnt<n)
	{
		int minm=1000,ind;
		for(int i=0;i<n;i++)
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
		if(head==min) dir="right";
		if(head==max) dir="left";
		cnt++;
	}
	cout<<"\nNumber of head movements: "<<hm;
}
