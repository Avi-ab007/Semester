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

int recv_fd(int socket) {
  int sent_fd, available_ancillary_element_buffer_space;
  struct msghdr socket_message;
  struct iovec io_vector[1];
  struct cmsghdr *control_message = NULL;
  char message_buffer[1];
  char ancillary_element_buffer[CMSG_SPACE(sizeof(int))];

  /* start clean */
  memset(&socket_message, 0, sizeof(struct msghdr));
  memset(ancillary_element_buffer, 0, CMSG_SPACE(sizeof(int)));

  /* setup a place to fill in message contents */
  io_vector[0].iov_base = message_buffer;
  io_vector[0].iov_len = 1;
  socket_message.msg_iov = io_vector;
  socket_message.msg_iovlen = 1;

  /* provide space for the ancillary data */
  socket_message.msg_control = ancillary_element_buffer;
  socket_message.msg_controllen = CMSG_SPACE(sizeof(int));

  if(recvmsg(socket, &socket_message, MSG_CMSG_CLOEXEC) < 0)
   return -1;

  if(message_buffer[0] != 'F')
  {
   /* this did not originate from the above function */
   return -1;
  }

  if((socket_message.msg_flags & MSG_CTRUNC) == MSG_CTRUNC)
  {
   /* we did not provide enough space for the ancillary element array */
   return -1;
  }

  /* iterate ancillary elements */
   for(control_message = CMSG_FIRSTHDR(&socket_message);
	   control_message != NULL;
	   control_message = CMSG_NXTHDR(&socket_message, control_message))
  {
   if( (control_message->cmsg_level == SOL_SOCKET) &&
	   (control_message->cmsg_type == SCM_RIGHTS) )
   {
	sent_fd = *((int *) CMSG_DATA(control_message));
	return sent_fd;
   }
  }

  return -1;
}

int main(int argc, char *argv[]) {
	string TL(argv[1]);
	stringstream ss;
	string ti, li;
	ss<<TL; ss>>ti; ss>>li;
	printf("Taxi going for %s\n", argv[1]);
	string ADDRESS = "/tmp/";
	ADDRESS += ti;
	ADDRESS += li;

	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
	int userv_len;

	usfd = socket(AF_UNIX , SOCK_STREAM , 0);
	perror("socket");

	bzero(&userv_addr,sizeof(userv_addr));

	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, ADDRESS.c_str());
	unlink(ADDRESS.c_str());
	userv_len = sizeof(userv_addr);

	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("bind");

	listen(usfd, 5);

	socklen_t ucli_len=sizeof(ucli_addr);

	int nusfd;
	nusfd = accept(usfd, (struct sockaddr *)&ucli_addr, &ucli_len);

	int nsfd = recv_fd(nusfd);

	string msg = "Aaja meri ghodi pe chadh jaa!";
	if (send(nsfd, msg.c_str(), 1024, 0) == -1) {
		perror("send failed");
	}
}