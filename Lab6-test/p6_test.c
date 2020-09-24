#include <stdio.h>

#include <stdlib.h>

 

typedef struct BinarySearchTree* Tree;

struct BinarySearchTree{

   int value;

   Tree left;

   Tree right;

};

 

Tree insertNode(Tree root, int key){

   if(root==NULL){

      root=malloc(sizeof(struct BinarySearchTree));

      if(root==NULL) printf("Out of space!!\n");

      else{

         root->value=key;

         root->left=root->right=NULL;

         printf("insert %d\n",key);

      }

   }

   else if(key<root->value) root->left=insertNode(root->left,key);

   else if(key>root->value) root->right=insertNode(root->right,key);

   else printf("Insertion Error : There is already %d in the tree.\n",key);

   return root;

}

void findNode(Tree root, int key){

   if(root==NULL){

      printf("%d is not in the tree\n",key);

   }

   else if(key<root->value) findNode(root->left,key);

   else if(key>root->value) findNode(root->right,key);

   else printf("%d is in the tree\n",root->value);

}

void printInorder(Tree root){

   if(root!=NULL){

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

Tree getMaxValueInTree(Tree parentNode,Tree root){

        if(root==NULL) return NULL;
	else if(root->right==NULL) return root;
	else return getMaxValueInTree(parentNode,root->right);

}

Tree deleteNode(Tree root, int key){
	//printf("%d deleteNode access\n",root->value);
	Tree Tmp;

	//printf("123");

   if(root==NULL) printf("Deletion Error : %d is not in the tree.\n",key);

   else if(key<root->value) root->left=deleteNode(root->left,key);

   else if(key>root->value) root->right=deleteNode(root->right,key);

   else{

      if(root->left!=NULL && root->right!=NULL){

         Tmp=getMaxValueInTree(Tmp,root->left);

        // printf("max value is %d\n",Tmp->value);

         root->value=Tmp->value;

         root->left=deleteNode(root->left,Tmp->value);

      }

   

      else{
	//printf("else access\n");
         Tmp=root;

         if(Tmp->left==NULL) {
		 root=root->right;
	 //	printf("left NULL\n");
	 }
	 else if(Tmp->right==NULL) {
		 root=root->left;
	 //	printf("right NULL\n");
	 }
	 //printf("before free\n");
         free(Tmp);
	//printf("free done\n");
         printf("Delete %d\n",key);

      }

   }

   return root;

 

}

 

void main(int argc, char* argv[]){

   FILE *fi=fopen(argv[1],"r");

   char cv;

   int key;

   Tree root=NULL;

   while(!feof(fi)){

      fscanf(fi,"%c",&cv);

      switch(cv){

      case 'i':

         fscanf(fi,"%d",&key);

         root=insertNode(root,key);

         break;

      case 'd':

         fscanf(fi,"%d",&key);

         deleteNode(root,key);

         break;   

      case 'f':

         fscanf(fi,"%d",&key);

         findNode(root,key);

         //printf("find done\n");

         break;

      case 'p':

         fscanf(fi,"%c",&cv);

         if(cv=='i') printInorder(root);

         printf("\n");

         break;

      }

   }

   deleteTree(root);

}

