#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
void btos(int *src, int len){
	int tem;
		for (int i = 0;i < len;i++){
			for (int j = 0;j < len-i-1 ; j++){
				if(src[j] < src[j+1]){
				tem = src[j];
				src[j] = src[j+1];
				src[j+1] = tem;
				}
			}
		}

}

void sort(int *src, int len){
	int tem;
		for (int i = 0;i < len;i++){
			for (int j = 0;j < len-i-1 ; j++){
				if(src[j] > src[j+1]){
				tem = src[j];
				src[j] = src[j+1];
				src[j+1] = tem;
				}
			}
		}
}

int main(){
//	int a[5];
	char buffer[10];
	int c,i=0,e;
	int *a,*b
/*		fd = open("/home/whitestone/num.txt",O_RDONLY);

		size = read(fd,buffer,sizeof(a));
		close(fd);*/

	FILE *fp = fopen("num.txt","r");

	memset(a,0,sizeof(a));

	if(fp){
 	while(fgets(buffer , 10 , fp)!=NULL){
		e = atoi(buffer);
		a[i]=e;
		i++;
//		b = malloc(sizeof(int));
//	                                                                                                                                                                                                                         	a+i=b;
		printf(" %d\n",e);
	}

	printf("How many numbers in the case? = %d\n",sizeof(a));
	printf("Increment(1) or Decreasoing(2)?\n");
	scanf ("%d",&c);
	if(c==1){
		sort(a, 5);
		for(int i = 0;i < 5;i++)
		printf(" %d\n", a[i]);
}

	if(c==2){
	btos(a, 5);
		for(int i = 0;i < 5;i++)
		printf(" %d\n", a[i]);
}
//	FILE *fp = fopen("num.txt","w");
//		fputs(a ,fp);

		/*fd = open("/home/whitestone/num.txt",O_WRONLY);
		write(fd,sizeof(a));
		close(fd);*/

	fclose(fp);
}
}
