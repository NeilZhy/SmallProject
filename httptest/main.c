#include<pthread.h>
#include"httpd.h"
   
   static void usage(const char *proc)
   {
       printf("Usage: %s [local_ip] [local_port]\n",proc);
   }
   
   int main()
  {
      int connet_sock = connetser();
if(connet_sock == -1)
{
printf("链接失败\n");
}
if(!shutdown(connet_sock,SHUT_RDWR))
{
printf("链接关闭成功了\n");
}

    //  int listen_sock = startup(argv[1],atoi(argv[2]));
      //while(1)
     // {
//	printf("hahahhaha\n");
  //        struct sockaddr_in client;
      //    socklen_t  len = sizeof(client);
    //      int new_sock = accept(listen_sock,(struct sockaddr*)&client,&len);
//printf("heheheheh\n");
  //        if(new_sock < 0)
    //      {
      //     print_log(strerror(errno),FATAL);
         //     continue;
     //   //  }
       //   printf("lian jie cheng gong\n\n");
         // printf("new_sock client_client_sock [%s : %d]\n",inet_ntoa(client.sin_addr),    ntohs(client.sin_port));
  
         // pthread_t id;
         // int ret = pthread_create(&id,NULL,handler_request,(void *)new_sock);
         // if(ret != 0)
         // {
           //   print_log(strerror(errno),WARNING);
             // close(new_sock);
        // }
          //else
         // {
           //   pthread_detach(id);
         // }
     //}
     // close(listen_sock);
  
      return 0;
  }
                                 
