#include <bits/stdc++.h>
#include <sys/socket.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<semaphore.h>
#include<cstdlib>
#include <arpa/inet.h>		/*  For htonl(PORT) */
#include<unistd.h>
#include<pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>		/* For inet_ntoa() and ntohs()*/
using namespace std;

#define MAX_PENDING_REQUESTS 10
#define BUFFER_LEN 100

struct sockaddr_in server_addr,client_addr,new_addr;
socklen_t len;
int ret,server_fd,client_fd,server_port,client_port,nsfd;
char filename[256],buffer[BUFFER_LEN];

int main(int argc, char const *argv[])
{
	if(argc<3){printf("usage <./server> <server_port> <client_port>\n"); return 0;}
	server_port=atoi(argv[1]); client_port=atoi(argv[2]);
	cout<<"server port = "<<server_port<<endl;
	cout<<"client port = "<<client_port<<endl;


	server_fd=socket(AF_INET,SOCK_STREAM,0);               client_fd=socket(AF_INET,SOCK_STREAM,0);
	server_addr.sin_family=AF_INET;                        client_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(server_port);				client_addr.sin_port=htons(client_port);

	ret =  bind(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr));
    if (ret<0)
    {
        perror("bind failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Client: Binded\n");
	ret = connect(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if ( ret < 0)
    {
        perror("Connection Failed \n");
        return -1;
    }
    cout<<"Client successfully connected to server "<<endl;
    cout<<"Enter the file name "<<endl;
    scanf("%s",filename);
    printf("filename = %s \n",filename );

    send(server_fd,&client_port,sizeof(client_port),0);

    send(server_fd,filename,BUFFER_LEN,0);
    cout<<"Client sent its port = "<<client_port<<" to server "<<endl;
    ret = listen(client_fd,MAX_PENDING_REQUESTS);
    if(ret<0){
    	perror("listen failed\n ");
    	exit(EXIT_FAILURE);
    }
    cout<<"Now client is listening for connect request from server "<<endl;
    nsfd = accept(client_fd, (struct sockaddr *)&new_addr, &len);

    printf("Connection accepted from server at %s : %d \n",inet_ntoa(new_addr.sin_addr),ntohs(new_addr.sin_port) );
    
    cout<<"Client 2-way connected to server "<<endl;
    
    recv(nsfd,buffer,BUFFER_LEN,0);
    printf("File contents are : \n %s \n",buffer );
    cout<<"Client process exiting "<<endl;
	return 0;
}