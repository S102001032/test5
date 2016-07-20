#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include "conio.h"
#include <windows.h>
#include <process.h>
#include <math.h>
#define QLEN       5
#define    WSVERS    MAKEWORD(2, 0)
#define    BUFLEN    2000             // 緩沖區大小
#pragma comment(lib,"ws2_32.lib")  //winsock 2.2 library
SOCKET    msock, ssock;            /* master & slave sockets           */
SOCKET    sockets[100] = {NULL};
int cc;

char    *pts;                    /* pointer to time string           */

time_t    now;                    /* current time                       */

char buf[2000];                      /* buffer                          */

char *input;

HANDLE hThread1,hThread[100] = {NULL};

unsigned int threadID,ThreadID[100],number;



struct    sockaddr_in fsin;

struct    sockaddr_in Sin;



unsigned int __stdcall Chat(PVOID PM) 

{    

 
       char buf2[2000];

      char buf3[2000];

       char buf4[2000];

        (void) time(&now);

       pts = ctime(&now);

      sockets[number] = ssock;

        SOCKET    sock = ssock;

      ThreadID[number] = threadID;

       unsigned int threadid = threadID;

      sprintf(buf1," 時間： %s  \t【我的線程號： %d 】\n",pts,threadid);

       (void) send(sock,buf1, sizeof(buf1), 0); 

        sprintf(buf2," 線程號 <%d> 客戶<IP:%s 端口:%d>  enter  \n",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port);

       printf("%s ",buf2);        

       printf("\t將自動把此數據發送給所有客戶！ \n");

       for(int i=0;i<=number;i++)

      {            

         if(sockets[i] != NULL && sockets[i] != sock)

          {

        (void) send(sockets[i],buf2, sizeof(buf2), 0); 

           printf(" 發送至線程號<%d>成功！\n",ThreadID[i]);

           }

        }

       printf(" \n");





 flag1:cc = recv(sock, buf3, BUFLEN, 0);   //cc為接收的字符數

   if(cc == SOCKET_ERROR|| cc == 0)

   {

       (void) time(&now);

       pts = ctime(&now);

        sprintf( buf3," 線程號 <%d> 客戶<IP:%s 端口:%d>  leave !  \n \t\t時間： %s",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port,pts);

        sock = NULL;    

       sockets[number] = NULL;

      CloseHandle(hThread[number]);

       printf("%s ", buf3);        

      printf("\t將自動把此數據發送給所有客戶！ \n");

       for(int i=0;i<=number;i++)

       {            

           if(sockets[i] != NULL && sockets[i] != sock)

           {

           (void) send(sockets[i], buf3, sizeof(buf3), 0);     

          printf(" 發送至線程號<%d>成功！\n",ThreadID[i]);

            }            

         }

    printf(" \n");

    }



     else if(cc > 0) 

    {

       (void) time(&now);

       pts = ctime(&now);

    sprintf(buf4," 線程號 <%d> 客戶<IP:%s 端口:%d>說 ：%s  \n \t\t時間 ： %s",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port,buf3,pts);

   

       printf("%s ",buf4);

        printf("\t將自動把此數據發送給所有客戶！ \n");

       for(int i=0;i<=number;i++)

        {            

         if(sockets[i] != NULL && sockets[i] != sock)

        {

         (void) send(sockets[i],buf4, sizeof(buf4), 0);         

            printf(" 發送至線程號<%d>成功！\n",ThreadID[i]);

          }            

     }

        printf(" \n");



        goto flag1;

     }

        (void) closesocket(sock);

     

        return 0;

        }


void main(int argc, char *argv[]) 

/* argc: 命令行參數個數， 例如：C:\> TCPdaytimed 8080 

argc=2 argv[0]="TCPdaytimed",argv[1]="8080" */

 {

   int     alen;                    /* from-address length               */    

   WSADATA wsadata; 

    char    *service = "5050";    

   WSAStartup(WSVERS, &wsadata);                         //加載 winsock 2.2 library
   msock = socket(PF_INET, SOCK_STREAM, 0);              //生成套接字。TCP協議號=6， UDP協議號=17
 memset(&Sin, 0, sizeof(Sin));

  Sin.sin_family = AF_INET;

    Sin.sin_addr.s_addr = INADDR_ANY;                    //指定綁定接口的IP地址。INADDR_ANY表示綁定(監聽)所有的接口。

    Sin.sin_port = htons((u_short)atoi(service));        //atoi--把ascii轉化為int，htons - 主機序(host)轉化為網絡序(network), s(short) 

     bind(msock, (struct sockaddr *)&Sin, sizeof(Sin));   // 綁定端口號（和IP地址)

    listen(msock, 5);                                    //隊列長度為5



    printf("\t\t\t\t Chat 多人聊天程序 \n");

   printf("\t\t\t\t       (Server) \n");

   (void) time(&now);

    pts = ctime(&now);

   printf("\t\t\t  時間 ：%s",pts);

        number = -1;

     while(1)                                    //檢測是否有按鍵

    {                

        alen = sizeof(struct sockaddr);

        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);

        number ++;

        hThread[number] = (HANDLE)_beginthreadex(NULL, 0,Chat,NULL, 0, &threadID);        

    }

    (void) closesocket(msock);

    WSACleanup();                         //卸載載 winsock 2.2 library

}