#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
 
// debug: strace ./f.out - system calls
// debug: ltrace ./f.out - library

int main() {
	 int c;
	 struct sockaddr_in server;
	 uint16_t n, suma;
	 c = socket(AF_INET, SOCK_STREAM, 0);
	 if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	 }

	 memset(&server, 0, sizeof(server));
 	 server.sin_port = htons(3897);
 	 server.sin_family = AF_INET;
 	 server.sin_addr.s_addr = inet_addr("127.0.0.1");
                                   
   if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
     printf("Eroare la conectarea la server\n");
     return 1;
   }

   printf("n = ");
   scanf("%hu", &n);
	 uint16_t *arr = (uint16_t *)malloc(sizeof(uint16_t) * n);
	 if(!arr) {
     printf("Eroare la creare array\n");
     return 1;
	 }
   int i;
	 for(i = 0;i < n;++i) {
		 printf("arr[%d] = ", i);
		 scanf("%hu", &arr[i]);
	 	 arr[i] = htons(arr[i]);
	 }
	 n = htons(n);

   send(c, &n, sizeof(n), 0);

	 n = ntohs(n);
	 for(i = 0;i < n;++i) {
   	 send(c, &arr[i], sizeof(arr[i]), 0);
	 }

   recv(c, &suma, sizeof(suma), 0);
   suma = ntohs(suma);
   printf("Suma este %hu\n", suma);
   close(c);

   return 0;
} 
