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

#define MYPORT "4950"

#define MAXBUFLEN 100

int main()
{
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv, numbytes;
	struct sockaddr_storage their_addr;
	char buf[MAXBUFLEN], buf1[MAXBUFLEN];
	socklen_t addr_len;
	
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;
	
	getaddrinfo(NULL, MYPORT, &hints, &servinfo);
	while(1) {
		for (p = servinfo; p != NULL; p = p->ai_next) {
			sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			continue;
		}
		break;
	}
	addr_len = sizeof their_addr;
	numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1, 0, (struct sockaddr *)&their_addr, &addr_len);
	buf[numbytes] = '\0';
	printf("Client:\t%s\n", buf);
	printf("Server:\t");
	scanf("%s", buf1);
	sendto(sockfd, buf1, MAXBUFLEN, 0, (struct sockaddr*)&their_addr, addr_len);
	close(sockfd);
	}
	return 0;
}
