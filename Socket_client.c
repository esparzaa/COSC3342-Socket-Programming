#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define PORT 5000


//ssize_t send(int sockfd, const void *buf, size_t len, int flags);

typedef struct {
	char *value;
	char *type;
}card;

int main(int argc, char const *argv[]) 
{ 
	int sockfd = 0, valread;
	struct sockaddr_in address;
	const char *deal = "Deal"; 
    char buffer[1024] = {0};
	char serv_res[2000], mess[2000], output[1024];
	
	//send(sockfd, deal, strlen(deal), 0); 
	
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Socket Creation Error\n");
		return -1;
	}
	
	address.sin_family = AF_INET; 
    address.sin_port = htons(PORT); 
	
	if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr)<=0)  
    { 
        printf("Invalid address\n"); 
        return -1; 
    } 
	
	if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
	
	printf("Type 'Deal': \n\n"); 
	
	while(1){
		srand(time(NULL));
		int i, r;
	
		char name[4][9] = {{"diamonds"}, {"clubs"}, {"hearts"}, {"spades"}};
		char number [13][6] = {{"ace"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"jack"}, {"queen"}, {"king"}};
	
		card c[52];
		card temp;
	
		for (i = 0; i < 52; i++) {
			c[i].type = name[i%4];
			c[i].value = number[i%13];
		}
	
		for(i = 0; i < 52; i++) {
			r = rand() % 52;
			temp = c[i];
			c[i] = c[r];
			c[r] = temp;
		}
	
		for (i = 0; i < 52; i++) {
		printf("%s %s\n", c[i].type, c[i].value);
		}
    
	valread = read( sockfd, buffer, 1024); 
    printf("%s\n",buffer );
	}
	
    return 0; 
}


    
