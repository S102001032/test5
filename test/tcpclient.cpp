#include <stdlib.h>

#include <stdio.h>

#include <winsock2.h>

#include <string.h>

#include <time.h>

#include <windows.h>

#include <process.h>

#include <math.h>



 #define    BUFLEN        2000                  // �w�R�Ϥj�p

 #define WSVERS        MAKEWORD(2, 0)        // ��������2.0 

 #pragma comment(lib,"ws2_32.lib")         // ����winsock 2.0 Llibrary



    

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

     int cc = recv(sock, buf, BUFLEN, 0);   //cc���������r�ż�

    if(cc == SOCKET_ERROR|| cc == 0)

    {

        printf("Error: %d.----",GetLastError());

        printf("�P�A�Ⱦ��_�}�s���I\n");

        CloseHandle(hThread);

       (void)closesocket(sock);

        break;

    }

    else if(cc > 0) 

    {

    //    buf[cc] = '\0';

         printf("%s\n",buf);

     //    printf("��J�ƾڡ]exit�h�X):  \n");

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

     WSAStartup(WSVERS, &wsadata);       /* �ҰʬY����Socket��DLL        */        



    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;

     sin.sin_port = htons((u_short)atoi(service));    //atoi�G��ascii��Ƭ�int. htons�G�D����(host)��Ƭ�������(network), s--short
     sin.sin_addr.s_addr = inet_addr(host);           //�p�Ghost����W�A�ݭn���Ψ��gethostbyname���W��Ƭ�IP�a�}



    sock = socket(PF_INET, SOCK_STREAM,0);



     connect(sock, (struct sockaddr *)&sin, sizeof(sin));


     printf("\t\t\t\tChat �h�H��ѵ{�� \n");

    printf("\t\t\t\t       (Client) \n");

     hThread = (HANDLE)_beginthreadex(NULL, 0,Chat, NULL, 0, &threadID);    

     printf(" \t\t\t\t �i�z�i�H�ۥѵo���j\n\n");

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

       printf(" �o�e���\�I ------�ɶ��G %s\n",pts);

}

    

end:    CloseHandle(hThread);

        closesocket(sock);

         WSACleanup();                     /* �����Y������DLL */  



    printf("���^�����~��...");

    getchar();

     return 0;                           /* exit */

 }
