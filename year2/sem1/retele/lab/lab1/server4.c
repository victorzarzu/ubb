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

		char *unu = (char *)malloc(sizeof(char) * 200);
		if(!unu) {
			printf("Eroare malloc\n");
			return 1;
		}
		char *doi = (char *)malloc(sizeof(char) * 100);
		if(!doi) {
			printf("Eroare malloc\n");
			return 1;
		}
		char *result = (char *)malloc(sizeof(char) * 200);
		if(!result) {
			printf("Eroare malloc\n");
			return 1;
		}

		uint16_t len_unu, len_doi;
		recv(c, &len_unu, sizeof(len_unu), MSG_WAITALL);
		len_unu = ntohs(len_unu);
		recv(c, unu, sizeof(char) * len_unu, MSG_WAITALL);

		recv(c, &len_doi, sizeof(len_doi), MSG_WAITALL);
		len_doi = ntohs(len_doi);
		recv(c, doi, sizeof(char) * len_doi, MSG_WAITALL);

		unu[len_unu] = 0;
		doi[len_doi] = 0;

		uint16_t pos_unu = 0, pos_doi = 0, pos_result = 0;
		while(pos_unu < len_unu && pos_doi < len_doi) {
			if(unu[pos_unu] < doi[pos_doi]) {
				result[pos_result] = unu[pos_unu];
				++pos_unu;
			}
			else {
				result[pos_result] = doi[pos_doi];
				++pos_doi;
			}
			++pos_result;
		}
		while(pos_unu < len_unu) {
			result[pos_result] = unu[pos_unu];
			++pos_unu;
			++pos_result;
		}
		while(pos_doi < len_doi) {
			result[pos_result] = doi[pos_doi];
			++pos_doi;
			++pos_result;
		}

		send(c, result, sizeof(char) * pos_result, 0);

		free(unu); free(doi);
		close(c);
	}

	close(s);
		
	return 0;
}
