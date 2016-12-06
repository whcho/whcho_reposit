#include <stdio.h>

int summation(int start, int end);

int main(){
	printf("%d\n",summation(1,100));
	return 0;
}

int summation(int start, int end){
	int i = start;
	int result = 0;
	while(i<=end){
		result+= i;
		i++;
	}

	return result;
}
