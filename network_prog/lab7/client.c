#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

int main(){
    int client_socket;
    struct sockaddr_in server_address;

    int send_timeout = 7000;
    int recv_timeout = 12000;

    //socket creation
    client_socket = socket(AF_INET, SOCK_STREAM,0);
    if(client_socket == -1){
        perror("Socket could not be created\n");
        exit(EXIT_FAILURE);
    }
    // setting timeout value for sending and recieving data
    struct timeval tvalue;
    tvalue.tv_sec = send_timeout;
    tvalue.tv_usec = (send_timeout % 1000)*1000;
    
    if(setsockopt(client_socket,SOL_SOCKET,SO_SNDTIMEO,&tvalue,sizeof(tvalue))==-1){
        perror("setsocketopt() for SO_SNDTIMEO failed!!");
        exit(EXIT_FAILURE);
    }
    tvalue.tv_sec = recv_timeout/1000;
    tvalue.tv_usec = (recv_timeout%1000)*1000;

    if(setsockopt(client_socket,SOL_SOCKET,SO_RCVTIMEO,&tvalue,sizeof(tvalue))==-1){
        perror("Setsocketopt() for SO_RECVTIMEO failed");
        exit(EXIT_FAILURE);
    }

    //fill details of server
    memset(&server_address,0,sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(64000);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(client_socket, (struct sockaddr*)&server_address,sizeof(server_address))==-1){
        perror("Could not be connected");
        exit(EXIT_FAILURE);
    }

    //sending and receiving data
    char buff[256];
    read(client_socket, buff, sizeof(buff));
    printf("\nMessage recived from server : %s\n",buff);
    char *msg;
    msg = (char*)malloc(sizeof(char)*50);
    printf("\nEnter the message for server : ");
    fgets(msg,50,stdin);
    write(client_socket,msg,strlen(msg));

    //socket closing
    close(client_socket);
    return 0;
} 
