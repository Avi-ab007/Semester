#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

int main() {
	int fd = open("/tmp/c1", O_RDONLY);
	char *buf;
	read(fd, buf, 10);
	int pid = atoi(buf);
	cout<<pid<<endl;
	int s;
	while (true) {
		cin>>s;
		if (s == 0)
			kill(pid, SIGUSR1);
	}
}