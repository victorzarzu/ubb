#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define LENGTH 100 


int main() {
	int c;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului server.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	char* nume = (char *)malloc(sizeof(char) * LENGTH);
	if(!nume) {
		printf("Eroare la malloc.\n");
		return -1;
	}
	scanf("%[^\n]%*c", nume);
	uint16_t len = strlen(nume); len = htons(len);

	sendto(c, &len, sizeof(uint16_t), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));
	sendto(c, nume, sizeof(char) * strlen(nume), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));
		
	free(nume);
	struct in_addr addr;
	recvfrom(c, &addr.s_addr, sizeof(uint32_t), MSG_WAITALL, NULL, NULL);
	addr.s_addr = htonl(addr.s_addr);
	printf("%s\n", inet_ntoa(addr));

	close(c);

	return 0;
}
