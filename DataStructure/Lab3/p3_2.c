#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct Node* ptr; // ptr is struct pointer
typedef ptr List;
typedef ptr Position ;    // and also Position
typedef struct Node
{
	int element;
	Position next;
}Node;
List MakeEmpty(List header)
{
	header=(List)malloc(sizeof(Node));
	header->element = -1;
	header->next = NULL;
	
}
int IsEmpty(List L)
{
	if(L->next==NULL)	return 1;
	else return 0;
}
int IsLast(Position P, List L)
{
	if(P->next==NULL)	return 1;
	else return 0;
}
void Insert(int input,List L, Position P)
{
	Position temp=NULL;
	temp=(Position)malloc(sizeof(Node));
	if(temp==NULL){
		printf("Out of space!!!\n");
		return;
	}
	
	temp->next=P->next;
	P->next = temp;
	temp->element = input;
}
void PrintList(List L)
{
	ptr nextcell=L->next;
	while(nextcell!=NULL){
		printf("key : %d  ",nextcell->element);
		nextcell=nextcell->next;
	}
}
Position Find(int x,List L)
{
	ptr cell=L;
	while(cell!=NULL && cell->element != x)
		cell=cell->next;
	return cell;

}
Position FindPrevious(int x,List L)
{
	Position P; // P is previous positon
	P=L;
	while(P->next!=NULL&&P->next->element!=x)
		P=P->next;
	return P;
}
void Delete(int x,List L)
{
	Position P,temp;
	P=FindPrevious(x,L);
	if(!IsLast(P,L))
	{
		temp=P->next;
		P->next=temp->next;
		free(temp);
		
	}
}
void DeleteList(List L)
{
	Position P, Tmp;
	P=L->next;
	L->next=NULL;
	while(P!=NULL){
		Tmp=P->next;
		free(P);
		P=Tmp;
	}
	free(L);
}
int main(int argc, char **argv){
	char command;
	int key1,key2;
	FILE *input;
	Position header;
	Position tmp;
	if(argc ==1){
		printf("No input file\n");
		return 0;
	}
	else
		input=fopen(argv[1],"r");
	header = MakeEmpty(header);
	while(1){
		command=fgetc(input);
		if(feof(input))	break; //break at the end of file(txt)
		switch(command){
			case 'i':
				fscanf(input,"%d %d",&key1,&key2);
				if(key2<=0) Insert(key1,header,header);
				else{
					tmp=Find(key2,header);
					if(tmp==NULL)
					{
						printf("Insertion(%d) Failed : cannot find the location to be inserted\n",key1);
						break;
					}
					Insert(key1,header,tmp);
				}
				break;
			case 'd':
				fscanf(input,"%d",&key1);
				if(Find(key1,header)==NULL)
				{
					printf("Deletion failed : element %d is not in the list\n",key1);
					break;
				}
				else
					Delete(key1,header);
				break;
			case 'f':
				fscanf(input,"%d",&key1);
				tmp=FindPrevious(key1,header);
				if(IsLast(tmp,header))
					printf("Could not find %d in the list\n",key1);
				else{
					if(tmp->element>0)
						printf("Key of the previous node of %d is %d.\n",key1,tmp->element);
					else
						printf("Key of the previous node of %d is header.\n",key1);
				}
				break;
			case 'p':
				PrintList(header);
				printf("\n");
				break;
			default:
				break;
		}

	}
	DeleteList(header);
	fclose(input);
	return 0;
}
