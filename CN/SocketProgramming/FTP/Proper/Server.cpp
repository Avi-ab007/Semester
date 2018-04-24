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
    if(argc<2){printf("usage <./server> <server_port>\n"); return 0;}
    server_port=atoi(argv[1]);
    cout<<"server port = "<<server_port<<endl;
    

	server_fd=socket(AF_INET,SOCK_STREAM,0);               
	server_addr.sin_family=AF_INET;                        
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  
	server_addr.sin_port = htons(server_port);             
    len=sizeof(server_addr);
	ret =  bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret<0)
    {
        perror("bind failed \n");
        exit(EXIT_FAILURE);
    }
    printf("Server: Binded\n");

    ret = listen(server_fd,MAX_PENDING_REQUESTS);
    if(ret<0){
    	printf("listen failed\n ");
    	exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("Server: Listening \n");
        nsfd = accept(server_fd, (struct sockaddr *)&new_addr, &len);
        printf("Connection accepted from client at %s : %d \n",inet_ntoa(new_addr.sin_addr),ntohs(new_addr.sin_port) );
        recv(nsfd,&client_port,sizeof(client_port),0); 
        cout<<"port received = "<<client_port<<endl;
        filename[0]=0;
        recv(nsfd,filename,BUFFER_LEN,0);
        cout<<"filename received = "<<filename<<endl;
        
        if ( ret < 0)
        {
            perror("Connection Failed in parent process\n");
            exit(EXIT_FAILURE);
        }
        //cout<<"Child Server 2-way connected to client"<<endl;
        int pid=fork();
        if(pid>0)
        {
            close(nsfd); 
        }
        else if(pid==0)
        {
        	client_fd=socket(AF_INET,SOCK_STREAM,0);
        	client_addr.sin_family=AF_INET;
        	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
            client_addr.sin_port=htons(client_port);
            ret = connect(client_fd, (struct sockaddr *)&client_addr, sizeof(client_addr));
            if ( ret < 0)
            {
                 perror("Connection Failed in child process\n");
                 exit(EXIT_FAILURE);
            }
                cout<<"Child Server 2-way connected to client"<<endl;
                close(server_fd); break;
        }
        

    }
    
    
    
    int fd = open(filename,O_RDONLY);
    if(fd<0) {perror("File opening"); return 0;}
    cout<<"File opened successfully "<<endl;
    int i=0; char ch; 
    while(read(fd,&ch,1)>0) 
    {
        cout<<ch;
        buffer[i++]=ch;
    }
    buffer[i]=0;
    printf("buffer = %s \n",buffer );
    send(client_fd,buffer,BUFFER_LEN,0);
	return 0;
}