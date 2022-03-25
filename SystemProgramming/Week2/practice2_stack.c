//Template
#include <stdio.h>
#include <stdlib.h>



typedef struct Node_ {
	int Data;
	struct Node *prev;
}Node_;


typedef struct Stack {
	//Node top;
	Node_ *last_node;
	int Size;
}Stack_;

typedef Node_* Node;
typedef Stack_* Stack;


Stack InitializeStack() {
	Stack new_stack = (Stack)malloc(sizeof(Stack_));
	new_stack->last_node = NULL;
	return new_stack;
};
void Push(Stack stack, int nData) {

	Node new_node = (Node)malloc(sizeof(Node_));
	new_node->Data = nData;
	new_node->prev = stack->last_node;
	stack->last_node = new_node;
	printf("%d pushed\n", nData);
}
int Pop(Stack stack) {
	int value = stack->last_node->Data;
	Node temp = stack->last_node;
	stack->last_node = stack->last_node->prev;
	free(temp);
	printf("%d poped\n", value);
	return value;
}


int main(void) {
	Stack My_Stack = InitializeStack();
	Push(My_Stack, 1);
	Push(My_Stack, 2);
	Push(My_Stack, 3);
	Push(My_Stack, 4);
	Pop(My_Stack);
	Pop(My_Stack);
	Pop(My_Stack);
	Pop(My_Stack);
	free(My_Stack);
	
	return 0;
}


