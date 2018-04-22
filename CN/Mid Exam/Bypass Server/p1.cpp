#include <time.h>
#include <stdio.h>
#include <bits/stdc++.h>
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
	struct sockaddr_in serv_addr;

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("\n socket");
	else printf("\n socket created successfully\n");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8055);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
		perror("\n connect : ");
	else printf("\nconnect succesful");

	printf("Sending port\n");
	string x = "8031";
	
	int sret = write(sfd, x.c_str(), 100);
	if (sret == -1)
		perror("Send error");

	printf("Sent port: %s\n", x.c_str());
	int ssfd;
	struct sockaddr_in nserv_addr, ncli_addr;
	socklen_t ncli_len = sizeof(ncli_addr);

	if((ssfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("\n socket ");
	else printf("\n socket created successfully");

	bzero(&nserv_addr,sizeof(nserv_addr));

	nserv_addr.sin_family = AF_INET;
	nserv_addr.sin_port = htons(8031);
	nserv_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(ssfd,(struct sockaddr *) &nserv_addr,sizeof(nserv_addr))==-1)
		perror("\n bind : ");
	else printf("\n bind successful ");
	
	int nnsfd;
	listen(ssfd,100); 
	cout<<"test\n";
	if((nnsfd = accept(ssfd , (struct sockaddr *)&ncli_addr , &ncli_len))==-1)
	perror("\n accept ");
	else printf("\n accept successful");

	char buf[100];
	int rcret = recv(nnsfd, buf, 100, 0);
	if (rcret == -1)
		perror("recv");
	printf("Message from outside: %s\n", buf);
}