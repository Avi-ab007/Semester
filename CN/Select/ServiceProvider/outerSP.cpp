#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

string tmpfifo = "/tmp/tmpfifo";

int main() {
	int fd = open(tmpfifo.c_str(), O_RDONLY);

	char buf[100];
	while (true) {
		memset((void *)buf, 0, 100);
		if (read(fd, buf, 100) <= 0){
			printf("Waiting for client\n");
			sleep(1);
			continue;
		}
		string rec(buf);
		stringstream ss;
		string pid, client, service;
		ss<<rec;
		ss>>pid; ss>>client; ss>>service;

		printf("%s: %s granted service: %s\n", pid.c_str(), client.c_str(), service.c_str());
	}
}