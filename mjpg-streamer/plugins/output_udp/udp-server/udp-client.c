
/* Sample UDP client */
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>

#include "udp.h"

int main(int argc, char**argv)
{
	struct udp_client udp;
   char sendline[1000];
   char recvline[1000];
   int n;
   if (argc != 2)
   {
      printf("usage:  %s <IP address>\n", argv[0]);
      exit(1);
   }


   udp_open(&udp, argv[1], 32000);
   while (fgets(sendline, 10000,stdin) != NULL)
   {
      udp_send(&udp, sendline, strlen(sendline));
      n = udp_recv(&udp, recvline, sizeof(recvline));
      recvline[n]=0;
      printf("rec# %s", recvline);
   }

   return 0;
}
