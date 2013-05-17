#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
	float flo = 2.0;
	char* str = malloc(10);
	
	sprintf(str, "%f", flo);
	printf("string: %s\n", str);
	return (0);
}
