#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

uint16_t cmmdc(uint16_t a, uint16_t b) {
	if(!b) {
		return a;
	}
	return cmmdc(b, a % b);
}

uint16_t cmmmc(uint16_t a, uint16_t b) {
	return a * b / cmmdc(a, b);
}

int process_request(int s) {
	struct sockaddr_in client;
	int l = sizeof(client);
	uint16_t a, b, cmdc, cmmc;

	recvfrom(s, &a, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l); a = ntohs(a);
	printf("%s\n", inet_ntoa(client.sin_addr));
	recvfrom(s, &b, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr *) &client, (socklen_t *) &l); b = ntohs(b);
	printf("%s\n", inet_ntoa(client.sin_addr));
	printf("%hu %hu\n", a, b);

	cmdc = cmmdc(a, b); cmdc = htons(cmdc);
	cmmc = cmmmc(a, b); cmmc = htons(cmmc);

	sendto(s, &cmdc, sizeof(uint16_t), 0, (struct sockaddr *) &client, (socklen_t) l);
	sendto(s, &cmmc, sizeof(uint16_t), 0, (struct sockaddr *) &client, (socklen_t) l);

	return 0;
}

int main() {
	int s;
	struct sockaddr_in server;

	if((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea server-ului client.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(s, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la bind.\n");
		return 1;
	}

	while(1) {
		if(process_request(s) < 0) {
			printf("Eroare la procesarea request-ului.\n");
		}
	}
	
	return 0;
}
