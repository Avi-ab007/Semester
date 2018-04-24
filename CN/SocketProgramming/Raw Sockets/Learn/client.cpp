#include <bits/stdc++.h>
#include <stdio.h>  //For standard things
#include <stdlib.h> //malloc
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>          //memset
#include <netinet/ip_icmp.h> //Provides declarations for icmp header
#include <netinet/udp.h>     //Provides declarations for udp header
#include <netinet/tcp.h>     //Provides declarations for tcp header
#include <netinet/ip.h>      //Provides declarations for ip header
#include <sys/socket.h>
#include <linux/if_ether.h>
#include <arpa/inet.h>

using namespace std;
#define pack 20
int len;

void errexit(string err) {
	perror(err.c_str());
	exit(EXIT_FAILURE);
}

void set_ip_hdr(struct iphdr *ip, int protocol_no) {
	ip->version = 4;
	ip->ihl = 5;
	ip->tos = 0;
	ip->frag_off = 0;
	ip->tot_len = htons(pack + len);
	ip->ttl = htons(100);
	ip->id = htons(1234);
	ip->protocol = protocol_no;
	ip->saddr = inet_addr("127.0.0.7");
	ip->daddr = inet_addr("127.0.0.1");
	ip->check = 0;
}

int main(int argc, char const *argv[]) {
	int rsfd = socket(AF_INET,SOCK_RAW, atoi(argv[1]));
	if (rsfd == -1) 
		errexit("socket failed");

	int opt = 1;
	if (setsockopt(rsfd, IPPROTO_IP, IP_HDRINCL, &opt, sizeof opt) == -1)
		errexit("setsockopt failed");

	struct sockaddr_in cli_addr;
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	char data[30];
	printf("Enter data: ");
	scanf("%s", data);
	len = strlen(data);
	char buff[pack + len + 1];

	struct iphdr *ip;
	ip = (struct iphdr*)buff;
	set_ip_hdr(ip, atoi(argv[1]));
	strcpy(buff + pack, data);
	cout<<inet_ntoa(*(in_addr*)&ip->daddr)<<endl;

	if (sendto(rsfd, buff, pack + len + 1, 0, (struct sockaddr*)&cli_addr, sizeof cli_addr) == -1)
		errexit("send to failed");

	return 0;
}