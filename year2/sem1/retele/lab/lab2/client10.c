#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

#define LENGTH 100

uint16_t is_port(char *port) {
	uint16_t i;
	for(i = 0;i < (uint16_t)strlen(port);++i) {
		if(port[i] < '0' || port[i] > '9') {
			return 0;
		}
	}
	return 1;
}

uint16_t port_to_int(char *port) {
	uint16_t i, result = 0;
	for(i = 0;i < (uint16_t)strlen(port);++i) {
		result = result * 10 + port[i] - '0';
	}
	return result;
}


int main(int argc, char **argv) {
	if(argc != 3) {
		printf("Numar incorect de argumente.\n");
		return 1;
	}
	if(!is_port(argv[2])) {
		printf("Format incorect al portului.\n");
		return 1;
	}

	int c;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(port_to_int(argv[2]));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(c, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la conectare\n");
		return 1;
	}

	char* calc = (char *)malloc(sizeof(char) * LENGTH);
	if(!calc) {
		printf("Eroare malloc\n");
		return 1;
	}
	printf("Nume calculator=");
	scanf("%[^\n]%*c", calc);


	uint16_t len = strlen(calc); len = htons(len);

	send(c, &len, sizeof(uint16_t), 0);
	send(c, calc, sizeof(char) * (strlen(calc) + 1), 0);

	recv(c, &len, sizeof(uint16_t), MSG_WAITALL); len = ntohs(len);
	recv(c, calc, len, MSG_WAITALL);
	if(!strcmp(calc, "Negasit")) {
		printf("Negasit\n");
		close(c);
		free(calc);
		return 0;
	}
	char* ip = inet_ntoa(*((struct in_addr *) calc));
	printf("%s\n", ip);

	close(c); free(calc);
	
	return 0;
}
