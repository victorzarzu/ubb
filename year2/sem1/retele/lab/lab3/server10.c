#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int process_request(int s) {
	struct sockaddr_in client;
	int l = sizeof(client);
	memset(&client, 0, sizeof(client));

	uint16_t len;
	recvfrom(s, &len, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l);
	len = ntohs(len);

	char* nume = (char *)malloc(sizeof(char) * (len + 1));
	if(!nume) {
		printf("Eroare la malloc.\n");
		return -1;
	}
	recvfrom(s, nume, sizeof(char) * len, MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l);
	nume[len] = 0;
	
	struct hostent* info = gethostbyname(nume);
	free(nume);

	uint32_t addr = (*(struct in_addr *) info->h_addr).s_addr;
	addr = htonl(addr);
	sendto(s, &addr, sizeof(uint32_t), 0, (struct sockaddr *) &client, (socklen_t) l);
	
	return 0;
}

int main() {
	int s;
	struct sockaddr_in server;

	if((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului server.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(s, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la bind.\n");
		return 1;
	}

	while(1) {
		if(process_request(s) < 0) {
			printf("Eroare la procesarea request-ului.\n");
			return 1;
		}
	}
		
	return 0;
}
