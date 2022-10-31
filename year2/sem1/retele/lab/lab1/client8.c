#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define LENGTH 100

uint32_t string_to_integer(char *string) {
	uint32_t result = 0, i;
	for(i = 0;i < (uint32_t) strlen(string);++i) {
		result = result * 10 + string[i] - '0';
	}
	return result;
}

int main(int argc, char **argv) {
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
		printf("Eroare la conectare\n");
		return 1;
	}

	uint32_t len1, len2, i;
	uint32_t *sir1 = (uint32_t *)malloc(sizeof(uint32_t) * LENGTH);
	if(!sir1) {
		printf("Eroare la malloc\n");
		return 1;
	}

	uint32_t *sir2 = (uint32_t *)malloc(sizeof(uint32_t) * LENGTH);
	if(!sir2) {
		printf("Eroare la malloc\n");
		return 1;
	}

	printf("len1=");
	scanf("%u", &len1);
	for(i = 0;i < len1;++i) {
		scanf("%u", &sir1[i]);
		sir1[i] = htonl(sir1[i]);
	}

	printf("len2=");
	scanf("%u", &len2);
	for(i = 0;i < len2;++i) {
		scanf("%u", &sir2[i]);
		sir2[i] = htonl(sir2[i]);
	}

	len1 = htonl(len1);
	send(c, &len1, sizeof(len1), 0); len1 = ntohl(len1);
	send(c, sir1, sizeof(uint32_t) * len1, 0);
	len2 = htonl(len2);
	send(c, &len2, sizeof(len2), 0); len2 = ntohl(len2);
	send(c, sir2, sizeof(uint32_t) * len2, 0);

	uint32_t len;
	uint32_t *sir = (uint32_t *)malloc(sizeof(uint32_t) * LENGTH);
	if(!sir) {
		printf("Eroare la malloc\n");
		return 1;
	}

	recv(c, &len, sizeof(len), MSG_WAITALL);
	len = ntohl(len);
	for(i = 0;i < len;++i) {
		recv(c, &sir[i], sizeof(sir[i]), MSG_WAITALL);
		sir[i] = ntohl(sir[i]);
	}

	for(i = 0;i < len;++i) {
		printf("%u ", sir[i]);
	}
	printf("\n");

	close(c);
	free(sir); free(sir1); free(sir2);
	return 0;
}
