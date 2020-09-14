#include <stdio.h>
#include <stdlib.h>
int main(void) {
	int n;
	int length;
	int i;

	scanf("%d", &n);
	char** pp_data = NULL;
	pp_data = (char**)malloc(sizeof(char*)*n);
	//1. define & dynamic allocation

	for (i = 0; i < n; i++) {
		scanf("%d", &length);
		pp_data[i] = (char*)malloc(sizeof(char)*length);
	//	puts(pp_data[i]);
		scanf("%s", pp_data[i]);
	}


	for (i = 0; i < n; i++) {
		printf("%s\n", pp_data[i]);
	}

	for (i = 0; i < n; i++) {
		free(pp_data[i]);
	}
	free(pp_data);

	return 0;
}
