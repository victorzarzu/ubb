#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define LENGTH 30

unsigned char* divizori(unsigned char number, unsigned char* len) {
	unsigned char* arr = (unsigned char *)malloc(sizeof(unsigned char) * LENGTH);
	if(!arr) {
		printf("Eroare malloc.\n");
		return NULL;
	}

	*len = 0;
	unsigned char div = 1;
	for(div = 1;div <= number;++div) {
		if(!(number % div)) {
			arr[*len] = div;
			*len = *len + 1;
		}
	}
	return arr;
}

int process_request(int s) {
	struct sockaddr_in client;
	unsigned char number, len;
	int l = sizeof(client);

	recvfrom(s, &number, sizeof(unsigned char), MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l);
	unsigned char* div = divizori(number, &len);
	if(!div) {
		return -1;
	}
	sendto(s, &len, sizeof(unsigned char), 0, (struct sockaddr *) &client, (socklen_t) sizeof(client)); 
	sendto(s, div, sizeof(unsigned char) * len, 0, (struct sockaddr*) &client, (socklen_t) sizeof(client));
	free(div);

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
			printf("Eroare la procesarea request-ului\n");
		}
	}

	return 0;
}
