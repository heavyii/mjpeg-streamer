/* Sample UDP server */
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <dirent.h>
int main(int argc, char**argv) {
	int sockfd, n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char frame[1024*1024];
	int frame_size;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(32000);
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	char buffer2[128];
	int cnt = 0;
	for (;;) {
		int fd;
		len = sizeof(cliaddr);
		frame_size = recvfrom(sockfd, frame, sizeof(frame), 0,
				(struct sockaddr *) &cliaddr, &len);
		if (frame_size < 0)
			continue;


		snprintf(buffer2, sizeof(buffer2), "udp-%d.jpg", cnt++);

		printf("#cnt=%d\n", cnt);
		continue;

		/* open file for write */
		if ((fd =
				open(buffer2, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
			printf("could not open the file %s\n", buffer2);
			continue;
		}

		/* save picture to file */
		if (write(fd, frame, frame_size) < 0) {
			printf("could not write to file %s\n", buffer2);
			perror("write()");
			close(fd);
			continue;
		}

		close(fd);
	}
}
