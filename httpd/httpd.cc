#include"httpd.h"
#include<iconv.h>
#include<stdlib.h>
#include<string.h>
#include<sys/sendfile.h>
#include<ctype.h>
#include<htmlcxx/html/ParserDom.h>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;
using namespace htmlcxx;
 
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
     printf("line : %s\n",line);
     return len;
 }
 
 static void echo_string(int sock)
 {}
 
 int echo_www(int sock,char* path,int size) //GET
 {
     printf("回显\n");
 int fd = open(path,O_RDONLY);
     if(fd < 0)
     {
     //  printf("error\n\n");
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
 
 void drop_header(int sock)
 {
     char line[1024];
     int  ret = -1;
     do
     {
         ret = get_line(sock,line,sizeof(line));
     }while(ret > 0&&strcmp(line,"\n"));
 }
 

int connetser(char *query_str)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
    	printf("sock error\n");
	}
    int opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(80);
    local.sin_addr.s_addr=inet_addr("1.85.11.58");
    int a =  connect(sock,(struct sockaddr*)&local,sizeof(local));
    if(a == 0)
    {
      //  printf("链接建立成功了\n");
      printf("我们已经爬到了网站上面啦！！！\n");
    }


    printf("请输入你要查询的车次：\n");
    char echo_line[420] = "GET /chaxun/bus/busreserch2.asp?keyword=";
    char echo_line2[] = "&submit= HTTP/1.1\r\nHost: www.xianyz.com\r\nUser-Agent: Mozilla/5.0 (X11; Linux i686; rv:52.0 ) Gecko/20100101 Firefox/52.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nCookie: ASPSESSIONIDASSDBCAD=ONPANMLFCHMBOJHPNDBFFBOJK\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";
    strcat(echo_line,query_str);  //传入的参数，是为了这里接到请求报头上面来的
    strcat(echo_line,echo_line2);
    send(sock,echo_line,strlen(echo_line),0);
    printf("正在查询，请稍后\n");
    char buf[5000];
    char arr[5000];
    char *pin = buf;
    char *pout = arr;
    memset(arr,0,5000);
    size_t olen = 5000;
    memset(buf,0,5000);
    int m1 = recv(sock,buf,4999,0);
    char buf2[5000];
    memset(buf2,0,5000);


	char *ifok = buf;
	ifok += 117;
	char ifokarr[5] = {0};
	int ii = 0;
	for(ii;ii<4;ii++)
	{
		ifokarr[ii] = *ifok;
		ifok++;
	}

	ii = atoi(ifokarr);
	cout<<"aaaaaaaaaaa"<<endl<<endl<<endl<<"长度为"<<ii<<endl;
	if(ii > 2500)
	{
	int m2 = recv(sock,buf2,4999,0);
    strcat(buf,buf2);
	}
    size_t len = strlen(buf); 
    iconv_t cd = iconv_open("utf-8","gb2312");
    if(cd == 0)
    {
        printf("error");
        return 0;
    }

    if(iconv(cd,&pin,&len,&pout,&olen) == -1)
    {
        printf("转码错误\n");
    }

    iconv_close(cd);


//这里把recv函数返回的数值大小返回来，因为我们在读取数据的时候，可能存在一个问题就是，打印的时候可能遇到了\0然后就没有打印完全

	if(ii>2500)
	{
    FILE* pf = fopen("txt","a+");
    fwrite(arr,1,strlen(arr),pf);
	HTML::ParserDom parser;
	tree<HTML::Node> dom = parser.parseTree(arr);
    tree<HTML::Node>::iterator it = dom.begin();
    tree<HTML::Node>::iterator end = dom.end();


    //输出所有的文本节点内容
	it+=130;
	//ofstream fout;
	//ofstream fout("tt",ios::binary|ios::noreplace);
	ofstream fout("./wwwroot/haha.html");
    fout<<"<html><head><meta charset=\"utf-8\"><title>haha</title></head><body>"<<it->text()<<"</body></html>";
	fout<<flush;
	fout.close();
	}
	else
	{
		cout<<"访问的页面不存在\n";
		//处理其他的事情

	ofstream fout("./wwwroot/haha.html");
    fout<<"<html><head><meta charset=\"utf-8\"><title>出错</title></head><body><p>对不起，访问的页面不存在</p></body></html>";
	fout<<flush;
	fout.close();
	}
	printf("\n");
    return a;
 }


