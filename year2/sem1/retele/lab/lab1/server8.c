#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define LENGTH 100

void delete_element(uint32_t *sir, uint32_t* len, uint32_t pos) {
	uint32_t i;
	for(i = pos;i < *len - 1;++i) {
		sir[i] = sir[i + 1];
	}		
	*len = *len - 1;
}

void insert_element(uint32_t *sir, uint32_t* len, uint32_t element) {
	sir[*len] = element;
	*len = *len + 1;
}

void delete_duplicates(uint32_t *sir, uint32_t* len) {
	uint32_t i, j;

	for(i = 0;i < *len - 1;++i) {
		for(j = i + 1;j < *len;++j) {
			if(sir[i] == sir[j]) {
				delete_element(sir, len, j);
				--j;
			}
		}
	}
}


int process_request(int socket) {
	uint32_t i, j, len1, len2, len = 0;

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

	uint32_t *sir = (uint32_t *)malloc(sizeof(uint32_t) * LENGTH);
	if(!sir) {
		printf("Eroare la malloc\n");
		return 1;
	}

	recv(socket, &len1, sizeof(len1), MSG_WAITALL);
	len1 = ntohl(len1);
	for(i = 0;i < len1;++i) {
		recv(socket, &sir1[i], sizeof(sir1[i]), MSG_WAITALL);
		sir1[i] = ntohl(sir1[i]);
	}

	recv(socket, &len2, sizeof(len2), MSG_WAITALL);
	len2 = ntohl(len2);
	for(i = 0;i < len2;++i) {
		recv(socket, &sir2[i], sizeof(sir2[i]), MSG_WAITALL);
		sir2[i] = ntohl(sir2[i]);
	}

	delete_duplicates(sir1, &len1);
	delete_duplicates(sir2, &len2);

	for(i = 0;i < len1;++i) {
		for(j = 0;j < len2;++j) {
			if(sir1[i] == sir2[j]) {
				insert_element(sir, &len, sir1[i]);
			}
		}
	}
	free(sir1); free(sir2);

	len = htonl(len);
	send(socket, &len, sizeof(len), 0); len = ntohl(len);
	for(i = 0;i < len;++i) {
		sir[i] = htonl(sir[i]);
		send(socket, &sir[i], sizeof(sir[i]), 0);
	}
	free(sir);
	close(socket);

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

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	signal(SIGCHLD, SIG_IGN);

	while(1) {
		c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l);
		printf("S-a conectat un client\n");
		if(fork() == 0) {
			if(process_request(c)) {
				printf("Eroare procesare request\n");
			}
			exit(0);
		}
	}

	return 0;
}
