#include<stdio.h>
#include<stdlib.h>
#define LEN 8
#define SWAP(x,y){int t;t=x;x=y;y=t;}

void selectionSort(int*,int,int(*)(int,int));
void insertionSort(int*,int,int(*)(int,int));
void bubbleSort(int*,int,int(*)(int,int));

void print(int*,int len);
int ascending(int,int);
int descending(int,int);

int main(void){
  int number[LEN]={10,9,1,2,5,3,8,7};

 selectionSort(number,LEN,ascending);
 print(number,LEN);

 insertionSort(number,LEN,descending);
 print(number,LEN);

 bubbleSort(number,LEN,ascending);
 print(number,LEN);

 return 0;
}

int selectedldx(int* arr,int from,int to,int(*compar)(int,int)){
 int selected=from;
int i;
for(i=from+1;i<to;i++)if(compar(arr[i],arr[selected])<0){
selected=i;
}
return selected;
}

void selectionSort(int* arr,int len,int(*compar)(int,int)){
int i;
for(i=0;i<len;i++){
int selected=selectedldx(arr,i,len,compar);
if(selected!=i){SWAP(arr[i],arr[selected])}
}
}
int insertedldx(int* arr,int eleldx,int(*compar)(int,int)){
int i;
for(i=0;i<eleldx;i++)if(compar(arr[i],arr[eleldx])>0){
break;
}
return i;
}

void insert(int* arr,int eleldx,int inserted){
int ele=arr[eleldx];
int i;
for(i=eleldx;i>inserted;i--){arr[i]=arr[i-1];}
arr[inserted]=ele;
}

void insertionSort(int* arr,int len,int(*compar)(int,int)){
int i;
for(i=0;i<len;i++){
int inserted=insertedldx(arr,i,compar);
if(inserted !=i){insert(arr,i,inserted);}
}
}
void bubbleTo(int* arr,int len,int(*compar)(int,int)){
int i;
for(i=0;i<len;i++){bubbleTo(arr,len-i,compar);}
}
void print(int* arr,int len){
int i;
for(i=0;i<len;i++){printf("%d",arr[i]);}
 printf("\n");
}

int ascending(int a,int b){return a-b;}
int descending(int a,int b){return -ascending(a,b);}
