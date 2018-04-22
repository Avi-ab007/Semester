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
	int fd = open("/tmp/writeTo", O_RDONLY);
	if (fd <=0)
		printf("Opening failed\n");
	char buf[100];
	
	while (true) {
		memset(buf, 0, 100);
		sleep(1);
		read(fd, buf, 100);
		if (buf[0] != '0' || buf[0] != ' ')
			printf("buf: %s\n", buf);
	}
}