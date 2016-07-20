#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int socket_client(char *ip, int port)
{
    int sockfd = 0;
    char buffer[1024];
    char str[5];
    struct sockaddr_in serv_addr; 
   while(1){
    memset(buffer, '\0',sizeof(buffer));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080); 

    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    if (read(sockfd, buffer, sizeof(buffer)) < 0)
    {
        printf("\n Error : Read Failed \n");
        return 1;
    } 
    printf("Server:");
    printf("buffer : [%s]\n\n", buffer);
    sleep(1);
    memset(buffer, '\0', sizeof(buffer));
    //strcpy(buffer, "YA I get client message!2");
    scanf("%s",buffer);
    if (write(sockfd, buffer, strlen(buffer)) < 0) 
    {
        printf("\n Error : Write Failed \n");
        return 1;
    } 
    }
    close(sockfd);
    
    return 0;
}

int main(int argc, char *argv[])
{

    socket_client("192.168.128.34", 5000);
    
    return 0;
}
