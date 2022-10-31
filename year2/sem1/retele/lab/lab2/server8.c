#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint16_t cmmdc(uint16_t a, uint16_t b) {
	if(!b) {
		return a;
	}
	return cmmdc(b, a % b);
}

uint16_t cmmmc(uint16_t a, uint16_t b) {
	return a * b / cmmdc(a, b);
}

int process_request(int c) {
	uint16_t a, b;
	recv(c, &a, sizeof(uint16_t), MSG_WAITALL);
	recv(c, &b, sizeof(uint16_t), MSG_WAITALL);

	uint16_t result1 = cmmdc(a, b);
	uint16_t result2 = cmmmc(a, b);

	send(c, &result1, sizeof(uint16_t), 0);
	send(c, &result2, sizeof(uint16_t), 0);
		
	return 0;
}

int main() {
	int s, c, l;
	struct sockaddr_in server, client;

	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(s, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}

	listen(s, 5);

	l = sizeof(server);
	memset(&client, 0, sizeof(client));

	while(1) {
		int c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l);
		printf("S-a conenctat un client\n");

		if(fork() == 0) {
			if(process_request(c)) {
				printf("Eroare la response");
			}
		}

		close(c);
	}


	
	return 0;
}
