#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int c;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea server-ului client.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	uint16_t a, b, cmmdc, cmmmc;
	scanf("%hu %hu", &a, &b);
	a = htons(a); b = htons(b);

	sendto(c, &a, sizeof(uint16_t), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));
	sendto(c, &b, sizeof(uint16_t), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));

	recvfrom(c, &cmmdc, sizeof(uint16_t), MSG_WAITALL, NULL, NULL); cmmdc = ntohs(cmmdc);
	recvfrom(c, &cmmmc, sizeof(uint16_t), MSG_WAITALL, NULL, NULL); cmmmc = ntohs(cmmmc);

	printf("%hhu %hhu\n", cmmdc, cmmmc);
	
	return 0;
}
