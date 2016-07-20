#include <stdlib.h>

#include <stdio.h>

#include <winsock2.h>

#include <string.h>

#include <time.h>

#include <windows.h>

#include <process.h>

#include <math.h>



 #define    BUFLEN        2000                  // 緩沖區大小

 #define WSVERS        MAKEWORD(2, 0)        // 指明版本2.0 

 #pragma comment(lib,"ws2_32.lib")         // 指明winsock 2.0 Llibrary



    

    SOCKET    sock,sockets[100] = {NULL};                          /* socket descriptor            */

 //    int    cc;                                /* recv character count            */

    char    *packet = NULL;               /* buffer for one line of text    */

     char *pts,*input;

    HANDLE hThread;

    unsigned threadID;


 unsigned int __stdcall Chat(PVOID PM ) 

{

       time_t    now;

      (void) time(&now);

       pts = ctime(&now);

        char buf[2000];



while(1)

{

     int cc = recv(sock, buf, BUFLEN, 0);   //cc為接收的字符數

    if(cc == SOCKET_ERROR|| cc == 0)

    {

        printf("Error: %d.----",GetLastError());

        printf("與服務器斷開連接！\n");

        CloseHandle(hThread);

       (void)closesocket(sock);

        break;

    }

    else if(cc > 0) 

    {

    //    buf[cc] = '\0';

         printf("%s\n",buf);

     //    printf("輸入數據（exit退出):  \n");

     }     

}

    return 0;

 }
 

 int main(int argc, char *argv[])

 {

    time_t    now;

      (void) time(&now);

        pts = ctime(&now);

    char    *host = "127.0.0.1";        /* server IP to connect         */

 //    char    *host = "172.18.33.155";

 //    char    *host = "172.18.33.93";

 //    char    *host = "172.18.187.1";

     char *service = "5050";          /* server port to connect       */

 //    char *service = "50000";

     struct  sockaddr_in sin;            /* an Internet endpoint address    */

    WSADATA wsadata;

     WSAStartup(WSVERS, &wsadata);       /* 啟動某版本Socket的DLL        */        



    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;

     sin.sin_port = htons((u_short)atoi(service));    //atoi：把ascii轉化為int. htons：主機序(host)轉化為網絡序(network), s--short
     sin.sin_addr.s_addr = inet_addr(host);           //如果host為域名，需要先用函數gethostbyname把域名轉化為IP地址



    sock = socket(PF_INET, SOCK_STREAM,0);



     connect(sock, (struct sockaddr *)&sin, sizeof(sin));


     printf("\t\t\t\tChat 多人聊天程序 \n");

    printf("\t\t\t\t       (Client) \n");

     hThread = (HANDLE)_beginthreadex(NULL, 0,Chat, NULL, 0, &threadID);    

     printf(" \t\t\t\t 【您可以自由發言】\n\n");

 while(1)

 {

     char buf1[2000];
     

     //     scanf("%s",&buf1);

     

         gets_s(buf1);

         if(!strcmp(buf1 ,"exit"))

              goto end;


       (void) send(sock,buf1, sizeof(buf1), 0);

        (void) time(&now);

         pts = ctime(&now);

       printf(" 發送成功！ ------時間： %s\n",pts);

}

    

end:    CloseHandle(hThread);

        closesocket(sock);

         WSACleanup();                     /* 卸載某版本的DLL */  



    printf("按回車鍵繼續...");

    getchar();

     return 0;                           /* exit */

 }
