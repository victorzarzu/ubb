#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <netdb.h>

#define LENGTH 100

int process_request(int c) {
	uint16_t len;
	char* calc = (char *)malloc(sizeof(char) * LENGTH);
	if(!calc) {
		printf("Eroare malloc\n");
		return 1;
	}

	recv(c, &len, sizeof(uint16_t), MSG_WAITALL); len = ntohs(len);
	recv(c, calc, sizeof(char) * len, MSG_WAITALL);

	struct hostent* info = gethostbyname(calc);
	if(!info) {
		calc = "Negasit";
		len = (strlen(calc) + 1) * sizeof(char); len = htons(len);
		send(c, &len, sizeof(uint16_t), 0);
		send(c, calc, len, 0);
	}

	len = info->h_length; len = htons(len);
	send(c, &len, sizeof(uint16_t), 0);
	send(c, info->h_addr, info->h_length, 0);

	free(calc);
	close(c);
	
	return 0;
}

int main() {
	int s, l;
	struct sockaddr_in server, client;

	if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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

	signal(SIGCHLD, SIG_IGN);

	while(1) {
		int c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l);
		printf("S-a conectat un client.\n");
		if(fork() == 0) {
			if(process_request(c)) {
				printf("Eroare la procesare request.\n");
				return 1;
			}
			exit(0);
		}
	}
	
	return 0;
}
