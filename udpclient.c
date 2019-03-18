#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>

#define SERVERPORT "4950"

#define MAXBUFLEN 100

int main()
{
	struct addrinfo hints, *servinfo, *p;
	int sockfd, numbytes;
	char buf[MAXBUFLEN], buf1[MAXBUFLEN];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	getaddrinfo("127.0.0.1", SERVERPORT, &hints, &servinfo);
	while(1){
		for (p = servinfo; p != NULL; p = p->ai_next) {
			if ((sockfd= socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
				continue;
			
			break;
		}
	
		printf("Client:\t");
		scanf("%s", buf);
		 if((strncmp(buf,"exit",4))==0)
                {
                     printf("Client Exit...\n");
                     break;
                }

		sendto(sockfd, buf, strlen(buf), 0, p->ai_addr, p->ai_addrlen);
		recvfrom(sockfd, buf1, MAXBUFLEN, 0, p->ai_addr, &(p->ai_addrlen));
		printf("Server:\t%s\n", buf1);
		if((strncmp(buf1,"exit",4))==0)
                {
                     printf("Client Exit...\n");
                     break;
                }

		close(sockfd);
	}
	return 0;
}
