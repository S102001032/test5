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
#define    BUFLEN    2000             // �w�R�Ϥj�p
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

      sprintf(buf1," �ɶ��G %s  \t�i�ڪ��u�{���G %d �j\n",pts,threadid);

       (void) send(sock,buf1, sizeof(buf1), 0); 

        sprintf(buf2," �u�{�� <%d> �Ȥ�<IP:%s �ݤf:%d>  enter  \n",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port);

       printf("%s ",buf2);        

       printf("\t�N�۰ʧ⦹�ƾڵo�e���Ҧ��Ȥ�I \n");

       for(int i=0;i<=number;i++)

      {            

         if(sockets[i] != NULL && sockets[i] != sock)

          {

        (void) send(sockets[i],buf2, sizeof(buf2), 0); 

           printf(" �o�e�ܽu�{��<%d>���\�I\n",ThreadID[i]);

           }

        }

       printf(" \n");





 flag1:cc = recv(sock, buf3, BUFLEN, 0);   //cc���������r�ż�

   if(cc == SOCKET_ERROR|| cc == 0)

   {

       (void) time(&now);

       pts = ctime(&now);

        sprintf( buf3," �u�{�� <%d> �Ȥ�<IP:%s �ݤf:%d>  leave !  \n \t\t�ɶ��G %s",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port,pts);

        sock = NULL;    

       sockets[number] = NULL;

      CloseHandle(hThread[number]);

       printf("%s ", buf3);        

      printf("\t�N�۰ʧ⦹�ƾڵo�e���Ҧ��Ȥ�I \n");

       for(int i=0;i<=number;i++)

       {            

           if(sockets[i] != NULL && sockets[i] != sock)

           {

           (void) send(sockets[i], buf3, sizeof(buf3), 0);     

          printf(" �o�e�ܽu�{��<%d>���\�I\n",ThreadID[i]);

            }            

         }

    printf(" \n");

    }



     else if(cc > 0) 

    {

       (void) time(&now);

       pts = ctime(&now);

    sprintf(buf4," �u�{�� <%d> �Ȥ�<IP:%s �ݤf:%d>�� �G%s  \n \t\t�ɶ� �G %s",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port,buf3,pts);

   

       printf("%s ",buf4);

        printf("\t�N�۰ʧ⦹�ƾڵo�e���Ҧ��Ȥ�I \n");

       for(int i=0;i<=number;i++)

        {            

         if(sockets[i] != NULL && sockets[i] != sock)

        {

         (void) send(sockets[i],buf4, sizeof(buf4), 0);         

            printf(" �o�e�ܽu�{��<%d>���\�I\n",ThreadID[i]);

          }            

     }

        printf(" \n");



        goto flag1;

     }

        (void) closesocket(sock);

     

        return 0;

        }


void main(int argc, char *argv[]) 

/* argc: �R�O��ѼƭӼơA �Ҧp�GC:\> TCPdaytimed 8080 

argc=2 argv[0]="TCPdaytimed",argv[1]="8080" */

 {

   int     alen;                    /* from-address length               */    

   WSADATA wsadata; 

    char    *service = "5050";    

   WSAStartup(WSVERS, &wsadata);                         //�[�� winsock 2.2 library
   msock = socket(PF_INET, SOCK_STREAM, 0);              //�ͦ��M���r�CTCP��ĳ��=6�A UDP��ĳ��=17
 memset(&Sin, 0, sizeof(Sin));

  Sin.sin_family = AF_INET;

    Sin.sin_addr.s_addr = INADDR_ANY;                    //���w�j�w���f��IP�a�}�CINADDR_ANY��ܸj�w(��ť)�Ҧ������f�C

    Sin.sin_port = htons((u_short)atoi(service));        //atoi--��ascii��Ƭ�int�Ahtons - �D����(host)��Ƭ�������(network), s(short) 

     bind(msock, (struct sockaddr *)&Sin, sizeof(Sin));   // �j�w�ݤf���]�MIP�a�})

    listen(msock, 5);                                    //���C���׬�5



    printf("\t\t\t\t Chat �h�H��ѵ{�� \n");

   printf("\t\t\t\t       (Server) \n");

   (void) time(&now);

    pts = ctime(&now);

   printf("\t\t\t  �ɶ� �G%s",pts);

        number = -1;

     while(1)                                    //�˴��O�_������

    {                

        alen = sizeof(struct sockaddr);

        ssock = accept(msock, (struct sockaddr *)&fsin, &alen);

        number ++;

        hThread[number] = (HANDLE)_beginthreadex(NULL, 0,Chat,NULL, 0, &threadID);        

    }

    (void) closesocket(msock);

    WSACleanup();                         //������ winsock 2.2 library

}