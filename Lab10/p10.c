#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node{
	int vertex;
	int dist;//distance
	int prev;
}Node;
typedef struct Graph{
	int size;
	int** vertices;
	Node* nodes;
}Graph;
typedef struct Heap{
	int Capacity;
	int size;
	Node* Element;
}Heap;
Graph CreateGraph(int size){
	Graph G;
	G.size=size;
	G.vertices=(int**)malloc(sizeof(int*)*size);
	int i,j;

	for(i=0;i<size;i++){
		G.vertices[i]=(int*)malloc(sizeof(int)*size);
		for(j=0;j<size;j++){
			G.vertices[i][j]=0;
		}
	}

	G.nodes=(Node*)malloc(sizeof(Node)*size);
	for(i=0;i<size;i++){ //initialize every node
		G.nodes[i].vertex=i;
		G.nodes[i].dist=1000000000;
		G.nodes[i].prev=0;
	}
	G.nodes[1].dist=0;

	return G;
}

Heap* CreateMinHeap(int heapSize){
	Heap* myheap;
	myheap=(Heap*)malloc(sizeof(Heap));
	myheap->Capacity=heapSize;
	myheap->size=0;
	myheap->Element=(Node*)malloc(sizeof(Node)*heapSize);
	return myheap;
	}

void InsertToMinHeap(Heap* minHeap, int vertex, int distance){
	Node N;
	N.vertex=vertex;
	N.dist=distance;
	minHeap->Element[++minHeap->size] = N;
	int i;
	for(i=++minHeap->size;minHeap->Element[i/2].dist>distance;i/=2)
		minHeap->Element[i]=minHeap->Element[i/2];
	
	minHeap->Element[i]=N;
}

//q.pop()
Node DeleteMin(Heap* minHeap){
	int i=1;
	Node min,last;
	min = minHeap->Element[1];
	last = minHeap->Element[minHeap->size--];
	int Child=i*2;
	for(i=1;i*2<=minHeap->size;i=Child){
		Child=i*2;
		if(Child!=minHeap->size&&minHeap->Element[Child+1].dist<minHeap->Element[Child].dist)
			Child++; //chose smaller child
		if(last.dist > minHeap->Element[Child].dist)
			minHeap->Element[i]=minHeap->Element[Child];
			//percolating
		else
			break;
		}
	minHeap->Element[i]=last;
	return min;

}
//dijkstra algorithm
void PrintShortestPath(Graph G){
	Heap* Heap = CreateMinHeap(G.size*G.size);
        int i,j;
        //insert start point 1 to minheap
        InsertToMinHeap(Heap,1,0);
	while(Heap->size!=0){
		Node cur_node = DeleteMin(Heap);
		for(i=1;i<G.size;i++){
			if(G.vertices[cur_node.vertex][i]!=0){//check adjacent nodes to cur_node
				Node next = G.nodes[i];
				int next_dist = cur_node.dist + G.vertices[cur_node.vertex][i];
				if(next_dist<G.nodes[i].dist){
					G.nodes[i].dist=next_dist;
					G.nodes[i].prev=cur_node.vertex;
					InsertToMinHeap(Heap,G.nodes[i].vertex,G.nodes[i].dist);
				}
			}
		}
	}

	//printf("line 106\n");
	//from line 108 to 132 is result-printing code
	for(i=2;i<G.size;i++){
		int* save=(int*)malloc(sizeof(int)*G.size);
		//printf("i : %d\n",i);
		if(G.nodes[i].prev==0){
			printf("Cannot reach to node %d.\n",i);
		}
		else{
	//	printf("nodes : %d dist : %d prev %d\n",G.nodes[i].vertex,G.nodes[i].dist,G.nodes[i].prev);
		int SIZE=0;
		int before=G.nodes[i].prev;
		save[SIZE++]=before;
		//printf("line 119\n");
		while(before!=1){
			//printf("line 121\n");
			before=G.nodes[before].prev;
			save[SIZE++]=before;
		}
		
		for(j=SIZE-1;j>=0;j--)
			printf("%d->",save[j]);
	
		printf("%d ",G.nodes[i].vertex);
		printf("(cost: %d)\n",G.nodes[i].dist);
		}
		free(save);
	}
//free
	for(i=0;i<G.size;i++){
		free(G.vertices[i]);

	}
	free(G.vertices);
	free(G.nodes);
	free(Heap->Element);
	free(Heap);

}




void main(int argc, char* argv[]){
	FILE* fi = fopen(argv[1],"r");
	Graph g;
	int size;
	fscanf(fi,"%d\n",&size);
	g=CreateGraph(size+1);
	char temp = 0;
	while(temp!='\n'){
		int node1,node2,weight;
		fscanf(fi,"%d-%d-%d",&node1,&node2,&weight);
		g.vertices[node1][node2] = weight;
		temp = fgetc(fi);
	}
	int i,j;
	/*for(i=1;i<=size;i++){
		for(j=1;j<=size;j++){
			printf("%d ",g.vertices[i][j]);
		}
		printf("\n");
	}*/
	PrintShortestPath(g);
}	




