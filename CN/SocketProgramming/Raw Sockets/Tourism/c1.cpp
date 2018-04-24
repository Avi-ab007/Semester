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
#define pack 20

void set_ip_hdr(struct iphdr *ip) {
	ip->version = 4;
	ip->ihl = 5;
	ip->tos = 0;
	ip->frag_off = 0;
	ip->tot_len = htons(100);
	ip->ttl = htons(100);
	ip->id = htons(1234);
	ip->protocol = 6;
	ip->saddr = inet_addr("127.0.0.7");
	ip->daddr = inet_addr("127.0.0.1");
	ip->check = 0;
}

void* getadd(void* args) {
	int rsfd;
	rsfd = socket(AF_INET, SOCK_RAW, 6);
	if (rsfd == -1) 
		perror("socket failed");

	char buff[65536];
	struct sockaddr cliaddr;
	socklen_t addrlen = sizeof cliaddr;
	while(1) {
		if (recvfrom(rsfd, buff,100, 0, (sockaddr*)&cliaddr, &addrlen) == -1)
			perror("recvfrom failed.");
		struct iphdr *ip;
		ip = (struct iphdr*)buff;
		//print_iphdr(ip);
		printf("Data received: %s\n", (buff + (ip->ihl)*4));
	}
}

int main () {
	int sfd;
	struct sockaddr_in serv_addr;
	int port_no = 8055;

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0)) == -1)
		perror("socket");

	int value = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
		perror("setsockopt failed");
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr)) == -1)
		perror("connect");

	string ti, li;
	cin>>ti>>li;
	string buf = ti;
	buf += " ";
	buf += li;

	if (send(sfd, buf.c_str(), 1024, 0) == -1)
		perror("send failed.");
	pthread_t th;
	pthread_create(&th,NULL,getad,NULL);

	while(1) {
		char msg[1024];
		if (recv(sfd, msg, 1024, 0) == -1)
			perror("recv failed");
		cout<<"Message received\n"<<msg<<endl;
		
	}
}