#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

uint16_t prim(uint32_t x) {
	if(x < 2) {
		return 1;
	}
	if(x == 2) {
		return 1;
	}
	if(!(x % 2)) {
		return 0;
	}

	uint32_t d;
	for(d = 3;d <= x / 2;++d) {
		if(!(x % d)) {
			return 0;
		}
	}
	return 1;
}

int main() {
	uint16_t result;
	uint32_t numar;
	int s, l;
	struct sockaddr_in server, client;
	
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

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while(1) {
		recvfrom(s, &numar, sizeof(uint32_t), 0, (struct sockaddr *) &client, (socklen_t *) &l);
		numar = ntohl(numar);
		result = prim(numar); result = htons(result);
		sendto(s, &result, sizeof(uint32_t), 0, (struct sockaddr *) &client, (socklen_t) l);
	}

	close(s);
}
