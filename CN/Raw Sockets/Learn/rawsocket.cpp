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

void errexit(string err) {
	perror(err.c_str());
	exit(EXIT_FAILURE);
}

int main() {
	int rsock;
	rsock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (rsock == -1) 
		errexit("socket failed");

	char buff[65536];
	struct sockaddr saddr;
	int addrlen = sizeof saddr;
	if (recvfrom,)
}