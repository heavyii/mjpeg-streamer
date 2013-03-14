
#ifndef UDP_CLIENT_H_
#define UDP_CLIENT_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct udp_client
{
	int sock;
	struct sockaddr_in target;
};

/**
 * udp_open - make udp socket
 * @return: 0 success, -1 error
 */
int udp_open(struct udp_client *uc, const char *ip, int port);

/**
 * udp_send - send data
 * @return: return sendto
 */
int udp_send (struct udp_client *uc, const void *data, int len);

/**
 * udp_recv - recvfrom socket
 * @return: return recvfrom
 */
int udp_recv (struct udp_client *uc, void *data, int len);

#endif
