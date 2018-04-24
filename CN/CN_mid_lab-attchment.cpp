HEADER FILES
--------------------------------------------------------------------------------------------------------------------------------

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

/**
 This function is used to send file descriptor over Unix domain socket
 You can use this function with file descriptor return
 by any one of below functions
 1 .  socketpair();
 2 .  socket(AF_UNIX,...);
 3 .  socket(AF_LOCAL,...);
 @param socket file_descriptor_of_sender
 @param fd_to_send
*/

SELECT
---------------------------------------------------------------------------------------------------------------------
	fd_set readfds;
	struct timeval timeout;
	while (true) {
		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);

		timeout.tv_sec = 3;
		timeout.tv_usec = 0;

		sret = select(1, &readfds, NULL, NULL, &timeout);
		if (FD_ISSET(mainfd, &readfds))
 

				SHARE MEMORY
-----------------------------------------------------------------------------------------------------------------------------------

	int state=1;
	key_t h=ftok(".",state++);	// value of state should on every program where this share memory is used
 	int shmid=shmget(h,sizeof(int),IPC_CREAT|0666);
 	share_memory=shmat(shmid,(const void*)0,0);
 	
 	
 				SEMAPHORE
-----------------------------------------------------------------------------------------------------------------------------------
 	
	void sem_wait(int semid)
	{
		struct sembuf sb;
		sb.sem_num=0;
		sb.sem_op=-1;
		sb.sem_flg=0;
		if((semop(semid,&sb,1))==-1)
		{
			perror("\nFailed to acquire semaphore.");
			exit(0);
		}
	}

	void sem_try_wait(int semid)
	{
		struct sembuf sb;
		sb.sem_num=0;
		sb.sem_op=-1;
		sb.sem_flg=IPC_NOWAIT;;
		return semop(semid,&sb,1);
	}

	void sem_signal(int semid)
	{
		struct sembuf sb;
		sb.sem_num=0;
		sb.sem_op=1;
		sb.sem_flg=0;
		if((semop(semid,&sb,1))==-1)
		{
			perror("\nFailed to release semaphore.");
			exit(0);
		}
	}

	int state=1;
	key_t h=ftok(".",state++);	// value of state should on every program where this semaphore is used
	int sem_id;
	if((sem_id=semget(h,1,0666|IPC_CREAT))==-1)
 	{
		printf("error in creation semaphore\n");
		exit(0);
	}
	
	int semaphore_value=1;

	if((semctl(sem_id,0,SETVAL,semaphore_value))==-1)
	{
		printf("error to set value\n");
	}

 				SELECT
----------------------------------------------------------------------------------------------------------------------------------
	fd_set readset;
	FD_ZERO(&readset);
	
	int max=-1;
	
	for(i=0;i<no_of_file_descriptors;i++)
	{
		FD_SET(fd[i], &readset);
		if(fd[i]>max)
		max=fd[i];		
	}
	
	
	struct timeval t;
	t.tv_sec=3;
	t.tv_usec=100;
	int rv = select(max + 1, &readset, NULL, NULL, &t);

	if (rv == -1) 
	{
		perror("select");
	}
	
	else if (rv == 0) 
	{
    		printf("Timeout occurred!\n");
	} 
	
	else 
	{
		int i;
		// check for events 
		for(i=0;i<no_of_file_descriptors;i++)
    		if (FD_ISSET(fd[i], &readset)) 
		{

    		}
	}
 	
				pthread
----------------------------------------------------------------------------------------------------------------------------------
 	
 	void do_thread_service(void *arg)
	{
		int *args= (int*)arg ;
 	
	}
	
	pthread_t t_service;
 	if(pthread_create(&t_service,NULL,(void*)&do_thread_service ,(void*)args)!=0)
	perror("\npthread_create ");
 	



		           CONNECTION ORIENTED SERVER	( usage -:  "./a.out port_no")
---------------------------------------------------------------------------------------------------------------------------------
	if(argc!=2)
	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len = sizeof(cli_addr);
	int port_no = atoi(argv[1]);

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
		perror("bind failed");

	listen(sfd,10);

	int nsfd;
	if((nsfd = accept(sfd , (struct sockaddr *)&cli_addr , &cli_len))==-1)
		perror("accept failed");


		          CONNECTION ORIENTED CLIENT	( usage -:  "./a.out port_no")
---------------------------------------------------------------------------------------------------------------------------------

	if(argc!=2)
	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_STREAM , 0))==-1)
		perror("socket failed");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);

	int value = 1;
	if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR|SO_REUSEPORT, &value, sizeof value) == -1) {
		perror("setsockopt failed");
	}

	if(connect(sfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr))==-1)
	perror("connect failed");



			           CONNECTION LESS SERVER	( usage -:  "./a.out port_no")
---------------------------------------------------------------------------------------------------------------------------------
	if(argc!=2)
	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr,cli_addr;
	socklen_t cli_len;
	int port_no=atoi(argv[1]);

	if((sfd = socket(AF_INET,SOCK_DGRAM,0)) == -1)
	perror("socket failed");

	bzero(&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);

	if(bind(sfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))==-1)
	perror("bind failed");

	cli_len = sizeof(cli_addr);

	fgets( buffer , 256 , stdin );
	sendto(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &cli_addr ,  cli_len);
	recvfrom(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &cli_addr , & cli_len );

		          CONNECTION LESS CLIENT	( usage -:  "./a.out port_no")
