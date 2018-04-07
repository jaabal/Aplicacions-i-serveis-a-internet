#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define BUF_SIZE 2000

void * receiveMessage(void * socket) {
	int sockfd, ret;
	char buffer[BUF_SIZE];
	sockfd = (int) socket;
	memset(buffer, 0, BUF_SIZE);
	for(;;){
		ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
		if (ret < 0){
			printf("Error receiving data!\n");
		}
		else {
			printf("Server: ");
			fputs(buffer, stdout);
		}
	}
}


int main(int argc, char *argv[]) {
	struct sockaddr_in addr, cl_addr;
	int sockfd, portno, ret; 
   	char buffer[BUF_SIZE];  
	char * serverAddr;    
	pthread_t rThread;


	if(argc < 3) { 
        	printf("\n Usage: %s <ip of server> <port>\n",argv[0]);
        	exit(1); 
    }	 

	serverAddr = argv[1];
	portno = atoi(argv[2]);
    
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Error : Could not create socket \n");
		exit(1);
	} 
	printf("Socket created...");

	memset(&addr, 0, sizeof(addr)); 
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(serverAddr);
	addr.sin_port = htons(portno);
    	
	ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));
	if (ret < 0) {
		printf("Error connecting to the server!\n");
		exit(1);
	}
	printf("Connected to the server...\n");
	
	memset(buffer, 0, BUF_SIZE);
	printf("Enter your messages one by one and press return key!\n");
	ret = pthread_create(&rThread, NULL, receiveMessage, (void *) sockfd);
	if (ret) {
		printf("Error. Return code from pthread_create() is %d\n", ret);
		exit(1);
	}
	
	while(fgets(buffer, BUF_SIZE, stdin) != NULL) {
		ret = sendto(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
		if (ret < 0) {
			printf("Error sending data!\n\t-%s",buffer);
		}
	}
		
	close(sockfd);
	pthread_exit(NULL);

	return 0;
}
