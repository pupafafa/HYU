#include<stdio.h>
#include<stdlib.h>
int Max(int a,int b) {
	if(a>=b) return a;
	else return b;
}
typedef struct AVLNode* AVLTree;
typedef AVLTree Position;
struct AVLNode
{
	int value;
	AVLTree Left;
	AVLTree	Right;
	int Height;
};

int Height(Position P)
{
	if(P==NULL)	return -1;
	else return P->Height;
}
Position SingleRotateWithLeft(Position k2){
	Position k1;
	k1=k2->Left;
	k2->Left=k1->Right;
	k1->Right=k2;
	
	k2->Height = Max(Height(k2->Left),Height(k2->Right)) +1;
	k1->Height = Max(Height(k1->Left),k2->Height)+1;
	
	return k1;
}
Position SingleRotateWithRight(Position k2){
	Position k1;
	k1=k2->Right;
	k2->Right=k1->Left;
	k1->Left=k2;

        k2->Height = Max(Height(k2->Left),Height(k2->Right)) +1;
        k1->Height = Max(Height(k1->Right),k2->Height)+1;

	return k1;
}
AVLTree Insert(int value,AVLTree T){
	if(T==NULL){
	T=malloc(sizeof(struct AVLNode));
	if(T==NULL)	{printf("Out of sapce\n");return NULL;}
	else{
		T->value=value;
		T->Height=0;
		T->Left = NULL;
		T->Right=NULL;
		}
	}
	else if(value<T->value){
		T->Left=Insert(value,T->Left);
		if(Height(T->Left)-Height(T->Right)==2){
			if(value<T->Left->value)
				T=SingleRotateWithLeft(T);
			//else
				//T=DoubleRotateWithLeft(T);
		}
	}
	else if(value>T->value){
		T->Right=Insert(value,T->Right);
		if(Height(T->Right)-Height(T->Left)==2){
			if(value>T->Right->value)
				T=SingleRotateWithRight(T);
		//	else
				//T=DoubleRotateWithRight(T);
		
		}
	}
	else{
	printf("[Error] %d already in the tree!\n",value);
	return T;
	}
	T->Height=Max(Height(T->Left),Height(T->Right))+1;
	return T;
	}
void PrintInorder(AVLTree T){
	if(T==NULL)	return;
	else{
		PrintInorder(T->Left);
		printf("%d(%d) ",T->value,T->Height);
		PrintInorder(T->Right);
	}
}
void DeleteTree(AVLTree T){
	if(T==NULL)	return;
	else{
	DeleteTree(T->Left);
	DeleteTree(T->Right);
	free(T);
	}
}
int main(int argc, char* argv[]){
	FILE* fp = fopen(argv[1],"r");
	AVLTree myTree = NULL;
	int num;
	if(fp==NULL){
		printf("There is no file : %s\n",argv[1]);
		exit(-1);
	}
	while(fscanf(fp,"%d",&num) != EOF){
		myTree=Insert(num,myTree);
		PrintInorder(myTree);
		printf("\n");
	}
	DeleteTree(myTree);
	return 0;
}
