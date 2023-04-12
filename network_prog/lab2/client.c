//to develop a client server using socket programming
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <fcntl.h> // open function
#include <unistd.h> // close function

int main(){
//create socket
    int network_socket;
    network_socket=socket(AF_INET,SOCK_STREAM,0);
  //specify address for socket
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;

    int connection_status=connect(network_socket,(struct sockaddr*)&server_address,sizeof(server_address));

    //check error in connection

    if(connection_status==-1){
        printf("\nError in connection wih server");
    }
    //recieve data from the server
    char server_response[256];
    recv(network_socket,&server_response,sizeof(server_response),0);

    //print server response
    printf("\nThe serval sent data: %s\n",server_response);

    //close socket

    close(network_socket);

    return 0;
}
