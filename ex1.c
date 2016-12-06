#include <stdio.h>

int summation (int start, int end);

int main(){
	int a = 1;
	int b = 100;
	int c = summation(a, b);

	printf("%d\n",c);

	return 0;
}

int summation (int start, int end){
	int result = 0;
	int i = 0;

	for (i=start; i<=end; i++)
		result = result + i;

	return result;
}


