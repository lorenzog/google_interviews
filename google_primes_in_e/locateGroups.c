#include <stdio.h>

//#define dbg

// to define off_t type of 64bits
#define _FILE_OFFSET_BITS 64

void usage(char* name) {
	printf("Usage: %s <primes list> [level] [offset] [digit to search]\n", name);
	printf("\nwhere [level] is the position of the digit into a 10-digit prime number\n");
	printf("and [offset] is given in terms of number of line (starting at 0)\n");
}

/*
 * locates the places in the file where groups of digits begins
 *
 * argv[0] program name
 * argv[1] file to search
 * argv[2] position of the digit
 * argv[3] offset from where to begin
 * argv[4] the digit to look for, starting at offset
 */
int main (int argc, char** argv) {

#ifdef dbg
	printf("argc: %d\n", argc);
#endif

	if ( argc < 2 )
	{
		usage(argv[0]);
		return 1;
	}

	// the position at which we're searching for the digit
	int level = 0;
	// from where we begin
	long offset = 0;
	// the digit we're looking for
	int digit = 0;

	/*
	 * command-line parsing
	 */
	if ( argc > 2 )
		level = atoi(argv[2]);

	if ( argc > 3 )
		offset = atol(argv[3]);

	if ( argc > 4 )
		digit = atoi(argv[4]);
	/*
	 * end command-line parsing
	 */

	// show what we're doing
	printf("seeking digit %d at level %d from offset %ld\n", digit, level, offset);

	// open the file
	FILE *f = fopen (argv[1], "r");

#ifdef dbg
	// print the address of the file pointer
	// used in case a linux cannot open files > 4gb
	printf("file: %x\n", f);
#endif

	// array holder: the line read from the file gets copied into this
	char n[11];
	// counter (the digit we're looking for)
	int i = 0;
	// the decimal value
	unsigned long long value;
	// line counter
	unsigned long line;
	// positions of blocks
	//unsigned long block[10];
	__off_t block[10];
	
	/*
	// print header
	for ( i = 0 ; i < 10 ; i++ )
		printf("%d", i);
	printf(" <- position\n");
	for ( i = 0 ; i < 10 ; i++ )
		printf("|");
	 */
	printf("\n");

	// jump to the desired offset
	//fseeko(f, offset, SEEK_SET);
	// and modify the line counter
	//line = (offset / 11)-1;
	
	// jump to the desired offset expressed as line number
	//
	// HACK: in a 4.2Gb file, the offset gets too big for unsigned long long around 
	// position 2025173590 in the file
	// so we use the line numbers
	//
	// remember that: offset = lines*11
	fseeko(f, 0, SEEK_SET);
	for ( i = 0 ; i < 11 ; i++ )
		fseeko(f, offset, SEEK_CUR);
	line = offset;
	
	// reset counter
	//i = 1;
	i = ( argc > 4 ) ? digit : 0;

	if ( digit == 0 && level == 0 )
	{
		printf("at level %d there cannot be digit %d\n", level, digit);
		printf("assuming digit: 1\n");
		i = 1;
	}

	// read the string + the \n value
	while ( fread(n, sizeof(char), 11, f) == 11 )
	{
		// the prime number
		value = atoi(n);	

		// if the n-th digit is equal to 
		// the first digit we're looking for
		// note: -'0' used to go from ascii -> int
		if ( n[level]-'0' == i ) 
		{
			// save the position
			//block[i] = ftell(f);
			block[i] = ftello(f);

			/*
			 * position is line * 11
			 */
			//printf("%lld - digit %d at pos %d starts at line %ld, file pos: %ld\n", value, i, level, line, block[i]);
			// printing in a more grepable format
			printf("%ld \t <- at this line starts digit %d at pos %d; p: ", line, i, level);
			//printf("\tchar: ");
			int k;
			for ( k = 0 ; k < 10 ; k++ )
				printf("%c", n[k]);
			printf("\n");

			// increment the counter
			i++;
			// increment the line number
			line++;

			// if we've already reached the 9
			if ( i > 9 )
				// get out of the loop
				break;
			// else keep reading from the file
			continue;
		}
		// anyway, increment the line number
		line++;
	}

	// close the file
	fclose(f);

	return 0;
}
