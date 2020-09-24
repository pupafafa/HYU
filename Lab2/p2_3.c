#include<stdio.h>
#include<stdlib.h>
void main(int argc, char** argv){
	printf("enter %s names:\n",argv[1]);
	int number_of_name=atoi(argv[1]);
	char** ptr=NULL;
	ptr=(char**)malloc(sizeof(char*)*number_of_name);
	int i;
	for(i=0;i<number_of_name;i++){
		ptr[i]=(char*)malloc(sizeof(char)*30);
		scanf("%s",ptr[i]);
	}
	printf("the names you entered:\n");
	for(i=0;i<number_of_name;i++){
		printf("%s\n",ptr[i]);

	}

	for(i=0;i<number_of_name;i++)	{free(ptr[i]);}
	
	free(ptr);
	

}
