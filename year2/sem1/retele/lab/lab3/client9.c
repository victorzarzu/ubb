#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

int is_number(char *sir) {
	uint16_t i;
	for(i = 0;i < (uint16_t) strlen(sir);++i) {
		if(sir[i] < '0' || sir[i] > '9') {
			return 0;
		}
	}
	return 1;
}

uint32_t string_to_number(char *sir) {
	uint16_t i;
	uint32_t number;
	for(i = 0;i < (uint16_t) strlen(sir);++i) {
		number = number * 10 + sir[i] - '0';
	}
	return number;
}

int main(int argc, char **argv) {
	if(argc != 3) {
		printf("Numar incorect de argument.\n");
		return 1;
	}
	if(!is_number(argv[2])) {
		printf("Format port invalid.\n");
		return 1;
	}

	int c;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului server.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(string_to_number(argv[2]));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);

	char mesaj[] = "mesaj";
	uint16_t len = strlen(mesaj); len = htons(len);

	sendto(c, &len, sizeof(uint16_t), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));
	sendto(c, &mesaj, sizeof(char) * strlen(mesaj), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));

	uint32_t sec;
	recvfrom(c, &sec, sizeof(uint32_t), MSG_WAITALL, NULL, NULL);
	sec = ntohl(sec);
	time_t t = sec;
	printf("data si ora curenta: %s\n", asctime(localtime(&t)));

	
	return 0;
}
