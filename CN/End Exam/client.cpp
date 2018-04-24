#include <bits/stdc++.h>
#include <time.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/un.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <pcap.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>

using namespace std;
#define IP "127.0.0.1"

int PORTS[] = {7041, 7052, 7063};

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./client <client no>\n");
		exit(EXIT_FAILURE);
	}

	int num = atoi(argv[1]);
	printf("Client port: %d\n", PORTS[num-1]);
	int sfd;
	struct sockaddr_in serv_addr, cli_addr;
	int port_no, srv;
	printf("Enter service required.\n");
	cin>>srv;
	if (srv == 1) port_no = 5031;
	if (srv == 2) port_no = 5042;
	if (srv == 3) port_no = 5053;

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
		perror("socket failed");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);

	cli_addr.sin_family = AF_INET;
	cli_addr.sin_port = htons(PORTS[num-1]);
	cli_addr.sin_addr.s_addr = inet_addr(IP);

	int value = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
		perror("setsockopt failed");
	}
	
	if (bind(sfd,(struct sockaddr *) &cli_addr,sizeof(cli_addr))==-1)
		perror("Bind failed");



	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
		perror("connect failed");

	char buf[1024];
	if (recv(sfd, buf, 1024, 0) == -1)
		perror("recv failed");
	printf("%s\n", buf);
}