#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, char **argv)
{
	int sock_fd = -1;
	struct sockaddr_in sock_addr;
	socklen_t slen = 0;
	char server_ip[16];
	int ret;
	char buff[5] = "hello";
	char recv_buff[50];

	sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	memset(server_ip, 0, sizeof(server_ip));
	strcpy(server_ip, argv[1]);
	sock_addr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &sock_addr.sin_addr);//inet_addr(server_ip);
	sock_addr.sin_port = htons(12340);
	slen = sizeof(sock_addr);
	ret = connect(sock_fd, (struct sockaddr *)&sock_addr, slen);
	if(ret)
	{
		fprintf(stderr, "\n server_ip:%s ret:%d \n", server_ip, ret);
	}
	memset(recv_buff, 0, sizeof(recv_buff));
	while(1)
	{
		//fprintf(stderr, "\nbuff:%s \n", buff);
		write(sock_fd, buff, sizeof(buff));
		sleep(1);
		read(sock_fd, recv_buff, sizeof(recv_buff));
		fprintf(stderr, "recv:%s \n", recv_buff);
	}

	close(sock_fd);
}
