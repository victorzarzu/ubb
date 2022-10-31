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

int main() {
	int c;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului client.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	uint16_t len;
	char* sir = (char *)malloc(sizeof(char) * LENGTH);
	if(!sir) {
		printf("Eroare la malloc.\n");
		return 1;
	}

	printf("sir=");
	scanf("%[^\n]%*c", sir);

	len = strlen(sir); len = htons(len);
	sendto(c, &len, sizeof(len), 0, (struct sockaddr *) &server, sizeof(server));
	sendto(c, sir, sizeof(char) * (strlen(sir) + 1), 0, (struct sockaddr *) &server, sizeof(server));

	uint16_t result;
	int l = sizeof(server);
	recvfrom(c, &result, sizeof(uint16_t), MSG_WAITALL, (struct sockaddr *) &server, (socklen_t* ) &l);
	result = ntohs(result);
	printf("%hu\n", result);
	
	return 0;
}
