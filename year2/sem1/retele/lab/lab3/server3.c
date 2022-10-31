#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define LENGTH 100

uint16_t nrSpatii(char *sir) {
	uint16_t result = 0, i;
	for(i = 0;i < (uint16_t) strlen(sir);++i) {
		if(sir[i] == ' ') {
			result++;
		}
	}
	return result;
}

int process_request(int s) {
	uint16_t len;
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	int l = sizeof(client);

	char* sir = (char *)malloc(sizeof(char) * LENGTH);
	if(!sir) {
		printf("Eroare la malloc.\n");
		return 1;
	}


	recvfrom(s, &len, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l); 
	len = ntohs(len);
	recvfrom(s, sir, sizeof(char) * (len + 1), MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l);

	uint16_t spatii = nrSpatii(sir); spatii = htons(spatii);
	sendto(s, &spatii, sizeof(uint16_t), 0, (struct sockaddr *) &client, (socklen_t) l);
	
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
	
	if(bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind.\n");
		return 1;
	}	


	while(1) {
		if(process_request(s) < 0) {
			printf("Eroare la procesarea request-ului.\n");
			return 1;
		}
	}

	close(s);
	
	return 0;
}
