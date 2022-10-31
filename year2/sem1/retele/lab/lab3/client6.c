#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define LENGTH 100

int main() {
	int c;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului server.\n");
		return 1;
	}
	
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	char* sir = (char *)malloc(sizeof(char) * LENGTH);
	if(!sir) {
		printf("Eroare la malloc\n");
		return 1;
	}
	char ch;

	scanf("%[^\n]%*c", sir);
	scanf("%c", &ch);

	uint16_t len = strlen(sir); 
	len = htons(len);

	sendto(c, &len, sizeof(uint16_t), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));
	sendto(c, sir, sizeof(char) * len, 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));
	sendto(c, &ch, sizeof(char), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));

	recvfrom(c, &len, sizeof(uint16_t), MSG_WAITALL, NULL, NULL); len = ntohs(len);

	uint16_t* pos = (uint16_t *)malloc(sizeof(uint16_t) * len);
	if(!pos) {
		printf("Eroare la malloc\n");
		return 1;
	}
	recvfrom(c, pos, sizeof(uint16_t) * len, MSG_WAITALL, NULL, NULL);
	uint16_t i;
	for(i = 0;i < len;++i) {
		printf("%hu ", pos[i]);
	}
	printf("\n");

	return 0;
}
