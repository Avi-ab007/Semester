#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
	cout<<"This is the program P1.\n";
	char* fid[] = {"/home/avinash/Documents/CN/p2", NULL, NULL};
	int pid = fork();
	if (pid > 0) {
		execvp(fid[0], fid);
	} else {
		cout<<"Main exiting.\n";
	}
}