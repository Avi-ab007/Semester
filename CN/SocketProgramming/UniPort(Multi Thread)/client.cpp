#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
#define BUF_SIZE 1024
#define IP "127.0.0.1"
#define PORT 5000

int main() {
	int cfd, ret;
	struct sockaddr_in client_addr, server_addr;
	char buf[BUF_SIZE], msg[BUF_SIZE];

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cfd < 0) {
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(IP);
	client_addr.sin_port = htons(PORT);

	ret = connect(cfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
	if (ret < 0) {
		perror("Connect failed");
		exit(EXIT_FAILURE);
	}

	printf("Enter service required: \n");
	scanf("%s", buf);
	string tmp(buf);
	int pid = getpid();
	stringstream ss; ss<<pid;
	string spid; ss>>spid;
	tmp += " " + spid;
	send(cfd, tmp.c_str(), BUF_SIZE, 0);
	printf("Request sent\n");
	int readret = recv(cfd, msg, BUF_SIZE, 0);
	printf("Message from server: %s\n", msg);

	return 0;
}