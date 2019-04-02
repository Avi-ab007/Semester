#include<bits/stdc++.h>
using namespace std;
int main()
{
	int f,n;
	cout<<"enter number of frames: ";
	cin>>f;
	cout<<"number of pages: ";
	cin>>n;
	if(n<f){
		cout<<"number of page faults = "<<n;
		return 0;
	}
	int frames[f];
	int ref[n];
	cout<<"enter reference string:\n";
	for(int i=0;i<n;i++)
	cin>>ref[i];
	for(int i=0;i<f;i++) frames[i]=ref[i];
	int pf=f,cnt=0;
	for(int i=f;i<n;i++)
	{
		int flag=0;
		for(int j=0;j<f;j++)
		{
			if(frames[j]==ref[i]) { flag=1; break;
			}
		}
		if(!flag)
		{
			frames[cnt]=ref[i];
			pf++; cnt=(cnt+1)%f;
		}
	}
	cout<<"number of page faults: "<<pf;
}
