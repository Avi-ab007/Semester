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
#define BUF_SIZE 1024
#define IP "127.0.0.1"
unsigned long int port[] = {5031, 5032, 5033};
string services[] = {"Service 1", "Service 2", "Service 3"};

int main() {
	int cfd, ret;
	struct sockaddr_in client_addr, server_addr;
	char buf[BUF_SIZE], msg[BUF_SIZE];

	printf("Enter service required(create, read, write, delete): \n");
	scanf("%s", buf);
	string tmp(buf);

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if (cfd < 0) {
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(IP);
	int port_id = 0;
	if (tmp == "read")
		port_id = 1;
	if (tmp == "write")
		port_id = 2;
	client_addr.sin_port = htons(port[port_id]);

	ret = connect(cfd, (struct sockaddr *)&client_addr, sizeof(client_addr));
	if (ret < 0) {
		perror("Connect failed");
		exit(EXIT_FAILURE);
	}

	int pid = getpid();
	stringstream ss; ss<<pid;
	string spid; ss>>spid;
	tmp += " " + spid;
	if (send(cfd, tmp.c_str(), BUF_SIZE, 0) < 0) {
		perror("Send error");
		exit(EXIT_FAILURE);
	}
	printf("Request sent\n");
	int readret = recv(cfd, msg, BUF_SIZE, 0);
	printf("Message from server: %s\n", msg);

	return 0;
}