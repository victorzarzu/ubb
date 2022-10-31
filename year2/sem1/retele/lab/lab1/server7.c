#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
	int s, c, l;
	struct sockaddr_in server, client;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(s, (struct sockaddr *) &server, (socklen_t) sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}

	listen(s, 5);

	l = sizeof(client);
	memset(&client, 0, sizeof(client));
	
	while(1) {
		c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l);
		printf("S-a conectat un client.\n");

		char *sir = (char *)malloc(sizeof(char) * 200);
		uint32_t len, i, l;
		recv(c, &len, sizeof(len), MSG_WAITALL);
		len = ntohl(len);
		printf("%u", len);

		recv(c, sir, sizeof(char) * len, MSG_WAITALL);
		recv(c, &i, sizeof(i), MSG_WAITALL);
		recv(c, &l, sizeof(l), MSG_WAITALL);
		i = ntohl(i);
		l = ntohl(l);

		sir[len] = 0;
		strcpy(sir, sir + i);
		strcpy(sir + l, "\0");

		send(c, sir, sizeof(char) * l, 0);

		free(sir);
		close(c);
	}

	close(s);
		
	return 0;
}
