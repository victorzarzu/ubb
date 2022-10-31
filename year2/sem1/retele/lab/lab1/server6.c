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

int adauga(uint32_t* poz, uint32_t *len, uint32_t position) {
	poz[*len] = position;
	*len = *len + 1;
	
	return 0;
}

int process_request(int c) {
	char ch;
	char* sir = (char *)malloc(sizeof(char) * LENGTH);
	if(!sir) {
		printf("Eroare malloc\n");
		return 1;
	}
	uint32_t len;

	recv(c, &len, sizeof(uint32_t), MSG_WAITALL); len = ntohl(len);
	printf("%hu\n", len);
	recv(c, sir, sizeof(char) * len, MSG_WAITALL);
	recv(c, &ch, sizeof(char), MSG_WAITALL);
	sir[len] = 0;

	uint32_t i, result_len = 0;
	uint32_t *result = (uint32_t *)malloc(sizeof(uint32_t) * LENGTH);
	if(!result) {
		printf("Eroare malloc\n");
		return 1;
	}

	for(i = 0;i < len;++i) {
		if(sir[i] == ch) {
			if(adauga(result, &result_len, i)) {
				return 1;
			}
		}
	}

	result_len = htonl(result_len);
	send(c, &result_len, sizeof(uint32_t), 0); result_len = ntohl(result_len);
	for(i = 0;i < result_len;++i) {
		result[i] = htonl(result[i]);
		send(c, &result[i], sizeof(uint32_t), 0);
	}

	free(result);	

	return 0;
}

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l;

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

	l = sizeof(server);
	memset(&client, 0, sizeof(client));

	while(1) {
		c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l);
		printf("S-a conectat un client.\n");

		if(process_request(c)) {
			printf("Eroare la procesare request\n");
		}


		close(c);
	}

	return 0;
}
