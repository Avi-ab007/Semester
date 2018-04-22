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
#define PORT 8055

int main() {
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	string msg = "Hello from client";
	char buf[1024];
	sock = socket(AF_INET, SOCK_STREAM, 0);
	printf("Socket got = %d \n",sock );
	if (sock < 0) {
		perror("Socket failed");
		exit(1);
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(PORT);
	int cval = connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	sockaddr_in saddr;
	socklen_t slen = sizeof(saddr);
	getpeername(sock, (struct sockaddr*)&saddr, &slen);
	printf("Peername: %s:%d\n", inet_ntoa(saddr.sin_addr), ntohs(slen));
	printf("cval : %d\n", cval);
	if (cval < 0) {
		perror("Connect failed");
		exit(1);
	}
	printf("Connection established with IP %s Port %d \n",inet_ntoa(serv_addr.sin_addr),ntohs(serv_addr.sin_port) );
	printf("Sending message : %s \n",msg.c_str());
	char sbuf[1024];
	{
		scanf("%s", sbuf);
		if (write(sock, sbuf, 1024) == -1)
			perror("write failed");
		char rbuf[1024];
		read(sock, rbuf, 1024);
		printf("buf: %s\n", rbuf);
		//sleep(2);
	}
}