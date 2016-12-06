#include <stdio.h>
#define N 10
void transpose(int A[][N], int B[][N]);

int main(){
	int A[N][N], B[N][N];
	int i=0, j=0;

	for(j=0; j<N; j++)
		for(i=0; i<N; i++)
			A[i][j] = i-j;
	printf("original matrix:\n");
	for(j=0; j<N; j++){
		for(i=0; i<N; i++)
			printf("%4d",A[i][j]);
		printf("\n");

	}

	transpose(A,B);
	printf("transposed matrix:\n");
	for(j=0; j<N; j++){
		for(i=0; i<N; i++)
			printf("%4d",B[i][j]);
		printf("\n");

	}

	return 0;
}

void transpose(int A[][N],int B[][N]){
	int i,j;
	for(j=0; j<N; j++)
		for(i=0; i<N; i++)
			B[i][j] = A[j][i];
}
