#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Stack{
	char* key;
	int top;
	int max_stack_size;
}Stack;
Stack* CreateStack(int max){
	Stack* S =NULL;
	S = (Stack*)malloc(sizeof(struct Stack));
	//if(S==NULL)
		
	S->key = (char*)malloc(sizeof(char)*max);
	S->top=-1;
	S->max_stack_size=max;
	return S;
}
int IsFull(Stack *S){
	if(S->top==S->max_stack_size-1)	return 1;
	else return 0;


}
void Push(Stack * S,char X){
	if(IsFull(S)==1)
     	{printf("Error Stack is full\n");
	}
	else
	{
		S->key[S->top+1]=X;
		S->top+=1;
		printf("%c inserted\n",X);
	}
}
void main(int argc,char* argv[]){
	FILE* fi =fopen(argv[1],"r");
	Stack* stack;
	char input_str[101];
	int max,i=0,a,b,result;

	fgets(input_str,101,fi);
	max=10;
	stack = CreateStack(max);

	for(i=0;i<strlen(input_str)&&input_str[i]!='#';i++){
		Push(stack,input_str[i]);
	}
	fclose(fi);
	//DeleteStack(stack);


}
