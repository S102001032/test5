#include<stdio.h>
int main(){
int number[10]={9,2,3,1,5,4,8,7,10,6};
int i=0,j=0;
int temp=0;
for(i=0;i<10;i++){
for(j=1;j<10;j++){
if(number[j]>number[i]){
temp=number[j];
number[j]=number[i];
number[i]=temp;
}
}
}
for(i=0;i<10;i++){
printf("%d",number[i]);
}
return 0;
}
