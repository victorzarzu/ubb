#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	uint16_t result;
	uint32_t numar;
	int s;
	struct sockaddr_in server;

	if((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului client.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("Numar=");
	scanf("%u", &numar);
	numar = htonl(numar);

	if(sendto(s, &numar, sizeof(uint32_t), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la trimiterea numarului.\n");
		return 1;
	}

	recvfrom(s, &result, sizeof(uint16_t), MSG_WAITALL, NULL, NULL); result = ntohs(result);
	if(result) {
		printf("Numarul este prim.\n");
	} else {
		printf("Numarul nu este prim.\n");
	}

	close(s);
	return 0;
}
