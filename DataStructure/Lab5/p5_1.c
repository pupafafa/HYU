#include<stdio.h>
#include<stdlib.h>
struct CompleteTree{
	int size;
	int nodeNum;
	int* Element;
};
typedef struct CompleteTree* Tree;

Tree CreateTree(int treeSize)
{
	Tree tree;
	tree=(Tree)malloc(sizeof(Tree));
	tree->size=treeSize;
	tree->nodeNum=0;
	tree->Element=(int*)malloc(sizeof(int)*(tree->size+1));//first index=1
	return tree;
}
void Insert(Tree tree,int value)
{ 	if(tree->nodeNum  >= tree->size)
	{
	printf("Error! Tree is FULL.\n");
	return;
	}
	tree->Element[tree->nodeNum+1]=value;
	tree->nodeNum+=1;
}

void printTree(Tree tree)
{
	int i=1;
	for(i;i<=tree->size;i++)	printf("%d ",tree->Element[i]);
}
void FreeTree(Tree tree)
{	free(tree->Element);
	free(tree);
}

void printPreorder(Tree tree,int index)
{	if(index<=tree->nodeNum){
		printf("%d ",tree->Element[index]);
		printPreorder(tree,index*2);
		printPreorder(tree,index*2+1);
	}
}
void main(int argc,char* argv[])
{
	FILE *fi;
	Tree tree;
	int treeSize;
	int tempNum;
	fi=fopen(argv[1],"r");
	fscanf(fi,"%d",&treeSize);
	tree = CreateTree(treeSize);
	while(fscanf(fi, "%d", &tempNum) ==1)
	{
		Insert(tree, tempNum);
	}
	printf("Preorder : ");
	printPreorder(tree,1);
	FreeTree(tree);
}
