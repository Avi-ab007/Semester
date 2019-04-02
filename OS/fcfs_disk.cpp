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
	int hm=0;
	for(int i=0;i<n;i++)
	{
		hm+=abs(rq[i]-head);
		head=rq[i];
		cout<<head<<" ";
	}
	cout<<"\nNumber of head movements: "<<hm;
}
