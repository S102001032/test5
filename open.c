#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>

int main(){
int fd,size;
char a[]="Linux programmer!",buffer[80];
fd = open("/home/whitestone/num.txt",O_WRONLY);
write(fd ,a ,sizeof(a));
close(fd);
fd = open("/home/whitestone/num.txt",O_RDONLY);
size = read(fd ,buffer ,sizeof(buffer));
close(fd);
printf("%s",buffer);
}
