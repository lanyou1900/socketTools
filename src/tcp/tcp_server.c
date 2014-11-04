#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_LEN                     (100)

int main(int argc, char **argv)
{
	int listen_fd;
	int connet_fd;
	int recv_len = 0;
	int cliet_addr_len = 0;
	struct sockaddr_in server_addr; 
	struct sockaddr_in cliet_addr;
	char send_buff[] = "server";
	char buff[MAX_LEN];
	int ret;

	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12340);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	ret |= listen(listen_fd, 100);
	if(0 != ret)
	{
		printf("\n ret:%d \n" ,ret);
	}

	connet_fd = accept(listen_fd, (struct sockaddr *)&cliet_addr, &cliet_addr_len);
	memset(buff, 0, sizeof(buff));
	while(1)
	{
		write(connet_fd, send_buff, sizeof(send_buff));
		recv_len = read(connet_fd, buff, MAX_LEN);
		printf("\n recv:%s, recv_len:%d \n", buff, recv_len);
		sleep(1);
	}
}
