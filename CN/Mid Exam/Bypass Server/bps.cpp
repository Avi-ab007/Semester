#include <time.h>
#include <bits/stdc++.h>
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
#include <errno.h>
#include <netinet/if_ether.h>
#include <net/ethernet.h>
#include <netinet/ether.h>
#include <netinet/udp.h>

using namespace std;
int main() {
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len = sizeof(cli_addr);

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8055);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");

	listen(sfd,100);

	while (true) {
		int nsfd;
		if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
		perror("\n accept ");
		else printf("\n accept successful");

		char buf[100];
		int rval = read(nsfd, buf, 100);
		if (rval == -1)
			perror("recv fail");

		string tmp(buf);
		int uskaport = atoi(buf);
		printf("Uska port: %d\n", uskaport);

		int ssfd;
		struct sockaddr_in sid_addr;

		bzero(&sid_addr,sizeof(sid_addr));

		if((ssfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
			perror("\n socket");
		else printf("\n socket created successfully\n");

		sid_addr.sin_family = AF_INET;
		sid_addr.sin_port = htons(6011);
		sid_addr.sin_addr.s_addr = INADDR_ANY;

		if(connect(ssfd , (struct sockaddr *)&sid_addr , sizeof(sid_addr))==-1)
			perror("\nconnect : ");
		else 
			printf("\nconnect succesful");
		int add = htons(cli_addr.sin_port);
		string address = tmp;
		int sret = send(ssfd, address.c_str(), 100, 0);
		if (sret == -1)
			perror("send error");
	}
}