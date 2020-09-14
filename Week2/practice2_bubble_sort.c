//Template
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#define SIZE 10

int	compare(int a, int b) {
	if (a > b)
		return 1;
	else
		return 0;
}
int(*funcptr)(int, int) = compare; //pointer to compare function
void buuble_sort(int* arr,int Size) {


	int length = Size;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length-i-1; j++) {
			if (funcptr(arr[j], arr[j + 1])) { 
		//		printf("%d is biiger than %d\n",arr[j],arr[j+1]);//left is bigger -> move
				int	temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
			else
				continue;
		}
	}
}


/***************************************************************
define bubble sort that uses pointer to 'compare' function above
***************************************************************/


int main() {
	int n_array[SIZE] = { 2,-9, 10, 15, 1, 3, -12, 5, 4, 1 };
	buuble_sort(n_array,SIZE);

	for (int i = 0; i < SIZE; i++) {
		printf("%d ", n_array[i]);
	}

	
	return 0;
}
