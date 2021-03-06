#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <time.h>


int main(int argc, char const *argv[])
{
	struct sockaddr_in address;
	
	int new_sock, sockfd=0, valread, deckofcards[52];

	char buffer[1024] = "You have reached the server";
	
	int addrlen = sizeof(address);
	
	unsigned int port_num;
	
	const char *deal ="Deal";
	
	
	if (isdigit(*argv[1]) == 0)
	{
        printf("Error: Invalid port number\n");
        exit(1);
    }
	
	port_num = atoi(argv[1]);

    if ((atoi(argv[1]) < 1) || (atoi(argv[1]) > 65535))
	{
           printf("Error: Port number must be in range 1 - 65,535\n");
           exit(1);
    }
	
	size_t server_len = sizeof(address);
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(argv[1]));
	
	if (bind(sockfd, (struct sockaddr *)&address, sizeof(address))<0)
	{
		printf("Error: Bind failed\n");
        exit(1);
	}
	
    if (listen(sockfd, 5)<0)
	{		
		printf("Error: Listen failed\n"); 
        exit (1);
	}
	
	if (new_sock = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen)<0)
	{ 
		printf("accept error\n"); 
		exit(1); 
	}
		
	//int comparingString = strcmp(buffer, deal);
	
	valread = read (new_sock, buffer, sizeof(buffer));
		
	new_sock = accept(sockfd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
	
	if (new_sock<0)
	{ 
		printf("accept error\n"); 
		exit(1); 
	}
	
	close(sockfd);
	return 0;
}
	
