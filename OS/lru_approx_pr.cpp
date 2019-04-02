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
	int frames[f],ref[n],refbit[f],time[f];
	cout<<"enter reference string:\n";
	for(int i=0;i<n;i++)
	cin>>ref[i];
	for(int i=0;i<f;i++) {frames[i]=ref[i]; refbit[i]=0;time[i]=i;}
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
			int ind;
			while(1)
			{
				int minm=time[0]; ind=0;
				for(int l=1;l<f;l++){
				if(time[l]<minm){ minm=time[l]; ind=l;}
				}
				if(!refbit[ind]) {ind=cnt;break;}
				else refbit[cnt]=0;
				cnt=(cnt+1)%f;
			}
			frames[ind]=ref[i]; refbit[ind]=1;
			pf++; 
		}
	}
	cout<<"number of page faults: "<<pf;
}
