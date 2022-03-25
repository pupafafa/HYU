#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct _Queue* Queue;
typedef struct _Graph* Graph;
int num_of_node=0;
struct _Queue
{
	int* key;
	int first;
	int rear;
	int qsize;
	int max_queue_size;
};
struct _Graph
{
	int size;
	int* node;
	int** matrix;
};
Graph CreateGraph(int* nodes){
	Graph myGraph;
	myGraph->size=num_of_node;
	myGraph->node=nodes;
	myGraph->matrix=(int**)malloc(sizeof(int*)*num_of_node);
	int k;
	for(k=0;k<num_of_node;k++)
		myGraph->matrix[k]=(int*)malloc(sizeof(int)*num_of_node);
	int a,b;
	for(a=0;a<num_of_node;a++){
		for(b=0;b<num_of_node;b++){
			myGraph->matrix[a][b]=0;}
	}
	return myGraph;
};
void InsertEdge(Graph G, int a, int b)
{
	G->matrix[a][b]=1;

};
void DeleteGraph(Graph G)
{
	int i;
	for(i=0;i<G->size;i++)
		free(G->matrix[i]);
	free(G->matrix);
	free(G->node);

};


void main(int argc, char* argv[]){
	FILE* fp = fopen(argv[1],"r");
	int* arr;
	int save[100];
	int i;
	char num;
	Graph myGraph = NULL;
	if(fp==NULL){
		printf("There is no file : %s\n", argv[1]);
	}
	while(!feof(fp)){
	if(fscanf(fp,"%c",&num)=='-') {printf("fucked\n");break;}
	else if(num==' ')	continue;
	else{
		++num_of_node;
		save[i++]=num-48;
		}
	}
	num_of_node--;
	arr=(int*)malloc(sizeof(int)*num_of_node);
	for(i=0;i<num_of_node;i++){
		arr[i]=save[i];
		printf("%d ",arr[i]);
	}
	printf("\n");
	//CreateGraph(arr);
	//FILE* fp2=fopen(argv[1],"r");
	//int check=0;
	//char num2;
	/*
	while(!feof(fp2)){
	while(!feof(fp2) && check==num_of_node){
		char a,b,c;
		a=fscanf(fp2,"%c",&num2);
		b=fscanf(fp2,"%c",&num2);
		c=fscanf(fp2,"%c",&num2);
		InsertEdge(myGraph,a-48,c-48);


	}break;
	fscanf(fp2,"%c",&num2);
	check++;





			}
	free(arr);
	int q,w;
	for(q=0;q<num_of_node;q++){
		for(w=0;w<num_of_node;w++){
			printf("%d ",myGraph->matrix[q][w]);
		}printf("\n");
	}
	printf("\n");
*/
//	DeleteGraph(myGraph);
	fclose(fp);
}
