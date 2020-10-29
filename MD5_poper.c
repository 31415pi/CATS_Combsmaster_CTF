// -lcrypto -lssl
#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <openssl/md5.h>
 
//#define SALT "d470d460"  // from line 57 of bot.sh
void rand_str(char *, size_t);

//char* itoa(int value, char* buffer, int base);

int main(void) {
	int n=1;
	int m = 0;
//	char result[] = "abcd232323232323232323232efg0badbeef23232323232";
    char str[] = { [41] = '\1' }; 				// make the last character non-zero so we can test based on it later
	unsigned char result[MD5_DIGEST_LENGTH];
	char salty[] = "d470d460"; 					// from line 57 of bot.sh
	char buzzword[] = "0badbeef"; //string in the md5 that needs to be found

	// start time stuff for seed
	long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    s  = spec.tv_sec;
	ms = spec.tv_nsec;
	srand(ms); //seed with ms
	int len = strlen(buzzword);



	//debug stuff
//	int debugquit = 40;			//limiting debug loop to 101 cycles to make sure random is gen quick enough 
	int found = 0;

		//start while loop here:

	while(found!= 1 ){
		//debugquit--; // keep while loop to 10 max
		//removed from while '&& (debugquit > 0)'
		rand_str(str, sizeof str - 1); //get a random string
		for(int v = 32; v < 41; v++){// appending salt
			str[v] = salty[(v-32)];
		}
		
		MD5(str, strlen(str), result); //hash salted string

//		printf("\n-%s : ",str);	//print the salted rando string and the result of hashing
//		for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
//			printf("%02x",result[i]);
//		printf("\n");


// character searching			
		if (result[n] == buzzword[m]){ //match, keep looking
			printf(" n%d,  m%d", n,m);
			n++; // load next char in result
			m++; //laod next char in buzz
				while(result[n] == buzzword[m]){
					printf(" n%d,  m%d", n,m);

					n++;
					m++;
					printf("+");
				} //while for continued finding
			printf("\nmatch");
			
			if(m == len ){
				printf("\n  ***FOUND***\n");
				found = 1;
				printf("%s : ",str);
				for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
					printf("%02x",result[i]);
				printf("\n  ***FOUND***\n");
				break;
				
			} //if for final match
			
		}// char match end
		printf('.');
//		for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
//			printf("%02x",result[i]);
//		printf(" %d,  %d", n,m);
		n++; //goto next char in result because no match on cur char;
		if (n==34)
			printf('^');
			n=0;
		m=0; //start from first char in buzzword
	} // end of while loop

			
	return EXIT_SUCCESS;
}

void rand_str(char *dest, size_t length) {
    char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (length-- > 0) {
        size_t index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        *dest++ = charset[index];
    }
    *dest = '\0';
}
