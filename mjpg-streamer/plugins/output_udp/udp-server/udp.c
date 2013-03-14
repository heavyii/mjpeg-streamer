#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "udp.h"

/**
 * udp_open - make udp socket
 * @return: 0 success, -1 error
 */
int udp_open(struct udp_client *uc, const char *ip, int port)
{
	uc->sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (uc->sock == -1) {
		fprintf(stderr, "%s: create sock err\n", __func__);
		return -1;
	}

	uc->target.sin_family = AF_INET;
	uc->target.sin_port = htons(port);
	uc->target.sin_addr.s_addr = inet_addr(ip);

	return 0;
}


void udp_close (struct udp_client *uc)
{
	close(uc->sock);
	uc->sock=-1;
}

/**
 * udp_send - send data
 * @return: return sendto
 */
int udp_send (struct udp_client *uc, const void *data, int len)
{
	return sendto(uc->sock, data, len, 0, (struct sockaddr*)&uc->target, (socklen_t)sizeof(struct sockaddr_in));
}

/**
 * udp_recv - recvfrom socket
 * @return: return recvfrom
 */
int udp_recv (struct udp_client *uc, void *data, int len)
{
	return recvfrom(uc->sock, data, len, 0, NULL, NULL);
}

