#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>

#define LEN 100

int main() {
	int c;
	struct sockaddr_in server;
	
	c = socket(AF_INET, SOCK_STREAM, 0);
	if(c < 0) {
		printf("Eroare la crearea socket-ului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server\n");
		return 1;
	}

	char *sir = (char *)malloc(sizeof(char) * LEN);
	if(!sir) {
		printf("Eroare malloc\n");
		return 1;
	}

	uint32_t i, l, len;
	printf("sir=");
	scanf("%[^\n]%*c", sir);
	printf("i=");
	scanf("%u", &i);
	printf("l=");
	scanf("%u", &l);

	len = strlen(sir);

	if(i > len) {
		printf("Pozitie prea mare\n");
		return 1;
	}

	len = htonl(len);
	i = htonl(i);
	l = htonl(l);

	send(c, &len, sizeof(len), 0);
	send(c, sir, sizeof(char) * strlen(sir), 0);
	send(c, &i, sizeof(i), 0);
	send(c, &l, sizeof(l), 0);
	l = ntohl(l);

	recv(c, sir, sizeof(char) * l, MSG_WAITALL);
	sir[l] = 0;
	printf("subsir=%s", sir);
	
	return 0;
}
