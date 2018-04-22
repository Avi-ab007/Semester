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
	socklen_t cli_len;

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(6011);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	int bret = bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	if(bret==-1)
	perror("\n bind : ");
	else printf("\n bind successful ");
	sleep(1);

	listen(sfd,101);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
	perror("\n accept ");
	else printf("\n accept successful");

	char buf[100];
	read(nsfd, buf, 100);
	int port = atoi(buf);
	printf("Recvd port: %d\n", port);

	int ssfd;
	struct sockaddr_in nserv_addr;

	bzero(&nserv_addr,sizeof(nserv_addr));

	if((ssfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	nserv_addr.sin_family = AF_INET;
	nserv_addr.sin_port = htons(port);
	nserv_addr.sin_addr.s_addr = INADDR_ANY;

	if(connect(ssfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("\n connect : ");
	else printf("\nconnect succesful");
	string tmp = "Porn chal gaya\n";
	int sret = send(ssfd, tmp.c_str(), 100, 0);
	if (sret == -1)
		perror("send");
}