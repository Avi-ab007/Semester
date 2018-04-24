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
#define len 65536

void errexit(string err) {
	perror(err.c_str());
	exit(EXIT_FAILURE);
}

void print_iphdr(struct iphdr *ip) {
	cout<<"IP header len: "<<(unsigned int)(ip->ihl)<<endl;
	cout<<"IP header version: "<<(unsigned int)(ip->version)<<endl;
	cout<<"IP header ttl: "<<(unsigned int)(ip->ttl)<<endl;
	cout<<"Type of Service: "<<(unsigned int)(ip->tos)<<endl;
	cout<<"Packet ID: "<<ntohs(ip->id)<<endl;
	cout<<"IP Packet len: "<<ntohs(ip->tot_len)<<endl;
	cout<<"Protocol: "<<(unsigned int)(ip->protocol)<<endl;
	cout<<"Check: "<<ip->check<<endl;
	cout<<"Source IP: "<<inet_ntoa(*(in_addr*)&ip->saddr)<<endl;
	cout<<"Destination IP: "<<inet_ntoa(*(in_addr*)&ip->daddr)<<endl;
}

int main(int argc, char *argv[]) {
	int rsfd;
	rsfd = socket(AF_INET, SOCK_RAW, atoi(argv[1]));
	if (rsfd == -1) 
		errexit("socket failed");

	char buff[65536];
	struct sockaddr cliaddr;
	socklen_t addrlen = sizeof cliaddr;
	if (recvfrom(rsfd, buff, len, 0, (sockaddr*)&cliaddr, &addrlen) == -1)
		errexit("recvfrom failed.");
	struct iphdr *ip;
	ip = (struct iphdr*)buff;
	print_iphdr(ip);
	printf("Data received: %s\n", (buff + (ip->ihl)*4));
	return 0;
}