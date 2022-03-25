#include<stdio.h>
#include<stdlib.h>
typedef struct HeapStruct
{
	int Capacity;
	int Size;
	int *Value;
}Heap;
Heap* CreateHeap(int HeapSize){
	if(HeapSize<1)	printf("Size should be bigger than 0\n");
	else{
	
	Heap* New_Heap = (Heap*)malloc(sizeof(Heap));
	New_Heap->Capacity=HeapSize;
	New_Heap->Size=0;
	New_Heap->Value=(int*)malloc(sizeof(int)*(HeapSize+1));//Value starts at 1
	New_Heap->Value[0]=999999999;
	return New_Heap;}
}

int Find(Heap* heap,int value){
        int i;
        for( i=1;i<=heap->Size;i++)
                if(heap->Value[i]==value)       return 1;
        return 0;
}

void Insert(Heap* heap,int value){
	if(heap->Size==heap->Capacity){
		printf("Insertion Error : Max Heap is full.\n");
		return;
	}
	int i;
	if(Find(heap,value)){
		printf("%d is already in the tree.\n",value);
		return;
	}
	heap->Size++;
	heap->Value[heap->Size]=value;
	for(i=heap->Size;heap->Value[i/2]<value; i/=2){
		heap->Value[i] = heap->Value[i/2];
		heap->Value[i/2]=value;
	}
	printf("insert %d\n",value);
	//printf("size check %d\nvalue check %d\n",heap->Size,heap->Value[heap->Size-1]);
}
int DeleteMax(Heap* heap){
	if(heap->Size==0)	printf("Deletion Error : Max heap is empty!\n");
	else{
	printf("Max Element : %d deleted\n",heap->Value[1]);
	int i,child;
	int MaxValue,LastValue;
	MaxValue=heap->Value[1];
	LastValue=heap->Value[heap->Size--];//after find last value, size--
	for(i=1;i*2<=heap->Size;i=child){
		child=i*2;
	if(child!=heap->Size&&heap->Value[child+1]>heap->Value[child])
		child++; // chose bigger child
	if(LastValue < heap->Value[child]) //when child is biiger than LastValue
		heap->Value[i] = heap->Value[child]; //child go up
	else // when LastValue is bigger than child ->i th value should be Lastvalue
		break;
	}
	heap->Value[i]=LastValue;
	return MaxValue;
	}
}
void PrintHeap(Heap* heap){
	int i=1;
	if(heap->Size==0) printf("Print Error : Max heap is empty!\n");
	else{
	for(i=1;i<=heap->Size;i++)	printf("%d ",heap->Value[i]);
	printf("\n");
}}
int main(int argc,char* argv[])
{
	FILE* fi = fopen(argv[1],"r");
	char cv;
	Heap* MaxHeap;
	int HeapSize,key;
	while(!feof(fi))
	{
		fscanf(fi,"%c", &cv);
		switch(cv){
		case 'n' :
			fscanf(fi,"%d",&HeapSize);
			MaxHeap=CreateHeap(HeapSize);
			break;
		case 'i' :
			fscanf(fi,"%d",&key);
			Insert(MaxHeap,key);
			break;
		case 'd' :
			DeleteMax(MaxHeap);
			break;
		case 'p' :
			PrintHeap(MaxHeap);
			break;
		case 'f' :
			fscanf(fi,"%d",&key);
			if(Find(MaxHeap,key))
				printf("%d is in the tree.\n",key);
			else
				printf("%d is not in the tree.\n",key);
			break;
		}
	}
	return 0;
}
