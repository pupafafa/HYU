#include<stdio.h>
#include<stdlib.h>
typedef struct BinarySearchTree* Tree;
struct BinarySearchTree{
	int value;
	Tree left;
	Tree right;
};
Tree findNode(Tree root,int key){
	if(root==NULL)
		printf("%d is not in the tree.\n",key);
	else if(key<root->value)
		findNode(root->left,key);
	else if(key>root->value)
		findNode(root->right,key);
	else //find where key can be
		return root;

}
void printInorder(Tree root){
	if(root){
	printInorder(root->left);
	printf("%d ",root->value);
	printInorder(root->right);
	}
}
void deleteTree(Tree root){
	if(root){
	deleteTree(root->left);
	deleteTree(root->right);
	free(root);
	}

}
Tree insertNode(Tree root,int key){
//find location first.

	if(root==NULL){
		root = malloc(sizeof(struct BinarySearchTree));
		if(root == NULL)
			printf("Out of space.\n");
		else{
			root->value = key;
			root->left = NULL;
			root->right = NULL;
			printf("insert %d\n",key);
		}
		
	}

	else if(key==root->value)
		printf("Insertion Error : There is already %d  in the tree.\n",key);
	else if(key<root->value)
		root->left = insertNode(root->left,key);
	else if(key>root->value)
		root->right = insertNode(root->right,key);

	return root;

}

void main(int argc, char* argv[])
{
	FILE *fi = fopen(argv[1], "r");
	char cv;
	int key;

	Tree root = NULL;

	while(!feof(fi))
	{
		fscanf(fi,"%c", &cv);
		switch(cv){
		case 'i':
			fscanf(fi,"%d",&key);
			root = insertNode(root,key);
			break;
	/*	case 'd':
			fscanf(fi,"%d",&key);
			deleteNode(root,key);
			break;*/
		case 'f':
			fscanf(fi,"%d",&key);
			findNode(root,key);
			break;
		case 'p':
			fscanf(fi,"%c",&cv);
			if(cv == 'i')
				printInorder(root);
			printf("\n");
			break;
		}
	}

}
