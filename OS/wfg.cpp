#include <bits/stdc++.h>
using namespace std;

int graph[20][20];
bool vis[20], recStack[20];
int n;

bool detect(int v){
	if(!vis[v]){
		vis[v] = recStack[v] = true;
		for(int i=0; i<n; i++){
			if(graph[v][i]){
				if(!vis[i] and detect(i))
					return true;
				else if(recStack[i])
					return true;
			}
		}
	}
	recStack[v] = false;
	return false;
}

int main(){
	memset(vis, false, sizeof(vis));
	memset(recStack, false, sizeof(recStack));
	int v, u;
	cout<<"Enter number of processes: ";
	cin>>n;
	cout<<"Enter the edges: ";
	cin>>u>>v;
	while(true){
		graph[u][v] = 1;
		cin>>u;
		if(u == -1)
			break;
		cin>>v;
	}
	bool flag = false;
	for(int i=0; i < n; i++){
		if(detect(i)){
			flag = true;
			break;
		}
	}
	if(flag)
		cout<<"System is deadlocked.\n";
	else
		cout<<"System is in safe state.\n";
}