void *handler_request(void *arg)
{
	unsigned long sock = (unsigned long)arg;
	//int sock = (int)arg;
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
 
     if(get_line(sock,buf,sizeof(buf)) <= 0)
     {
         echo_string(sock);//fail
         ret = 5;
         goto end;
	 }
	 //buf里面放置的内容就是我的url和方法的信息，就是我的整个请求行
     i = 0; //method -> index
     j = 0; //buf->index

	 //printf("成功了\n");
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
	//method里面的内容是方法，这里一般就是GET
	 if(strcasecmp(method,"GET") &&strcasecmp(method,"POST"))
     {
         echo_string(sock);
         ret = 6;
         goto end;
     }
	 if(strcasecmp(method,"post") == 0)
     {
         cgi = 1;
     }
     //buf -> "GET / http/1.0"
     while(isspace(buf[j])&&j<sizeof(buf))
     {
         j++;
     }
	// printf("%s\n",buf);
	// printf("%d",j);
	// printf("aaaaaaaaaaaaaa\n");
	// printf("aaaaaaaaaaaaaa\n");
	// printf("aaaaaaaaaaaaaa\n");
	// printf("aaaaaaaaaaaaaa\n");
	// printf("aaaaaaaaaaaaaa\n");

     i = 0;
     //while(isspace(buf[j])&&j<sizeof(buf)&&i<sizeof(url))
     while(!isspace(buf[j])&&j<sizeof(buf)&&i<sizeof(url))
     {
         url[i] = buf[j];
         i++;
         j++;
     }
     url[i] = 0;
     printf("method : %s url :%s\n",method,url);
     //pan duan shibushi you ? hao   
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
	 printf("path %s\n",path);
     if(path[strlen(path) - 1] == '/')// '/'
     {
         strcat(path,"index.html");
     }
 
	 struct stat st;
     if(stat(path,&st) != 0)
     {
         //falue:404 Not Found
		 printf("文件路径不存在呢\n\n\n\n");
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
		 printf("aaaaaaaaaaa\n");
		 printf("aaaaaaaaaaa\n");
		 printf("aaaaaaaaaaa\n");
		 printf("请求的路径存在\n\n\n\n\n\n\n");
         }
         else if((st.st_mode & S_IXUSR)||(st.st_mode & S_IXGRP)||(st.st_mode & S_IXOTH))
         {
             //cheng xu
			 printf("aaaaaaaaaaaaaa\n");
			 printf("aaaaaaaaaaaaaa\n");
			 printf("aaaaaaaaaaaaaa\n");
			 printf("aaaaaaaaaaaaaa\n");
			 printf("aaaaaaaaaaaaaa\n");
			 printf("aaaaaaaaaaaaaa\n");
			 printf("aaaaaaaaaaaaaa\n");
			 printf("aaaaaaaaaaaaaa\n");
             printf("%s\n",path);
			 cgi = 1;
         }
		 else
         {
			 printf("这里不管是不是正确的路径，都进入到这个函数内部了，是什么原因\n");
			 printf("aaaaaaaa\n");
			 printf("aaaaaaaa\n");
			 printf("aaaaaaaa\n");
			 printf("cgi %d\n\n\n\n",cgi);
			 //当我们输入数据的时候，出错的地方是这个位置，这个位置什么都没有做，然后
			 //然后就直接退出了
		 }
         //ok -> cgi=?,path,query_string,method
        //上面有一个分心path的程序部分，就是处理那个query的那个部分的地方，我哪里把cgi
		//写成是1了，就导致了总是进入到下面的内容 中了，所以我这里先把这个if给注释掉了
		// if(cgi)
        // {
        //   //exe_cgi();
        // }
        // else
        // {
        //     printf("method : %s\n url :%s \n path : %s\n cgi : %d\nquery_string:%s\n    ",method,url,path,cgi,query_string);
        //    drop_header(sock);  //!!!!!!!!      
        //    echo_www(sock,path,st.st_size);  //GET
        // }
		if(cgi)
		{
			//FILE* fp = fopen("./wwwroot/haha.html","r+");
			//if(fp == NULL)
			//{
			//	printf("文件打开失败\n");
			//}
		    query_string+=5;	
			connetser(query_string);
			//fclose(fp);
		}
             printf("method : %s\n url :%s \n path : %s\n cgi : %d\nquery_string:%s\n    ",method,url,path,cgi,query_string);
            drop_header(sock);  //!!!!!!!!      
            echo_www(sock,path,st.st_size);  //GET
     }
 
 
 end:
     printf("quit client ...\n");
     close(sock);
	return (void*)ret;
 #endif
}

