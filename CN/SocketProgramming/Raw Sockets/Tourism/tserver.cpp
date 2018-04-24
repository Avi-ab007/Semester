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
#define PORT 8055

map<string, int> tiai;
void initialize() {
	tiai["t1"] = 5031;
	tiai["t2"] = 5042;
	tiai["t3"] = 5053;
}

int send_fd(int socket, int fd_to_send) {      
	struct msghdr socket_message;
	struct iovec io_vector[1];
	struct cmsghdr *control_message = NULL;
	char message_buffer[1];
	/* storage space needed for an ancillary element with a paylod of length is CMSG_SPACE(sizeof(length)) */
	char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];
	int available_ancillary_element_buffer_space;

	/* at least one vector of one byte must be sent */
	message_buffer[0] = 'F';
	io_vector[0].iov_base = message_buffer;
	io_vector[0].iov_len = 1;

	/* initialize socket message */
	memset(&socket_message, 0, sizeof(struct msghdr));
	socket_message.msg_iov = io_vector;
	socket_message.msg_iovlen = 1;

	/* provide space for the ancillary data */
	available_ancillary_element_buffer_space = CMSG_SPACE(sizeof(int));
	memset(ancillary_element_buffer, 0, available_ancillary_element_buffer_space);
	socket_message.msg_control = ancillary_element_buffer;
	socket_message.msg_controllen = available_ancillary_element_buffer_space;

	/* initialize a single ancillary data element for fd passing */
	control_message = CMSG_FIRSTHDR(&socket_message);
	control_message->cmsg_level = SOL_SOCKET;
	control_message->cmsg_type = SCM_RIGHTS;
	control_message->cmsg_len = CMSG_LEN(sizeof(int));
	*((int *) CMSG_DATA(control_message)) = fd_to_send;

	return sendmsg(socket, &socket_message, 0);
}

void contactAgent(string ti, string li) {

	int sfd;
	struct sockaddr_in serv_addr;
	printf("Contacting %d agent\n", tiai[ti]);
	int port_no = tiai[ti];

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
	perror("ContactAgent socket");

	int value = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
		perror("setsockopt failed");
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("Contact Agent connect");

	string TL = ti;
	TL += " ";
	TL += li;
	if (send(sfd , TL.c_str() , 1024 , 0) == -1) 
		perror("Contact agent Sendto failed");

	printf("Contacted Agent for %s\n", TL.c_str());
}

void sendToXi(string ti, string li, int nsfd) {
	string ADDRESS = "/tmp/";
	ADDRESS += ti;
	ADDRESS += li;
	int usfd;
	struct sockaddr_un userv_addr;
  	int userv_len,ucli_len;

  	usfd = socket(AF_UNIX, SOCK_STREAM, 0);

  	if(usfd==-1)
  		perror("socket");

  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
   	strcpy(userv_addr.sun_path, ADDRESS.c_str());

	userv_len = sizeof(userv_addr);

	if(connect(usfd,(struct sockaddr *)&userv_addr,userv_len)==-1)
		perror("SendtoXi connect");

	send_fd(usfd, nsfd);
}

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


void* ad(void* args) {
	int rsfd = socket(AF_INET,SOCK_RAW,6);
	if (rsfd == -1) 
		perror("socket failed");

	int opt = 1;
	if (setsockopt(rsfd, IPPROTO_IP, IP_HDRINCL, &opt, sizeof opt) == -1)
		perror("setsockopt failed");

	struct sockaddr_in cli_addr;
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	char data[30] = "THIS IS ADVERTISEMENT";
	
	int len = strlen(data);
	char buff[100];

	struct iphdr *ip;
	ip = (struct iphdr*)buff;
	set_ip_hdr(ip);
	strcpy(buff + 20, data);
	cout<<inet_ntoa(*(in_addr*)&ip->daddr)<<endl;
	while(true) {
		if (sendto(rsfd, buff, 100, 0, (struct sockaddr*)&cli_addr, sizeof cli_addr) == -1)
			perror("send to failed");
		sleep(20);
	}
}

int main(int argc, char const *argv[]) {
	
	initialize();	
	int sfd, nsfd, ret;
	struct sockaddr_in server_addr, client_addr;
	pid_t child_pid;

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IP);
	server_addr.sin_port = htons(PORT);

	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd < 0) {
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}
	int value = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
		perror("setsockopt failed");
	}
	ret = bind(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0) {
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}

	ret = listen(sfd, 100);
	if (ret < 0) {
		perror("Listen failed");
		exit(EXIT_FAILURE);
	}
	pthread_t th;
	pthread_create(&th,NULL,ad,NULL);
	while (true) {
		if ((nsfd = accept(sfd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr)) == -1) {
			perror("Accept failed");
			exit(EXIT_FAILURE);
		}
		char buf[1024];
		if (recv(nsfd, buf, 1024, 0) == -1) {
			perror("recv failed");
			exit(EXIT_FAILURE);
		}
		printf("Client sent requested: %s\n", buf);
		string TL(buf);
		stringstream ss;
		string ti, li;
		ss<<TL; ss>>ti; ss>>li;
		contactAgent(ti, li);
		sleep(1);
		sendToXi(ti, li, nsfd);
	}
	return 0;
}