---------------------------------------------------------------------------------------------------------------------------------

	if(argc!=2)
	printf("\n usage ./a.out port_no");

	int sfd;
	struct sockaddr_in serv_addr;
	int port_no=atoi(argv[1]);
	char buffer[256];

	bzero(&serv_addr,sizeof(serv_addr));

	if((sfd = socket(AF_INET , SOCK_DGRAM , 0))==-1)
	perror("socket failed");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = inet_addr(IP);
	
	socklen_t serv_len = sizeof(serv_addr);
	
	fgets( buffer , 256 , stdin );
	sendto(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &serv_addr ,  serv_len);
	recvfrom(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &serv_addr , & serv_len );

		           UNIX SOCKET CONNECTION ORIENTED SERVER	( usage -:  "./a.out")
---------------------------------------------------------------------------------------------------------------------------------
	#define ADDRESS  "mysocket"

	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	int userv_len,ucli_len;

	usfd = socket(AF_UNIX , SOCK_STREAM , 0);
	perror("socket failed");

  	bzero(&userv_addr,sizeof(userv_addr));

  	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, ADDRESS);
	unlink(ADDRESS);
	userv_len = sizeof(userv_addr);

	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("bind failed");

	listen(usfd, 5);

	ucli_len=sizeof(ucli_addr);

	int nusfd;
	nusfd=accept(usfd, (struct sockaddr *)&ucli_addr, &ucli_len);


		          UNIX SOCKET CONNECTION ORIENTED CLIENT	( usage -:  "./a.out")
---------------------------------------------------------------------------------------------------------------------------------

	#define ADDRESS     "mysocket"

	int usfd;
	struct sockaddr_un userv_addr;
  	int userv_len,ucli_len;

  	usfd = socket(AF_UNIX, SOCK_STREAM, 0);

  	if(usfd==-1)
  	perror("\nsocket  ");

  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
   	strcpy(userv_addr.sun_path, ADDRESS);

	userv_len = sizeof(userv_addr);

	if(connect(usfd,(struct sockaddr *)&userv_addr,userv_len)==-1)
	perror("\n connect ");

	else printf("\nconnect succesful");



















				SEND_FD AND RECV_FD
---------------------------------------------------------------------------------------------------------------------

int send_fd(int socket, int fd_to_send)
 {      
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
 
 
 
 
 
 int recv_fd(int socket)
 {
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




		           UNIX SOCKET CONNECTION LESS SERVER	( usage -:  "./a.out")
---------------------------------------------------------------------------------------------------------------------------------
	#define ADDRESS  "mysocket"

	int  usfd;
	struct sockaddr_un userv_addr,ucli_addr;
  	int userv_len,ucli_len;

	usfd = socket(AF_UNIX , SOCK_DGRAM , 0);
	perror("socket");

  	bzero(&userv_addr,sizeof(userv_addr));

  	userv_addr.sun_family = AF_UNIX;
	strcpy(userv_addr.sun_path, ADDRESS);
	unlink(ADDRESS);
	userv_len = sizeof(userv_addr);

	if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
	perror("server: bind");

	fgets( buffer , 256 , stdin );
	sendto(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &ucli_addr ,  ucli_len);
	recvfrom(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &ucli_addr , & uscli_len );


		          UNIX SOCKET CONNECTION LESS CLIENT	( usage -:  "./a.out")
---------------------------------------------------------------------------------------------------------------------------------

	#define ADDRESS     "mysocket"

	int usfd;
	struct sockaddr_un userv_addr;
  	int userv_len,ucli_len;

  	usfd = socket(AF_UNIX, SOCK_DGRAM, 0);

  	if(usfd==-1)
  	perror("\nsocket  ");

  	bzero(&userv_addr,sizeof(userv_addr));
  	userv_addr.sun_family = AF_UNIX;
   	strcpy(userv_addr.sun_path, ADDRESS);

	userv_len = sizeof(userv_addr);
	
	fgets( buffer , 256 , stdin );
	sendto(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &userv_addr ,  userv_len);
	recvfrom(sfd , buffer , 256 , 0 , ( struct sockaddr * ) &userv_addr , & userv_len );


		         SOCKET PAIR	( usage -:  "./a.out")
---------------------------------------------------------------------------------------------------------------------------------

	int usfd[2];
	if(socketpair(AF_UNIX,SOCK_STREAM,0,usfd)==-1)
	perror("socketpair ");
			
	int c=fork();
			
	if(c==-1)
	perror("\nfork ");
			
	else if(c>0)
	{
		close(usfd[1]);
	}
			
	else if(c==0)
	{
		close(usfd[0]);	
		dup2(usfd[1],0);
		execvp(file_name,args);
	}



						RAW SOCKET SERVER
-----------------------------------------------------------------------------------------------------------------------------------
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

						RAW SOCKET CLIENT
---------------------------------------------------------------------------------------------------------------------------------------
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