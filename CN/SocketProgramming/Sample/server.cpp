#include <bits/stdc++.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;
#define PORT 8055

int main() {
	/*Variables*/
	int server_fd;
	struct sockaddr_in srv_addr, client_addr;
	int nfd;
	char buf[1024];
	int rval;

	/*Create socket*/
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1) {
		perror("Failed to create socket");
		exit(1);
	}

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("172.30.35.80");
	srv_addr.sin_port = htons(PORT);


	/*Call bind*/
	if (bind(server_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0) {
		perror("Bind failed");
		exit(1);
	}


	/*Listen*/
	listen(server_fd, 5);


	printf("Waiting for accept\n");
	/*Accept*/
	unsigned int len = sizeof(client_addr);
	{
		printf("Accepting request \n");
		nfd = accept(server_fd, (struct sockaddr *) &client_addr, (socklen_t *)&len);

		if (nfd <0)
			perror("Accept failed");
		else {
			printf("Accepted connection from IP : %s Port : %d \n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port) );
			sockaddr_in saddr;
			socklen_t slen = sizeof(saddr);
			getsockname(server_fd, (struct sockaddr*)&saddr, &slen);
			printf("Sockname: %s:%d\n", inet_ntoa(saddr.sin_addr), ntohs(slen));
			memset(buf, 0, sizeof(buf));
			rval = recv(nfd, buf, 1024, 0);
			printf("Recv = %d \n",rval);
			if (rval  < 0)
				perror("Reading stream message error.");
			// else if (rval == 0)
			// 	printf("Closing connection\n");
			else{
				printf("Printing buffer \n");
				printf("MSG: %s\n", buf);
				close(nfd);	
			}

			
			
		}
	}
}