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

int PORTS[] = {5031, 5042, 5053};
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: ./s1 <service no>\n");
		exit(EXIT_FAILURE);
	}

	int port_no = PORTS[atoi(argv[1]) - 1];
	printf("%d\n", port_no);
	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len = sizeof(cli_addr);

	if((sfd = socket(AF_INET,SOCK_STREAM,0))==-1)
		perror("socket failed");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);

	int value = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
		perror("setsockopt failed");
	}

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
		perror("client connection bind failed");

	listen(sfd,10);

	bool flag;
	
	int fsfd;
	struct sockaddr_in fserv_addr,fcli_addr;
	socklen_t fcli_len;
	int fport_no = port_no + 1000;
	printf("Connecting firewall on %d\n", fport_no);

	if((fsfd = socket(AF_INET,SOCK_DGRAM,0)) == -1)
	perror("socket failed");

	bzero(&fserv_addr,sizeof(fserv_addr));

	fserv_addr.sin_family = AF_INET;
	fserv_addr.sin_port = htons(fport_no);
	fserv_addr.sin_addr.s_addr = inet_addr(IP);

	if(bind(fsfd,(struct sockaddr *) &fserv_addr,sizeof(fserv_addr))==-1)
		perror("firewall connection bind failed");

	fcli_len = sizeof(fcli_addr);


	while (true) {
		char buffer[256];
		recvfrom(fsfd , buffer , 256 , 0 , ( struct sockaddr * ) &fcli_addr , & fcli_len );
		string aff(buffer);
		int nsfd;
		if (aff == "Allow") {
			printf("Connection Allowed\n");
			flag = true;
			//Now accepting the connection......

			if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
				perror("accept failed");

			string msg = "Hello from S";
			int num = atoi(argv[1]);
			msg += to_string(num);
			if (send(nsfd, msg.c_str(), 1024, 0) == -1)
				perror("Send failed in s1");
		} else {
			close(nsfd);
			printf("Connection Blocked\n");
			continue;
		}
	}

}