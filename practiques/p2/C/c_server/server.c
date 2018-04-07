#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 2000
#define CLADDR_LEN 100

void * receiveMessage(void * socket) {
	int sockfd, ret;
	char buffer[BUF_SIZE];
	sockfd = (int) socket;
	memset(buffer, 0, BUF_SIZE);
	for(;;) {
		ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL);
		if(ret < 0) {
			printf("Error receiving data!\n");
		}
		else {
			printf("client: ");
			fputs(buffer, stdout);
		}
	}
}

void main(int argc, char *argv[]) {
	struct sockaddr_in addr, cl_addr; //
	int sockfd, len, ret, newsockfd, portno;
	char buffer[BUF_SIZE];           //
	pid_t childpid;                  //
	char clientAddr[CLADDR_LEN];
	pthread_t rThread;
    
     	if (argc < 2) {
        	printf("./server [port]\n");
        	exit(1);
     	}

     	sockfd = socket(AF_INET, SOCK_STREAM, 0);
     	if (sockfd < 0) {
        	printf("ERROR opening socket");
     	}

	printf("Socket created!\n");
	
	portno = atoi(argv[1]);

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(portno);
     
 	if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) { 
		printf("ERROR on binding");
		exit(1);
     	}
	printf("Binding done...\n");

	printf("Waiting for a connection...\n");
	listen(sockfd,5);
    	
	len = sizeof(cl_addr);
     	newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len);
	
	if (newsockfd < 0) { 
		printf("Error accepting connection!\n");
	}
	
	inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
	printf("Connection accepted from %s: ",clientAddr);

	// Creating a new thread for receiving messages from the client
	ret = pthread_create(&rThread, NULL, receiveMessage, (void *) newsockfd);
	if(ret < 0) {
		printf("Return code from pthread_create() is %d\n", ret);
		exit(1);
	}
	
	while (fgets(buffer, BUF_SIZE, stdin) != NULL) {
		ret = sendto(newsockfd, buffer, BUF_SIZE, 0, (struct sockaddr *) &cl_addr, len);
		if(ret < 0) {
			printf("Error sending the data");
			exit(1);
		}
	}

	close(newsockfd);
	close(sockfd);

	pthread_exit(NULL);
	return;
}
