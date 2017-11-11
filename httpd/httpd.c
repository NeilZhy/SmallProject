#include"httpd.h"

void print_log(char *msg,int level)
{
#ifdef _STDOUT_
	const char* const level_msg[] = 
	{
		"SUCCESS",
		"NOTICE",
		"WARNING",
		"ERROR",
		"FATAL",
	};

	printf("[%s][%s]\n",msg,level_msg[level%5]);
#else
#endif
}

int startup(const char* ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		print_log(strerror(errno),FATAL);
		exit(2);
	}

	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);
	if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		print_log(strerror(errno),FATAL);
		exit(3);
	}
	if(listen(sock,10)<0)
	{
		print_log(strerror(errno),FATAL);
		exit(4);
	}
	return sock;
}

//ret > 1 ,line != '\0',ret = 1,line = '\n',ret<=0,line=='\0'
static int get_line(int sock,char line[],int size)
{
	//read 1 char ,one by one
	char c = '\0';
	int len = 0;
	while(c != '\n' && len < size -1)
	{
		int r = recv(sock,&c,1,0);
		if(r > 0)
		{
			if(c == '\r')
			{
				int ret = recv(sock,&c,1,MSG_PEEK);
				if(ret > 0)
				{
					if(c == '\n')
					{
						recv(sock,&c,1,0);
					}
					else
					{
						c = '\n';
					}
				}
			}// \r -> \n,\r\n ->\n
			//c == \n
			line[len++] = c;
		}
		else
		{
			c = '\n';
		}

	}
	line[len] = '\0';
//	printf("line : %s\n",line);
	return len;
}

static void echo_string(int sock)
{}

static int echo_www(int sock,char* path,int size) //GET
{
	//wenjian fanhui liulanqi
	int fd = open(path,O_RDONLY);
	if(fd < 0)
	{
	//	printf("error\n\n");
		echo_string(sock);
		print_log(strerror(errno),FATAL);
		return 8;
	}	
	
	const char *echo_line="HTTP/1.0 200 OK\r\n";
	send(sock,echo_line,strlen(echo_line),0);
	const char *null_line="\r\n";
	send(sock,null_line,strlen(null_line),0);


	//success
	if(sendfile(sock,fd,NULL,size)<0)
	{
		//printf("error\n\n");
		echo_string(sock);
		print_log(strerror(errno),FATAL);
		return 9;
	}
	close(fd);
}

static void drop_header(int sock)
{
	printf("进入到了drop_head函数的内部\n");
	char line[1024];
	int  ret = -1;
	do
	{
		ret = get_line(sock,line,sizeof(line));
	}while(ret > 0&&strcmp(line,"\n"));
	printf("drop_header函数结束了\n");
}

static int exe_cgi(int sock,char* method,char* path,char* query_string)
{
	printf("\n这里是exe_cgi函数的内部\n");
	int content_len = -1;
	//cgi = 1
	//GET query_string
	
	//创建环境变量，因为环境变量会被紫禁城集成
	char method_env[SIZE/10];
	char query_string_env[SIZE];
	char content_len_env[SIZE];

	if(strcasecmp(method,"GET") == 0)  //GET
	{
		printf("GET方法\n");
		drop_header(sock);
		printf("drop_head函数结束了\n");
	}
	else //POST
	{
		char line[1024];
		int ret = -1;
		do{
			ret = get_line(sock,line,sizeof(line));
			if(ret > 0	&& strncasecmp(line,"Content-Length: ",16) == 0)

			{
				content_len = atoi(&line[16]);
			}
		}while(ret > 0 && strcmp(line,"\n"));
		if(content_len  == -1)
		{
			echo_string(sock);
			return 10;
		}

	}

	printf("发送包头信息\n");
	const char* echo_line = "HTTP/1.0 200 OK\r\n";
	send(sock,echo_line,strlen(echo_line),0);
	const char* type="Content-Type:text/html;charset=ISO-8859-1\r\n";
	send(sock,type,strlen(type),0);
	const char *null_line="\r\n";
	send(sock,null_line,strlen(null_line),0);

	printf("query_string: %s\n",query_string);
	//path -> exe
	
	int input[2];  //站在了紫禁城的角度，input是紫禁城的输入
	int output[2];  //out是紫禁城的输出
	if(pipe(input) < 0 || pipe(output) < 0)
	{
		echo_string(sock);
		return 11;
	}

	printf("创建紫禁城\n");
	pid_t id = fork();  //创建紫禁城来执行这个新的path和querystring，所以
						//就只有紫禁城去执行程序，然后将结果返回给父进程
	if(id < 0)
	{
		echo_string(sock);
		return 12;
	}
	else if(id == 0)
	{
		printf("紫禁城内部\n");
		close(input[1]);  //保留了读
		close(output[0]);  //保留了写
		//我们想要子进程的标准输入变成input，我们的子进程的标准输出变成是output
		//我们需要通过环境变量来传递这些参数的，考虑我们是不是可以使用管道的方式呢
		printf("关闭读写\n");
		sprintf(method_env,"METHOD=%s",method); //环境变量名和内容
		putenv(method_env);
		if(strcasecmp(method,"GET") == 0)   //这里括号匹配有问题，丫丫呀
		{
			sprintf(query_string_env,"QUERY_STRING=%s",query_string);
			putenv(query_string_env);
		}
		else  //POST
		{
			sprintf(content_len_env,"CONTENT_LENGTH=%d",content_len);
			putenv(content_len_env);
		}
		
		printf("重新定向\n");
		dup2(input[0],0);
		printf("第一个dup2没有问题，第二个dup2有问题\n");
		dup2(output[1],1);
		printf("dup2函数也没有问题????\n");
		printf("执行execl函数\n");
		execl(path,path,NULL);  //应该之这里的execl去执行了那个mathcgi函数
				//execl不会影响dup2的结果，这里程序替换的时候，不会影响文件
				//描述表，所以在紫禁城中的那些冲定性不会有问题的
		printf("execl函数执行完毕\n");
		//execl程序替换的时候，不会影响文件描述符表
		exit(1);
	}
	else  //father
	{
		close(input[0]);
		close(output[1]);
		
		//父进程需要吧数据放出去
		//

		int i = 0;
		char c = '\0';
		if(strcasecmp(method,"POST") == 0)
		{
		//父进程把数据写到管道里面，供给我们的子进程进行数据的读取
			for(;i<content_len;i++)
			{
				recv(sock,&c,1,0);
				write(input[1],&c,1);
			}
		}
		
		//读取子进程返回的数据
		c = '\0';
		while(read(output[0],&c,1) >0)
		{
			send(sock,&c,1,0);
		}
		int ret = waitpid(id,NULL,0);
		close(input[1]);
		close(output[0]);
	}
}

