#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>

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

	if(connect(c, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la conectare\n");
		return 1;
	}

	char sir1[100], sir2[100];
	scanf("%[^\n]%*c", sir1);
	scanf("%[^\n]%*c", sir2);
	uint16_t len = ((strlen(sir1) > strlen(sir2)) ? strlen(sir2) : strlen(sir1));


	len = htons(len);
	send(c, &len, sizeof(len), 0);
	len = ntohs(len);
	send(c, sir1, sizeof(char) * len, 0);
	send(c, sir2, sizeof(char) * len, 0);
	
	uint16_t ch, maxim;
	recv(c, &maxim, sizeof(maxim), MSG_WAITALL);
	recv(c, &ch, sizeof(ch), MSG_WAITALL);

	ch = ntohs(ch);
	maxim = ntohs(maxim);

	printf("%c %hu", ch, maxim);
	
	close(c);

	return 0;
}
