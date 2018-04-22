#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <string.h> //for memset
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_ntoa()
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header

using namespace std;

int main(int argc, char *argv[]) {
	printf("In myls\n");
	struct sockaddr_in sin;
	int fd = atoi(argv[1]);
	int nsfd;
	if ((nsfd = accept(fd, (struct sockaddr*)&sin, (socklen_t*)sizeof(sin))) == -1)
		perror("accept failed.");
	char buf[1024];
	if (recv(nsfd, buf, 1024, 0) == -1)
		perror("recv failed");

	printf("Data received: %s\n", buf);
}