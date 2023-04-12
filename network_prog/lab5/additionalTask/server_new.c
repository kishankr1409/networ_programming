//to study the read and write function in socket programming in c language 
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>


int main(int argc, char *argv[]){
	//define server socket

	int server_socket;
	server_socket=socket(AF_INET,SOCK_STREAM,0);
	
	//define the server address
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=INADDR_ANY;
	server_address.sin_port=htons(64000);

	//bind socket
	bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address));

	listen(server_socket, 5);
	printf("\nServer started listening....\n");
    
    while(1){
		int client_socket;
		client_socket=accept(server_socket,NULL,NULL);
		char *msg="Welcome, this is server Kishan";
		write(client_socket,msg,strlen(msg));
		printf("\nMessage sent...");

		char buff[256];
                		printf("\nMessage recieved from client : %s\n",buff);
		char *p=strstr(buff,"END");
        
		if(p!=NULL){
			printf("\nServer is going to off...\n");
			break;
		}
		read(client_socket,buff,sizeof(buff));
        switch (buff[0])
        {
		case '1': strcpy(buff,"ONE");
		    break;
		case '2': strcpy(buff,"TWO");
		    break;
		case '3': strcpy(buff,"THREE");
		    break;
		case '4': strcpy(buff,"FOUR");
		    break;
		case '5': strcpy(buff,"FIVE");
		    break;
		default:strcpy(buff,"INVALID INPUT");
		}
	}
	
	close(server_socket);
}	
	

