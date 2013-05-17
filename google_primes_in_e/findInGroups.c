/*
 * apri file
 * prendi prima cifra del numero
 * salta nel file alla riga dove iniziano i p con prima cifra cercata
 *
 * prendi seconda cifra
 * salta nel file alla riga dove iniziano i p con la seconda cifra cercata 
 * 	a partire dalla riga precedente
 * prendi terza cifra
 * ...
 *
 * condizione di arresto: la riga dove iniziano i p con la n-ma cifra cercata
 * 	a partire dalla riga precedente
 * e` maggiore
 * 	della riga dove finiscono i p con la n-ma cifra cercata..
 *
 * altrimenti itera fino a quando la cifra non e` la nona (a partire da zero)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define dbg

// to define off_t type of 64bits
#define _FILE_OFFSET_BITS 64

/*
 * the offset (in lines) from where begins the p with an incrementing first digit
 * lines[0] -> lines[8]: the more general offset
 * lines[9] -> null value
 * lines[10] -> lines[18]: primes beginning with 10 and ending with 19
 * lines[19] -> null value
 * lines[20] -> lines[28]: ..
 *
 *
 * following lines build with ./locateGroups primes10.dat 1 <offset> | awk ' { print $1,", /<star> p: ",$13," <star>/ } '
 *
 */
unsigned long lines[] = {
	0,		/* null value */
	0,		/* p: 1000000007 */
	47374753, 	/* p: 2000000011 */
	93602003,	/* p: 3000000019 */
	139114278,	/* p: 4000000007 */
	184106689,	/* p: 5000000029 */
	228697834,	/* p: 6000000001 */
	272956818,	/* p: 7000000001 */
	316936120,	/* p: 8000000011 */
	360675661,	/* p: 9000000001 */

	0 , /* p:  1000000007  */
	4814936 , /* p:  1100000009  */
	9607171 , /* p:  1200000041  */
	14380799 , /* p:  1300000003  */
	19137939 , /* p:  1400000023  */
	23878994 , /* p:  1500000001  */
	28604299 , /* p:  1600000009  */
	33315485 , /* p:  1700000009  */
	38014888 , /* p:  1800000011  */
	42700394 , /* p:  1900000043  */

	47374753 , /* p:  2000000011  */
	52038992 , /* p:  2100000011  */
	56692588 , /* p:  2200000009  */
	61337406 , /* p:  2300000041  */
	65970913 , /* p:  2400000011  */
	70595837 , /* p:  2500000001  */
	75214633 , /* p:  2600000041  */
	79822658 , /* p:  2700000007  */
	84422724 , /* p:  2800000051  */
	89016477 , /* p:  2900000017  */

	93602003 , /* p:  3000000019  */
	98181107 , /* p:  3100000027  */
	102753271 , /* p:  3200000087  */
	107318295 , /* p:  3300000001  */
	111877662 , /* p:  3400000013  */
	116431799 , /* p:  3500000011  */
	120979602 , /* p:  3600000011  */
	125521983 , /* p:  3700000021  */
	130058660 , /* p:  3800000003  */
	134589091 , /* p:  3900000007  */

	139114278 , /* p:  4000000007  */
	143633535 , /* p:  4100000027  */
	148148569 , /* p:  4200000037  */
	152659714 , /* p:  4300000013  */
	157165920 , /* p:  4400000021  */
	161666789 , /* p:  4500000013  */
	166163785 , /* p:  4600000001  */
	170656633 , /* p:  4700000057  */
	175144209 , /* p:  4800000013  */
	179628011 , /* p:  4900000013  */

	184106689 , /* p:  5000000029  */
	188582459 , /* p:  5100000011  */
	193054808 , /* p:  5200000033  */
	197523426 , /* p:  5300000023  */
	201986531 , /* p:  5400000031  */
	206446986 , /* p:  5500000039  */
	210904330 , /* p:  5600000033  */
	215358760 , /* p:  5700000067  */
	219808018 , /* p:  5800000027  */
	224254017 , /* p:  5900000027  */

	228697834 , /* p:  6000000001  */
	233137422 , /* p:  6100000009  */
	237575335 , /* p:  6200000087  */
	242008887 , /* p:  6300000061  */
	246437664 , /* p:  6400000007  */
	250863934 , /* p:  6500000009  */
	255290077 , /* p:  6600000067  */
	259711199 , /* p:  6700000003  */
	264129632 , /* p:  6800000027  */
	268544187 , /* p:  6900000013  */

	272956818 , /* p:  7000000001  */
	277367672 , /* p:  7100000051  */
	281773366 , /* p:  7200000019  */
	286177267 , /* p:  7300000027  */
	290579370 , /* p:  7400000033  */
	294979078 , /* p:  7500000031  */
	299374291 , /* p:  7600000003  */
	303767582 , /* p:  7700000003  */
	308158983 , /* p:  7800000017  */
	312548447 , /* p:  7900000001  */

	316936120 , /* p:  8000000011  */
	321321232 , /* p:  8100000023  */
	325702325 , /* p:  8200000033  */
	330083195 , /* p:  8300000011  */
	334460297 , /* p:  8400000001  */
	338834893 , /* p:  8500000013  */
	343208376 , /* p:  8600000089  */
	347578141 , /* p:  8700000013  */
	351945923 , /* p:  8800000007  */
	356312056 , /* p:  8900000027  */

	360675661 , /* p:  9000000001  */
	365038094 , /* p:  9100000009  */
	369395628 , /* p:  9200000039  */
	373755875 , /* p:  9300000013  */
	378111061 , /* p:  9400000003  */
	382464258 , /* p:  9500000021  */
	386816138 , /* p:  9600000001  */
	391167342 , /* p:  9700000001  */
	395515202 , /* p:  9800000017  */
	399861243 , /* p:  9900000001  */

	0		/* XXX end of file */
};

