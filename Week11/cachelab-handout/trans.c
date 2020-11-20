//2016024957
//s=5 e=1 b=5
//32sets direct cache  32bytes = 8 integers can be inserted

/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

char transpose_submit_desc[] = "Transpose submission";

//subpart 8x8


void square1(int M, int N, int input[N][M], int output[M][N], int row, int column);
void square2(int M, int N, int input[N][M], int output[M][N], int row, int column);
void find (int M, int N, int input[N][M], int output[M][N], int row, int column);
typedef void (*block_t)(int M, int N, int input[N][M], int output[M][N], int row, int column);
void transpose_submit(int M, int N, int input[N][M], int output[M][N])
{
	block_t block;
	if(N==32&&M==32) //32x32
		block=square1;
	else if(N==64&&M==64)//64x63
		block=square2;	
	else
		block=find;
	for(int i=0;i<N;i+=8){
		for(int j=0;j<M;j+=8){
			block(M,N,input,output,i,j);
		}
	}
}

void square1(int M, int N, int input[N][M], int output[M][N], int row, int column){
	if(row!=column)
		return find(M,N,input,output,row,column);

	for(int i=row;i<row+8;++i){
		int save=input[i][i];
		for(int j=column;j<column+8;++j){
			if(i==j)
				continue;
			output[j][i]=input[i][j];
		}
		output[i][i]=save;
	}
}

void square2(int M, int N, int input[N][M], int output[M][N], int row, int column){

	int *t= &input[column][row+4];
	int first=t[0];
	int second = t[1];
	int third = t[2];
	int fourth = t[3];
 	
	for(int k=0;k<8;++k){// upper half
		int* t = &input[column+k][row];
		int first = t[0];
		int second = t[1];
		int third = t[2];
		int fourth = t[3];
		t= &output[row][column+k];
		t[0]=first;
		t[64]=second;
		t[128]=third;
		t[192]=fourth;
	}
	for(int k=7;k>0;--k){
		int *t = &input[column+k][row+4];
		int first=t[0];
		int second=t[1];
		int third=t[2];
		int fourth=t[3];
		t=&output[row+4][column+k];
		t[0]=first;
		t[64]=second;
		t[128]=third;
		t[192]=fourth;
	}
	t=&output[row+4][column];
	t[0]=first;
	t[64]=second;
	t[128]=third;
	t[192]=fourth;
}

void find(int M, int N, int input[N][M], int output[M][N], int row, int column){
	for(int i = column;i<column+8 && i <M; ++i){
		for(int j = row; j<row+8 && j<N ; ++j){
			output[i][j] = input[j][i];
		}
	}
}



// trans - A simple baseline transpose function, not optimized for the cache.
 
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{ 
  //trans_checker
      	int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

