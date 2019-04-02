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
	int frames[f],ref[n],time[f];
	cout<<"enter reference string:\n";
	for(int i=0;i<n;i++)
	cin>>ref[i];
	for(int i=0;i<f;i++) {frames[i]=ref[i]; time[i]=i;}
	int pf=f,cnt=f;
	for(int i=f;i<n;i++)
	{
		int flag=0;
		for(int j=0;j<f;j++)
		{
			if(frames[j]==ref[i]) { time[j]=cnt++;flag=1; break;
			}
		}
		if(!flag)
		{
			int minm=time[0], ind=0;
			for(int l=1;l<f;l++){
				if(time[l]<minm){ minm=time[l]; ind=l;
				}
			}
			frames[ind]=ref[i];
			pf++; time[ind]=cnt++;
		}
	}
	cout<<"number of page faults: "<<pf;
}
