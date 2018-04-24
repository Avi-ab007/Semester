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

int main() {
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no = 5031;

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
	perror("socket ");
	else printf("socket created successfully");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("bind");

	listen(sfd, 10);

	int nsfd;
	socklen_t sz=sizeof(cli_addr);
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &sz))==-1)
	perror("accept ");
	
	char buffer[1024];
	if (recv(nsfd, buffer, 1024, 0) == -1) 
		perror("recv failed");
	printf("Request came in for %s\n", buffer);
	string TL(buffer);
	stringstream ss;
	string ti, li;
	ss<<TL; ss>>ti; ss>>li;

	char *param[] = {"x1",buffer, NULL};
	pid_t cpid;
	cpid = fork();
	if (cpid == 0) {
		execvp("./x1", param);
	}
}