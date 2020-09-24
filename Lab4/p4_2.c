#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Stack{
	int* key;
	int top;
	int max_stack_size;
}Stack;
Stack* CreateStack(int max){
	Stack* S =NULL;
	S = (Stack*)malloc(sizeof(struct Stack));

	if(S==NULL)	{printf("Error\n");};
	
	S->key = (int*)malloc(sizeof(int)*max);
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
		S->key[S->top+1]=X-48;
		S->top+=1; //top++
		printf("%d ",X-48);
	}
}
int IsEmpty(Stack* S){
	if(S->top==-1)	return 1;
	else return 0;

}
int Pop(Stack* S){
	if(IsEmpty(S))	printf("Error Stack is Empty\n");
	else{
	S->top-=1; // top--
	return S->key[(S->top)+1];
	}

}
void DeleteStack(Stack* S){
	free(S->key);
	free(S);
}
int Postfix(Stack *S, char input_str){
	int a,b;
	int result;
	switch(input_str){
		case '+':
			a=Pop(S);
			b=Pop(S);
			result=a+b;
			Push(S,result+48);
			break;
		case '-':
			a=Pop(S);
			b=Pop(S);
			result=b-a;
			Push(S,result+48);
			break;
		case '*':
			a=Pop(S);
			b=Pop(S);
			result=a*b;
			Push(S,result+48);
			break;
		case '/':
			a=Pop(S);
			b=Pop(S);
			result=b/a;
			Push(S,result+48);
			break;
		case '%':
			a=Pop(S);
			b=Pop(S);
			result=b%a;
			Push(S,result+48);
			break;
		default:
			Push(S,input_str);
			break;
	}
	return result;



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
		result=Postfix(stack,input_str[i]);
	}
	printf("\nevaluation result : %d\n",result);
	fclose(fi);
	DeleteStack(stack);


}
