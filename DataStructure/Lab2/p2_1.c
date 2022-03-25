#include<stdio.h>
void swap(int* a,int*b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void main(){
	int input1,input2;
	printf("enter 2 integers\n");
	scanf("%d %d",&input1,&input2);
	printf("you entered\n%d, %d\n",input1,input2);
	swap(&input1,&input2);
	printf("after swapping\n%d, %d\n",input1,input2);}

