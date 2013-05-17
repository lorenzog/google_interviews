#include <stdio.h>

int main (int argc, char **argv) {
	
	if ( argc != 3 )
		return 1;
	FILE *e = fopen (argv[1], "r");
	FILE *out = fopen (argv[2], "w");

	char n[11];
	int j = 0;

	printf("writing sub-strings of length 10 to file %s...\n", argv[2]);

	do 
	{
		
		// read 10 digits
		fread(n, sizeof(char), 10, e);
		// no 9-length numbers
		// no odd numbers or mults of 5
		if ( n[0] == '0' || n[9] % 2 == 0  || atoi(n) % 5 == 0 ) 
			continue;
		// write them into the output file
		fwrite(n, sizeof(char), 10, out);
		fputs("\n", out);
		fflush(out);
		
#ifdef _DEBUG
		for ( j = 0 ; j < 10 ; j++ )
			printf("%d ", n[j]-'0');
		printf("\n");
		sleep(1);
#endif
	}
	while ( fseek(e, -9, SEEK_CUR) != -1 );

	fclose(e);
	fclose(out);

	return 0;
}
