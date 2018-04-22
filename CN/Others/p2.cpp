#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
	cout<<"This is the program P2.\n";
	char *fid[] = {"/home/avinash/Documents/CN/p3", NULL, NULL};
	int pid = fork();
	if (pid > 0) {
		execvp(fid[0], fid);
	} else {
		cout<<"P1 exiting.\n"; 
	}
}