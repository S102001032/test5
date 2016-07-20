#include <stdio.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <string.h>
 #include <unistd.h>
 #include <netinet/in.h>
 #include <sys/socket.h>
 #include <sys/wait.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 
int main()
{
 int sockfd, new_fd, numbytes, sin_size;
 char buf[1000000];
 struct sockaddr_in my_addr;
 struct sockaddr_in their_addr;
 struct stat filestat;
 FILE *fp;
   //TCP socket
  if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
            perror("socket");
            exit(1);
}
  //Initail, bind to port 2323
 my_addr.sin_family = AF_INET;
 my_addr.sin_port = htons(2324);
 my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 bzero( &(my_addr.sin_zero), 8 );
//binding
 if ( bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
         perror("bind");
         exit(1);
  }  
 //Start listening
 if ( listen(sockfd, 10) == -1 ){
          perror("listen");
          exit(1);
 }  
 //Get file stat
 if ( lstat("TEST.MP3", &filestat) < 0){
          exit(1);
 } printf("The file size is %lu\n", filestat.st_size);
  fp = fopen("TEST.MP3", "rb");
 //Connect
 if ( (new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)) == -1 ){
           perror("accept"); exit(1);
 }
//Sending file
 while(!feof(fp)){
 numbytes = fread(buf, sizeof(char), sizeof(buf), fp);
 printf("fread %d bytes, ", numbytes);
 numbytes = write(new_fd, buf, numbytes);
 printf("Sending %d bytes\n",numbytes);
 }
 
 close(new_fd);
 close(sockfd);
 return 0;
 }