#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define LENGTH 20


int main() {
	int c;
	unsigned char number, len;
	struct sockaddr_in server;

	if((c = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Eroare la crearea socket-ului server.\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4444);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	printf("numar=");
	scanf("%hhu", &number);
	sendto(c, &number, sizeof(unsigned char), 0, (struct sockaddr *) &server, (socklen_t) sizeof(server));

	recvfrom(c, &len, sizeof(unsigned char), MSG_WAITALL, NULL, NULL);
	unsigned char* arr = (unsigned char *)malloc(sizeof(unsigned char) * len);
	if(!arr) {
		printf("Eroare malloc.\n");
		return 1;
	}
	recvfrom(c, arr, sizeof(unsigned char) * len, MSG_WAITALL, NULL, NULL);
	unsigned char i;
	for(i = 0;i < len;++i) {
		printf("%hhu ", arr[i]);
	}
	printf("\n");
	
	return 0;
}
