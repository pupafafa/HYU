#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
bool IsZero(int );
bool Equal(int ,int ); // if equal return true
int Successor(unsigned int a);
int Add(unsigned int a,unsigned int );
int Subtract(int , int );
#define INT_MAX 2147438647
void main(int argc,char** argv){
	int input1,input2;
	input1=atoi(argv[1]);
	input2=atoi(argv[2]);
	//since # of inputs is 2, argc equals 3
	
	printf("Is %d zero? ",input1);
	if(IsZero(input1))printf("True\n");
	else printf("False\n");

	printf("Is %d zero? ",input2);
	if(IsZero(input2))printf("True\n");
	else printf("False\n");

	printf("Does %d equal %d? ",input1,input2);
	if(Equal(input1,input2))printf("True\n");
	else printf("False\n");

	int successor1,successor2;
	successor1=Successor(input1);
	successor2=Successor(input2);
	printf("%d's next number is %d\n",input1,successor1);
	printf("%d's next number is %d\n",input2,successor2);

	int add;
	add=Add(input1,input2);
	printf("%d + %d = %d\n",input1,input2,add);

	int sub;
	sub=Subtract(input1,input2);
	printf("%d - %d = %d\n",input1,input2,sub);

}

bool IsZero(int a){
	if(a==0)return true;
	else return false;
}
bool Equal(int a, int b){
	if(a==b)return true;
	else return false;
}
int Successor(unsigned int a){
	if(a+1<INT_MAX)	{return a+1;}
	else return a;
}
int Add(unsigned int a,unsigned int b){
	if(a+b<INT_MAX) {return a+b;}
	else return INT_MAX;
}
int Subtract(int a,int b){
	if(a>b)	{return a-b;}
	else return 0;
}