FILE *f;

// the offset from where to start and to stop
unsigned long off_begin, off_end;
// the new starting and ending offset
unsigned long new_off_begin, new_off_end;


/**
 * display usage of the program.
 */
void usage(char* name) {
	printf("Usage: %s <number to check> <primes list>\n", name);
}

/**
 * used to jump to a certain position in the file
 * given the initial offset as a line number (starting from zero).
 */
void jump_to(unsigned long offset) {
	fseeko(f, 0, SEEK_SET);
	int i;
	for ( i = 0 ; i < 11 ; i++ )
		fseeko(f, (__off_t)offset, SEEK_CUR);
}

/**
 * taken from locateGroups.c
 */
unsigned long locateGroup(int position, unsigned long off_begin, char p_n) {
#ifdef dbg
	printf("searching for digit %d at position %d starting from %ld...\n", (p_n-'0')%10, position, off_begin);
#endif

	// we're checking the last digit
	// and it's an even number
	if ( position == 9 && (p_n-'0')%2 == 0 )
	{
		return off_begin;
	}
	// the destination string to be used as a buffer
	char n[11];
	// the line where we're at
	unsigned long line;
	// which now is equal to the beginning offset
	line = off_begin;
	// read the string + the \n value
	while ( fread(n, sizeof(char), 11, f) == 11 )
	{
		// if the n-th digit is equal to 
		// the first digit we're looking for
		// note: -'0' used to go from ascii -> int
		//if ( n[position]-'0' == i ) 
		if ( n[position] - '0' == (p_n-'0')%10 ) 
		{
			/*
			 * position is line * 11
			 */
#ifdef dbg
			printf("%ld \t <- at this line starts digit %d at pos %d; p: ", line, p_n-'0', position);
			int k;
			for ( k = 0 ; k < 10 ; k++ )
				printf("%c", n[k]);
			printf("\n");
#endif

			// get out of the loop ; we've got what we were looking for
			break;
		}
		// nothing found, increment the line number
		line++;
		// and keep searching
	}

	return line;
}

/*
 *
 * argv[0] program name
 * argv[1] number to check
 * argv[2] file to search
 */
int main (int argc, char** argv) {

#ifdef dbg
	printf("argc: %d\n", argc);
#endif

	if ( argc != 3 )
	{
		usage(argv[0]);
		return 1;
	}

	// the number to check as a char
	char* p = (char*) malloc(sizeof(char)*10);
	//char p[10];
	// copy the first 10 digits of the number into the program
	strncpy(p, argv[1], 10);

	// open the file
	f = fopen (argv[2], "r");

	/*
	 * the search will start
	 * from the line where the primes beginning with the digit found at p[0] start
	 * to the line where the primes beginning with the digit p[0]+1 start
	 *
	 * ex: we're looking for number 8281828459
	 * first digit is: 8
	 * the search will start from offset line 316936120 (lines[7] = lines[8-1])
	 * and end with offset line 360675661 (lines[8])
	 *
	 * here p[0] is the first digit
	 */

	char* tmp[3];
	sprintf(tmp, "%c%c", p[0], p[1]);

	// the beginning of the number
	int p_beg = atoi(tmp);
#ifdef dbg
	printf("p_beg: %d\n", p_beg);
#endif
	
	// from where we begin
	off_begin = lines[p_beg];
	// to where we finish
	off_end = lines[p_beg+1];

#ifdef dbg
	printf("off_begin: %ld, off_end: %ld\n", off_begin, off_end);
#endif

	// XXX watch out for the end of file
	// lines[100] = 0 !!
	// so lines_to_scan MUST be > 0
	long lines_to_scan = off_end - off_begin;
	if ( lines_to_scan < 0 )
		printf("we're looking at the end of the file.. watcha\n");
	long lines_scanned = 0;

	// now jump to the first offset
	jump_to(off_begin);
	
	// the position of the digit we're going to examine
	int position;
	// we've already cleared the first 2 digits (0 and 1)
	position = 2;

	do { 
		// search for the next starting point
		new_off_begin = locateGroup(position, off_begin, p[position]);
		// go to the old position
		jump_to(off_begin);

		// check agains the old offset
		if ( new_off_begin > off_end )
		{
			printf("%s is not prime, test 1\n", p);
			return 1;
		}
		
		// search for the starting point for the next digit
		new_off_end = locateGroup(position, off_begin, p[position]+1);
		// go to the old position
		jump_to(off_begin);

#ifdef dbg
		printf("new_off_begin: %ld, new_off_end: %ld\n", new_off_begin, new_off_end);
#endif

		// check against the new offset
		if ( new_off_begin > new_off_end )
		{
			printf("%s is not prime, test 2\n", p);
			return 1;
		}

		// the new starting points
		off_begin = new_off_begin;
		off_end = new_off_end;

		// go to the new position
		jump_to(off_begin);
		

		/*
		if ( new_off_end < off_end )
		{
			printf("%s is not prime, 2\n", p);
			return 1;
		}
		else
			off_end = new_off_end;
			*/

		position++;
		//lines_scanned = off_end - new_off;

	//} while ( position < 9 || lines_scanned > lines_to_scan );
	} while ( position <= 9 );

	printf("%s is prime!\n", p);

	// close the file
	fclose(f);
	free(p);
	return 0;
}

