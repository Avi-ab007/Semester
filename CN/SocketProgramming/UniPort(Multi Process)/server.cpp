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
	int sfd, nfd, ret;
	struct sockaddr_in server_addr, client_addr;
	pid_t child_pid;

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IP);
	server_addr.sin_port = htons(PORT);

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd < 0) {
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	ret = bind(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	ret = listen(sfd, 100);
	if (ret < 0) {
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}

	while (true) {
		nfd = accept(sfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr);
		if (nfd < 0) {
			perror("Accept failed");
			exit(EXIT_FAILURE);
		}

		printf("Connection established with %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		child_pid = fork();
		if (child_pid == 0) {
			printf("Forked new process\n");
			close(sfd);
			break;
		} else {
			printf("Main thread continuing\n");
		}
	}
	char buf[1024];
	int readret = recv(nfd, buf, BUF_SIZE, 0);
	if (readret < 0) {
		perror("Receive error");
		exit(EXIT_FAILURE);
	}

	string service(buf), pid;
	stringstream ss;
	ss<<service;
	ss>>service;
	ss>>pid;
	printf("Server alloting service %s to client %s\n", service.c_str(), pid.c_str());
	string msg = service;
	msg += "granted";
	send(nfd, msg.c_str(), BUF_SIZE, 0);

	return 0;
}
