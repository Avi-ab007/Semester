#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main(){
	cout<<"This is the program P3.\n";
	char *fid[] = {"/home/avinash/Documents/CN/p4", NULL, NULL};
	int pid = fork();
	if (pid > 0) {
		execvp(fid[0], fid);
	} else {
		cout<<"P3 exiting.\n"; 
	}
}