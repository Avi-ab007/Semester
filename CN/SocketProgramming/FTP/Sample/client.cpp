#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <pthread.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
char comm[100];
#define PORT 8055
#define MAX_BUF 1024
string lsproc = "./myls";
string getproc = "./myget";
string putproc = "./myproc";
std::vector<int> dataports;

int get_socket() {
	int port = (rand() + 3000)%(10000);
	while (find(dataports.begin(), dataports.end(), port) != dataports.end())
		port = (rand() + 3000)%(10000);

	dataports.push_back(port);

	struct sockaddr_in sin;
	int s;
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		perror("Socket failed");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(port);

	if (bind(s, (struct sockaddr*)&sin, sizeof(sin)) == -1)
		perror("bind failed");
	if (listen(s, 10) == -1)
		perror("listen failed");

	return s;
}

int main() {
	struct sockaddr_in s_addr, c_addr;
	int sfd;
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	s_addr.sin_port = htons(PORT);
	socklen_t slen = sizeof s_addr;

	int nsfd;
	if ((connect(sfd, (struct sockaddr*)&s_addr, sizeof(s_addr))) == -1) {
		perror("connect failed");
		exit(-1);
	}

	while (true) {
		string cmd;
		printf(">FTP\t");
		cin>>cmd;
		int datafd = get_socket();
		int dport = dataports[dataports.size() - 1];
		if (cmd == "ls") {
			cmd += " ";
			cmd += dport;
			if (send(sfd, cmd.c_str(), MAX_BUF, 0) == -1)
				perror("send failed");
			
			char buf[MAX_BUF];
			// if (recv(sfd, buf, MAX_BUF, 0) == -1)
			// 	perror("recv failed");
			// printf("%s\n", buf);

			char proc[10];	strcpy(proc, lsproc.c_str());
			char nsf[5]; 	strcpy(nsf, to_string(datafd).c_str());
			char *ars[] = {proc, nsf, NULL};
			int cpid = fork();
			if (cpid == 0) {
				execvp(ars[0], ars);
			}
		} 
	}
}