//to develop a client server using socket programming
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <fcntl.h> // open function
#include <unistd.h> // close function

int main(){
  char server_message[256]="kishan server is working\n";
  
  int server_socket;
  server_socket=socket(AF_INET,SOCK_STREAM,0);
  struct sockaddr_in server_address;
  server_address.sin_family=AF_INET;
  server_address.sin_port=htons(9002);
  server_address.sin_addr.s_addr=INADDR_ANY;

  bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));
  listen(server_socket,3);
  int client_scoket;
  client_scoket=accept(server_socket,NULL,NULL);
  send(client_scoket,server_message,sizeof(server_message),0);

  //close socket
  close(server_socket);
  return 0;                                 
}

