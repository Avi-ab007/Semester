#include <pcap.h>
#include <stdio.h>
#include <stdlib.h> // for exit()
#include <string.h> //for memset
#include <bits/stdc++.h> //sabka baap 
#include <sys/socket.h>
#include <arpa/inet.h> // for inet_ntoa()
#include <net/ethernet.h>
#include <netinet/ip_icmp.h>   //Provides declarations for icmp header
#include <netinet/udp.h>   //Provides declarations for udp header
#include <netinet/tcp.h>   //Provides declarations for tcp header
#include <netinet/ip.h>    //Provides declarations for ip header

using namespace std;
#define IP "127.0.0.1"
map<pair<int, int>, bool> rules;

void initialize() {
	rules[make_pair(5031, 7041)] = true;
	rules[make_pair(5042, 7052)] = true;
	rules[make_pair(5042, 7063)] = true;
	rules[make_pair(5053, 7063)] = true;
}

bool checkRange(int sport, int dport) {
	return (dport > 5000 and dport < 5100) and (sport > 7000 and sport < 7100);
}

bool checkRule(int sport, int dport) {
	printf("checkRule(%d, %d)\n", sport, dport);
	if ((sport == 7041 and dport == 5031) 
		|| (sport == 7052 and dport == 5042)
		|| (sport == 7063 and dport == 5042)
		|| (sport == 7063 and dport == 5053))
		return true;
	return false;
}

void connectToDest(int dport, int allow) {
	int sfd;
	struct sockaddr_in serv_addr;
	int port_no = dport + 1000;
	printf("Connecting to service: %d\n", port_no);
	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_DGRAM , 0))==-1)
	perror("socket failed");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);
	
	socklen_t serv_len = sizeof(serv_addr);

	string msg;
	if (allow) 
		msg = "Allow";
	else
		msg = "Block";
	sendto(sfd , msg.c_str() , 256 , 0 , ( struct sockaddr * ) &serv_addr ,  serv_len);
	printf("Sent affirmation: %s to server....\n", msg.c_str());
}

void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer) {
	struct sockaddr_in saddr, source, dest;
	struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
	int iphdrlen = 4*iph->ihl;
	struct tcphdr *tcph = (struct tcphdr*)(buffer+sizeof(struct ethhdr)+iphdrlen);
	memset(&source, 0, sizeof(source)); source.sin_addr.s_addr = iph->saddr; source.sin_port = tcph->source; 
	memset(&dest, 0, sizeof(dest)); dest.sin_addr.s_addr = iph->daddr; dest.sin_port = tcph->dest;

	printf("Source %s:%d\n", inet_ntoa(source.sin_addr), ntohs(source.sin_port));
	printf("Destination %s:%d\n", inet_ntoa(dest.sin_addr), ntohs(dest.sin_port));
	int src_port = ntohs(source.sin_port);
	int dest_port = ntohs(dest.sin_port);
	if (checkRange(src_port, dest_port)) {
		printf("Checking rules on %d -> %d\n", src_port, dest_port);
		if (checkRule(src_port, dest_port)) {
			connectToDest(dest_port, 1);
			printf("Connection allowed\n");
		} else {
			connectToDest(dest_port, 0);
			printf("Connection Blocked\n");
		}
	} else {
		connectToDest(dest_port, 0);
		printf("Connection Blocked\n");
	}
}

int main() {
	printf("========>>> Firewall initiating <<<===========\n");
	initialize();
	char errbuf[PCAP_ERRBUF_SIZE];
	char device[] = "lo";
	char protocol[] = "tcp";
	pcap_t *handle;
	struct bpf_program fp;		/*To hold compiled program*/
	bpf_u_int32 pMask, pNet;	/*Subnet Mask and IP Address*/

	int promiscous_mode = 0;
	pcap_lookupnet(device, &pNet, &pMask, errbuf);
	handle = pcap_open_live(device, BUFSIZ, promiscous_mode, -1, errbuf);

	if (pcap_compile(handle, &fp, protocol, 1, pNet) == -1) {
		perror("pcap_compile() failed");
		exit(-1);
	}
	if (pcap_setfilter(handle, &fp) == -1) {
		perror("setfilter failed");
		exit(-1);
	}

	pcap_loop(handle, -1, process_packet, NULL);
	printf("===========>>> Firewall terminating <<<===========\n");
	return 0;
}