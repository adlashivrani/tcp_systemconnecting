#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h> //iner_addr
#define SIZE 100
#define _PORT_ 55555

int main()
{
    char buff[SIZE]; //creating buffer
	char BUF[SIZE];
   	int cfd; //file descriptor for client
	char str[SIZE] = "10.91.243.85";
    struct sockaddr_in client;//calling structure for client   
    client.sin_family = AF_INET;
    client.sin_port = htons(_PORT_);
    //client.sin_addr.s_addr = INADDR_ANY;
    client.sin_zero[8] = '\0';
	
    //creating server socket file descriptor
    if ((cfd = socket(AF_INET, SOCK_STREAM,0)) == -1) {
		printf("\nCLIENT SOCKET FD NOT CREATED\n");
    	exit(1);//socket not created
    }
	if ((inet_pton(AF_INET, str, &client.sin_addr.s_addr)) == -1 ) {
		printf("\nNot Able to Connect to the ip address given\n");
		exit(1);
	}
  	
	if ((connect(cfd, (struct sockaddr*)&client, sizeof(client))) == -1) {
		printf("\nNOT CONNECTED TO THE SERVER!\n");
		exit(1);
	}
	write(cfd,"Hello! It's Rani!",SIZE);
	printf("\nWrite a message to server\n");
	while(1) {
	bzero(BUF, SIZE);
	bzero(buff, SIZE);
	fgets(BUF, SIZE, stdin);
	write(cfd,BUF, SIZE); // writing to the server file descriptor
    read(cfd, buff, SIZE); //reading from the client file descriptor
    printf("%s\n", buff);
	}
    close(cfd);
   	
    return 0;
}
 
