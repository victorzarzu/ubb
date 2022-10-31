#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int string_to_integer(char* string) {
	int result = 0, i;
	for(i = 0;i < strlen(string);++i) {
		result = result * 10 + string[i] - '0';
	}

	return result;
}

int main(int argc, char** argv) {
	if(argc != 3) {
		printf("Numar incorect de argumente\n");
		return 1;
	}

	int c;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(string_to_integer(argv[2]));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(c, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la connect\n");
		return 1;
	}

	uint16_t a, b, cmmdc, cmmmc;
	printf("a=");
	scanf("%hu", &a);
	printf("b=");
	scanf("%hu", &b);

	a = htons(a); b = htons(b);
	send(c, &a, sizeof(uint16_t), 0);
	send(c, &b, sizeof(uint16_t), 0);

	recv(c, &cmmdc, sizeof(uint16_t), MSG_WAITALL); cmmdc = ntohs(cmmdc);
	recv(c, &cmmmc, sizeof(uint16_t), MSG_WAITALL); cmmmc = ntohs(cmmmc);

	printf("cmmdc=%d cmmmdc=%d\n", cmmdc, cmmmc);

	
	return 0;
}
