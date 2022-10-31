#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int process_request(int s) {
	struct sockaddr_in client;
	char mesaj[100];
	uint16_t len;

	int l = sizeof(client);
	memset(&client, 0, sizeof(client));

	recvfrom(s, &len, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l);
	len = ntohs(len);
	recvfrom(s, mesaj, sizeof(char) * len, MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l);
	if(!strcmp(mesaj, "data")) {
		return -1;
	}

	uint32_t t = time(NULL); 
	t = htonl(t);
	sendto(s, &t, sizeof(uint32_t), 0, (struct sockaddr *) &client, (socklen_t) l);	

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
