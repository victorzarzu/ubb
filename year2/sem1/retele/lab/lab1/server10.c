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

		uint16_t len;
		char sir1[100], sir2[100];
		recv(c, &len, sizeof(len), MSG_WAITALL);
		len = ntohs(len);

		recv(c, sir1, sizeof(char) * len, MSG_WAITALL);
		recv(c, sir2, sizeof(char) * len, MSG_WAITALL);
		sir1[len] = sir2[len] = 0;

		uint16_t freq[129], i, maxim = 0, ch_max = 0;
		memset(freq, 0, sizeof(uint16_t) * 129);

		for(i = 0;i < len;++i) {
			if(sir1[i] == sir2[i]) {
				freq[(uint16_t)sir1[i]]++;
				if(freq[(uint16_t)sir1[i]] > maxim) {
					maxim = freq[(uint16_t)sir1[i]];
					ch_max = sir1[i];
				}
			}
		}

		ch_max = htons(ch_max);
		maxim = htons(maxim);

		send(c, &maxim, sizeof(maxim), 0);
		send(c, &ch_max, sizeof(ch_max), 0);

		close(c);
	}
	
	
	return 0;
}
