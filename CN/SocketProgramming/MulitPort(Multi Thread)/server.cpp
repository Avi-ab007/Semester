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

struct clientInfo {
	string serviceName;
	int service_id;
	int nsfd;
};

void *ServiceHandler(void *data) {
	struct clientInfo cObj = *(struct clientInfo *)data;
	int nfd = cObj.nsfd;
	int sid = cObj.service_id;
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
	msg += " granted";
	send(nfd, msg.c_str(), BUF_SIZE, 0);

	pthread_exit(0);
}

int main() {
	int sfd[3], nfd[3], ret[3];
	struct sockaddr_in server_addr[3], client_addr;
	pid_t child_pid[3];

	
	for (int i = 0; i < 3; i++) {
		server_addr[i].sin_family = AF_INET;
		server_addr[i].sin_addr.s_addr = inet_addr(IP);
		server_addr[i].sin_port = htons(port[i]);


		sfd[i] = socket(AF_INET, SOCK_STREAM, 0);

		if (sfd[i] < 0) {
			perror("Socket failed");
			exit(EXIT_FAILURE);
		}

		ret[i] = bind(sfd[i], (struct sockaddr *)&server_addr[i], sizeof(server_addr[i]));

		if (ret[i] < 0) {
			perror("Bind failed");
			exit(EXIT_FAILURE);
		}

		ret[i] = listen(sfd[i], 100);
		if (ret[i] < 0) {
			perror("Listen failed");
			exit(EXIT_FAILURE);
		}
	}

	fd_set readfds;
	struct timeval timeout;

	while (true) {
		FD_ZERO(&readfds);
		int MAX_FD = sfd[0];
		for (int i = 0; i < 3; ++i) {
			FD_SET(sfd[i], &readfds);
			MAX_FD = max(MAX_FD, sfd[i]);
		}
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;

		int sret = select(MAX_FD, &readfds, NULL, NULL, &timeout);
		if (sret == 0)
			printf("Timeout\n");
		if (sret < 0) {
			perror("Select error");
			exit(EXIT_FAILURE);
		} else {

			for (int i = 0; i < 3; i++) {
				if (FD_ISSET(sfd[i], &readfds)) {
					printf("Serving on Port %d\n", (int)port[i]);
					nfd[i] = accept(sfd[i], (struct sockaddr *)&client_addr, (socklen_t *)&client_addr);
					if (nfd[i] < 0) {
						perror("Accept failed");
						exit(EXIT_FAILURE);
					}

					printf("Connection established with %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
					struct clientInfo clientObj;
					clientObj.nsfd = nfd[i];
					clientObj.service_id = i;
					pthread_t newThread;
					pthread_create(&newThread, NULL, ServiceHandler, (struct clientInfo *)&clientObj);
				} 
			}
		}
	}

	return 0;
}
