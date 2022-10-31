#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define LENGTH 100

uint16_t * getPos(char* sir, uint16_t length, char ch, uint16_t *len) {
	uint16_t* pos = (uint16_t *)malloc(sizeof(uint16_t) * LENGTH);
	if(!pos) {
		printf("Eroare la malloc\n");
		return NULL;
	}
	*len = 0;

	uint16_t i;
	for(i = 0;i < length;++i) {
		if(sir[i] == ch) {
			pos[*len] = i;
			*len = *len + 1;
		}
	}
	return pos;
}

int process_request(int s) {
	struct sockaddr_in client;
	int l = sizeof(client);
	memset(&client, 0, sizeof(client));
	
	uint16_t len, length;
	recvfrom(s, &len, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr *)&client, (socklen_t *) &l);
	len = ntohs(len);

	char* sir = (char *)malloc(sizeof(char) * len);
	if(!sir) {
		printf("Eroare la malloc\n");
		return -1;
	}
	char ch;

	recvfrom(s, sir, sizeof(char) * len, MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l);
	recvfrom(s, &ch, sizeof(char), MSG_WAITALL, (struct sockaddr *)&client, (socklen_t *) &l);


	uint16_t* pos = getPos(sir, len, ch, &length);
	if(!pos) {
		return -1;
	}

	length = htons(length);
	sendto(s, &length, sizeof(uint16_t), 0, (struct sockaddr *) &client, (socklen_t) l); length = ntohs(length);
	sendto(s, pos, sizeof(uint16_t) * length, 0, (struct sockaddr *) &client, (socklen_t) l);

	free(pos);

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
