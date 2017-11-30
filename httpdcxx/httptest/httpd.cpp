#include"httpd.h"
#include <iconv.h>
#include<stdlib.h>
#include<string.h>
#include<sys/sendfile.h>
#include<ctype.h> 
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

int connetser()
{
	printf("helllo\n");
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


   // const char* echo_line = "GET /chaxun/bus/busreserch2.asp?keyword=336&submit= HTTP/1.1\r\nHost: www.xianyz.com\r\nConnection: keep-alive\r\nCache-Control: max-age=0\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nAccept-Encoding: gzip, deflate, sdch\r\nAccept-Language: zh-CN,zh;q=0.8\r\nCookie: ASPSESSIONIDCQSAADAD=BEGIDJODNHHHDIAEMMEHCHFI\r\n\r\n";
    //const char* echo_line = "GET /chaxun/bus/busreserch2.asp?keyword=336&submit= HTTP/1.1\r\nHost: www.xianyz.com\r\nUser-Agent: Mozilla/5.0 (X11; Linux i686; rv:52.0 ) Gecko/20100101 Firefox/52.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nCookie: ASPSESSIONIDASSDBCAD=ONPANMLFCHMBOJHPNDBFFBOJK\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";
    printf("请输入你要查询的车次：\n");
    char busarr[5];
    scanf("%s",busarr);
    char echo_line[420] = "GET /chaxun/bus/busreserch2.asp?keyword=";
    char echo_line2[] = "&submit= HTTP/1.1\r\nHost: www.xianyz.com\r\nUser-Agent: Mozilla/5.0 (X11; Linux i686; rv:52.0 ) Gecko/20100101 Firefox/52.0\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\nAccept-Language: en-US,en;q=0.5\r\nAccept-Encoding: gzip, deflate\r\nCookie: ASPSESSIONIDASSDBCAD=ONPANMLFCHMBOJHPNDBFFBOJK\r\nConnection: keep-alive\r\nUpgrade-Insecure-Requests: 1\r\n\r\n";
    strcat(echo_line,busarr);
    strcat(echo_line,echo_line2);
    //printf("echo_lint_len = %d\n",strlen(echo_line2));
    send(sock,echo_line,strlen(echo_line),0);
    //printf("数据发送成功了\n");
    printf("正在查询，请稍后\n");
    char buf[5000];
    char arr[5000];
    char *pin = buf;
    char *pout = arr;
    memset(arr,0,5000);
    size_t olen = 5000;
    memset(buf,0,5000);
//  int mm =  recv(sock,buf,4999,MSG_WAITALL);
    int m1 = recv(sock,buf,4999,0);
    //printf("buf len == %d\n",strlen(buf));
    char buf2[5000];
    memset(buf2,0,5000);
    int m2 = recv(sock,buf2,4999,0);
    //printf("buf2 == %d\n",strlen(buf2));
    strcat(buf,buf2);

    size_t len = strlen(buf); 
   // printf("%d\n",len);
    iconv_t cd = iconv_open("utf-8","gb2312");
    if(cd == 0)
    {
        printf("error");
        return 0;
    }

    if(iconv(cd,&pin,&len,&pout,&olen) == -1)
    {
        printf("转码错误\n");
        //return 0;
    }

    iconv_close(cd);



//这里把recv函数返回的数值大小返回来，因为我们在读取数据的时候，可能存在一个问题就是，打印的时候可能遇到了\0然后就没有打印完全
//
    //printf("%s\n",arr);
    FILE* pf = fopen("txt","a+");
    fwrite(arr,1,strlen(arr),pf);

    char *pread = arr;
    while((*pread++) != 0  )
    {
if((*pread) <0 )
      printf("%c",*pread);
    }
printf("\n");
    return a;
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
     printf("huixian\n");
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
 
void *handler_request(void *arg)
{
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
 
     if(get_line(sock,buf,sizeof(buf)) <= 0)
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
     i = 0;
     while(isspace(buf[j])&&j<sizeof(buf)&&i<sizeof(url))
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
             //exe_cgi();
         }
         else
         {
             printf("hahahahah\n\n");
             printf("method : %s\n url :%s \n path : %s\n cgi : %d\nquery_string:%s\n    ",method,url,path,cgi,query_string);
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

