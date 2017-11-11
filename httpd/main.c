#include<pthread.h>
#include"httpd.h"

static void usage(const char *proc)
{
	printf("Usage: %s [local_ip] [local_port]\n",proc);
}

int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1],atoi(argv[2]));
	while(1)
	{
		struct sockaddr_in client;
		socklen_t  len = sizeof(client);
		int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
	
		printf("链接成功了\n");
		if(new_sock < 0)
		{
			print_log(strerror(errno),FATAL);
			continue;
		}
		printf("客户端 \nclient_client_sock  [ip :%s :port %d]\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

		pthread_t id;
		printf("綫裎创建成功了\n");
		int ret = pthread_create(&id,NULL,handler_request,(void *)new_sock);
		if(ret != 0)
		{
			print_log(strerror(errno),WARNING);
			close(new_sock);
		}
		else
		{
			pthread_detach(id);
		}
	}
	close(listen_sock);

	return 0;
}