void *handler_request(void *arg)
{
	printf("綫程函数内部\n");
	int sock = (int)arg;
#ifdef _DEBUG_
	char line[1024];
	do{
		int ret = get_line(sock,line,sizeof(line));
		if(ret > 0)
		{
			printf("%s",line);
		}
		else
		{
			printf("request .......done\n");
			break;
		}
	}
	while(1);
#else

	int ret = 0;
	char buf[SIZE];
	char method[SIZE/10];
	char url[SIZE];
	char path[SIZE];
	int i,j;
	int cgi = 0;
	char* query_string = NULL;

	if(get_line(sock,buf,sizeof(buf)) <= 0)  //获取sock中的数据的第一行，进行包头分析，判断方法
						//吧第一行的数据放在了buf中了
	{
		echo_string(sock);//fail
		ret = 5;
		goto end;
	}
	//success
	i = 0; //method -> index
	j = 0; //buf->index
	
	//GET / http/1.1
	while(!isspace(buf[j])\
			&&j < sizeof(buf)\
		   	&&i < sizeof(method) - 1)
	{
		method[i] = buf[j];
		i++;
		j++;
	}
	method[i] = 0;
	printf("方法是：【%s】\n",method);
	if(strcasecmp(method,"GET") &&strcasecmp(method,"POST"))
	{
		printf("推出程序\n");
		echo_string(sock);
		ret = 6;
		goto end;
	}

	if(strcasecmp(method,"post") == 0)
	{
		printf("POST方法\n");
		cgi = 1;
	}
	printf("buf的内容是%s",buf);
	//buf -> "GET / http/1.0"
	printf("%d\n",j);
	while(isspace(buf[j])&&j<sizeof(buf))
	{
		j++;
	}
	printf("%d\n",j);
	i = 0;
	while(!isspace(buf[j])&&j<sizeof(buf)&&i<sizeof(url))
	{
		url[i] = buf[j];
		i++;
		j++;
	}
	printf("打印url的数据，如果没有打印出俩，则说明是url有错误\n");
	url[i] = 0;
	printf("method : %s url :%s\n",method,url);
	//pan duan shibushi you ? hao
	//
	//用query_string标记我们的参数，所以querystring的任务实际上找到那个？
	//因为？后面的位置就是参数的部分
	//同时如果有参数的话，我们会吧我们的cgi标记为1，这就是请求我们的cgi程序	
	query_string = url;
	while(*query_string != '\0')
	{
		if(*query_string == '?')
		{
			*query_string = '\0';
			query_string++;
			cgi = 1;
			break;
		}
		query_string++;
	}



	//pinjie genmulu
	sprintf(path,"wwwroot%s",url);

	//method,url,query_string,cgi
	if(path[strlen(path) - 1] == '/')// '/'
	{
		strcat(path,"index.html");
	}

	struct stat st;
	if(stat(path,&st) != 0)
	{
		//falue:404 Not Found
		echo_string(sock);
		ret  = 7;
		goto end;
	}
	else
	{
		//success
		//mulu
		if(S_ISDIR(st.st_mode))
		{
			strcat(path,"/index.html");
		}
		else if((st.st_mode & S_IXUSR)||(st.st_mode & S_IXGRP)||(st.st_mode & S_IXOTH))
		{
			//cheng xu
			cgi = 1;
		}
		else
		{}
		//ok -> cgi=?,path,query_string,method
		if(cgi)
		{
			printf("enter cgi\n\n");
			printf("进入到了cgi的函数的内容了，接下来应进入到exe_cgi函数的内部\n\n\n\n\n\n\n");
			exe_cgi(sock,method,path,query_string);
		}
		else
		{
			printf("hahahahah\n\n");
			printf("method : %s\n url :%s \n path : %s\n cgi : %d\nquery_string:%s\n",method,url,path,cgi,query_string);
			drop_header(sock);  //!!!!!!!!		
			echo_www(sock,path,st.st_size);  //GET
		}
	}


end:
	printf("quit client ...\n");
	close(sock);
	return (void*)ret;
#endif
}
