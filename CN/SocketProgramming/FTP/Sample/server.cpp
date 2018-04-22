#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <string.h> //for memset
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_ntoa()
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header

using namespace std;
char comm[100];
#define PORT 8055
#define MAX_BUF 1024
string lsproc = "./myls";
string getproc = "./myget";
string putproc = "./myproc";

bool isActive = true;

int connect_socket(int port) {
	int s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(port);

	if (connect(s, (struct sockaddr*)&sin, sizeof(sin)) == -1)
		perror("Connect failed before server thread");

	return s;
}
void *lsworker(void *data) {
	string p = *(string *)data;
	int port;
	stringstream ss;
	ss<<p; ss>>port;
	int nsf = connect_socket(port);

	std::string ls = "ls -l";
	FILE* file = popen(ls.c_str(), "r");

	char buffer[MAX_BUF];
	while (!feof(file))
    	fgets(buffer, MAX_BUF, file);

    if (send(nsf, buffer, MAX_BUF, 0) == -1)
    	perror("Send failed in ls");

    pthread_exit(0);
}
int main() {
	struct sockaddr_in s_addr, c_addr;
	socklen_t clen = sizeof c_addr;
	int sfd;
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	s_addr.sin_family = AF_INET;
	s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	s_addr.sin_port = htons(PORT);

	if (bind(sfd, (struct sockaddr*)&s_addr, sizeof(s_addr)) == -1) {
		perror("Bind failed");
		exit(-1);
	}

	listen(sfd, 10);

	while (true) {
		int nsfd;
		if ((nsfd = accept(sfd, (struct sockaddr*)&c_addr, &clen)) == -1) {
			perror("accept failed");
			exit(-1);
		}

		char buf[1024];
		if (recv(nsfd, buf, 1024, 0) == -1) {
			perror("recv failed");
			exit(-1);
		}
		string tmp(buf); stringstream ss;
		ss<<tmp;
		string dcomm, dport;
		ss>>dcomm; ss>>dport;
		if (dcomm == "ls") {
			pthread_t lst;
			pthread_create(&lst, NULL, lsworker, (void*)&dport);
		} 

	}
}