#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>

#define LENGTH 100

int main() {
	int c;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(c, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}

	char ch;
	char* sir = (char *)malloc(sizeof(char) * LENGTH);
	if(!sir) {
		printf("Eroare malloc\n");
		return 1;
	}
	uint32_t len;

	scanf("%[^\n]%*c", sir);
	scanf("%c", &ch);
	len = strlen(sir);
	len = htonl(len);

	send(c, &len, sizeof(uint32_t), 0);
	send(c, sir, sizeof(char) * strlen(sir), 0);
	send(c, &ch, sizeof(char), 0);

	
	uint32_t i, x;
	recv(c, &len, sizeof(uint32_t), MSG_WAITALL); len = ntohl(len);
	for(i = 0;i < len;++i) {
		recv(c, &x, sizeof(uint32_t), MSG_WAITALL); x = ntohl(x);
		printf("%u ", x);
	}
	printf("\n");

	free(sir);
	close(c);

	return 0;
}
