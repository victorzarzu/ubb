#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int c;
	uint32_t numar;
	struct sockaddr_in server;
	
	c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(7676);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server");
		return 1;
	}

	printf("numar = ");
	scanf("%u", &numar);

	if(numar <= 0) {
		printf("Numarul trebuie sa fie strict pozitiv!\n");
		return 1;
	}

	numar = htonl(numar);
	send(c, &numar, sizeof(numar), 0);

	uint32_t div;
	while(1) {
		recv(c, &div, sizeof(div), MSG_WAITALL);
		div = ntohl(div);
		if(div) {
			printf("%u ", div);
		}
		else {
			break;
		}
	}
	printf("\n");

	close(c);

	return 0;
}
