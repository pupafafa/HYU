#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct _DisjointSet
{
	int size_maze;
	int* ptr_arr;
} DisjointSets;
void init(DisjointSets* sets,DisjointSets* maze_print, int num){
	int i,Size;
	Size=num*num+1; //1~n*n
	sets->size_maze=Size;
	sets->ptr_arr=(int*)malloc(sizeof(int)*Size);
	maze_print->size_maze=2*num*num+1;
	maze_print->ptr_arr=(int*)malloc(sizeof(int)*2*num*num+1);
	for(i=0;i<Size;i++)
		sets->ptr_arr[i]=0;
	for(i=0;i<maze_print->size_maze;i++)
		maze_print->ptr_arr[i]=0;
}
int Find(DisjointSets* sets, int i){
	/*if(sets->ptr_arr[i]<=0)
		return i; 
	else
		return(ptr_arr[i]=Find(sets,ptr_arr[i]));

		*/
	while(sets->ptr_arr[i]>0)
		i=sets->ptr_arr[i];
	return i;
		}
void Union(DisjointSets* sets, int i, int j){
	if(sets->ptr_arr[Find(sets,j)]<sets->ptr_arr[Find(sets,i)])
		sets->ptr_arr[Find(sets,i)]=Find(sets,j);
	else
	{
		if(sets->ptr_arr[Find(sets,j)]==sets->ptr_arr[Find(sets,i)])
			sets->ptr_arr[Find(sets,i)]--;
		sets->ptr_arr[Find(sets,j)]=Find(sets,i);

	}
}
int smaller(int a, int b){
	if(a<b)	return a;
	else return b;
}
void CreateMaze(DisjointSets* sets, DisjointSets* maze_print, int num){
	srand(time(NULL));
	int direction_arr[4]={1,-1,num,-num};//right left up down
	int random_num;
	int direction;
	int adjacent;
	while(Find(sets,1)!=Find(sets,num*num)){
		random_num=rand()%(num*num)+1; // select random between 1~n*n
		direction=direction_arr[rand()%4];
		adjacent=random_num+direction;
		if(adjacent<1||adjacent>num*num) // out of range
			continue;
		if(random_num%num==1&&direction==-1)
			continue;
		if(random_num%num==0&&direction==1)
			continue;
		if(Find(sets,random_num)!=Find(sets,adjacent)){ 
			int small=smaller(random_num,adjacent);
			Union(sets,random_num,adjacent);
			//remove wall
			if(direction==1||direction==-1)//left right
				maze_print->ptr_arr[small]=1;
			else if(direction==num||direction==-num)//up down
				maze_print->ptr_arr[small+num*num]=1;
		}
	}
}

void PrintMaze(DisjointSets* sets,int num){
	int i=1;
	int j=num*num+1;
	int k=1;
	for(k=1;k<=num;k++)
		printf("~~");
	printf("*\n");
	while(j<2*num*num){
		printf("  ");
		while(1){
			//printf("%d ",i++);
			if(sets->ptr_arr[i]==1)
				printf("  ");
			else
				printf("| ");
			i++;
			//printf("%d ", sets->ptr_arr[i++]);
		
			if(i%num==0){
				if(sets->ptr_arr[i]==1)
                                printf("  ");
                        else
                                printf("| ");
                        i++;
			//	printf("%d ",i++);
			//	printf("%d ",sets->ptr_arr[i++]);
				break;}

		}
		printf("\n");
		while(1){
			//printf("%d ",j++);
			//printf("%d ",sets->ptr_arr[j++]);
			if(sets->ptr_arr[j]==1)
				printf("  ");
			else
				printf("~~");
			j++;
			if(j%num==0){
				 if(sets->ptr_arr[j]==1)
                                printf("  ");
                        else
                                printf("~~");
                        j++;
			printf("*");
			//	printf("%d ",j++);
				//printf("%d ",sets->ptr_arr[j++]);
				break;}
		}
		printf("\n");
	}

}
void FreeMaze(DisjointSets* sets,DisjointSets* maze_print){
	free(sets->ptr_arr);
	free(sets);
	free(maze_print->ptr_arr);
	free(maze_print);
}

int main(int argc,char* argv[])
{
	int num,i;
	FILE* fi = fopen(argv[1],"r"); //not fopen?
	DisjointSets* sets;
	DisjointSets* maze_print;
	fscanf(fi,"%d",&num);
	sets=(DisjointSets*)malloc(sizeof(DisjointSets));
	maze_print=(DisjointSets*)malloc(sizeof(DisjointSets));
	init(sets,maze_print,num);
	CreateMaze(sets,maze_print,num);
	PrintMaze(maze_print,num);
	FreeMaze(sets,maze_print);

	return 0;




}
