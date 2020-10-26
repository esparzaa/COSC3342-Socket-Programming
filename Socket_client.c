#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 5000


//ssize_t send(int sockfd, const void *buf, size_t len, int flags);

int main(int argc, char const *argv[]) 
{ 
	int sockfd = 0, valread;
	struct sockaddr_in address
	char *deal = "Deal"; 
    char buffer[1024] = {0}; 
	//int inet_pton(int af, const char *src, void *dst);
	
	
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Socket Creation Error\n");
		return -1;
	}
	
	address.sin_family = AF_INET; 
    address.sin_port = htons(PORT); 
	
	if(inet_pton(AF_INET, "192.168.1.74", &address.sin_addr)<=0)  
    { 
        printf("Invalid address\n"); 
        return -1; 
    } 
	
	if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
	
	send(sockfd, deal, strlen(deal), 0); 
    printf("deal accepted \n"); 
    
	valread = read( sockfd, buffer, 1024); 
    printf("%s\n",buffer );
	
    return 0; 
}
