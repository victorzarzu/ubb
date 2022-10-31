#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

int main() {
	int s;
	struct sockaddr_in server, client;
	int c, l;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(7676);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if(bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}

	listen(s, 5);

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while(1) {
		uint32_t numar;

		c = accept(s, (struct sockaddr *) &client, (socklen_t *) &l);
		printf("S-a conectat un client.\n");

		recv(c, &numar, sizeof(numar), MSG_WAITALL);
		numar = ntohl(numar);
		
		uint32_t i;
		for(i = 1;i <= numar;++i) {
			if(!(numar % i)) {
				uint32_t j = htonl(i);
				send(c, &j, sizeof(j), 0);
			}
		}

		i = 0;
		i = htonl(i);
		send(c, &i, sizeof(i), 0);

		close(c);
	}

	return 0;
}
