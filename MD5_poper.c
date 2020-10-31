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
 
void rand_str(char *, size_t);

int main(void) {
	int n=0;
	int m = 0;
    char str[]= "lol0loll0l0l0l0l0l0l0l0l0l0l0l0l0";// make the last character non-zero so we can test based on it later
	unsigned char result[MD5_DIGEST_LENGTH];
	char salty[] = "d470d406"; 					// from line 57 of bot.sh
	char buzzword[] = "0BADBEEF"; //string in the md5 that needs to be found
	// start time stuff for seed
	long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    s  = spec.tv_sec;
	ms = spec.tv_nsec;
	srand(ms); //seed with ms
	int len = 33;
	int found = 0;
	char testy[44]; // container for the conversion
	testy[0] = '\0';
	char buff[6]; //buffer while we convert
	int i;
	while(found != 1 ){
		rand_str(str, sizeof str - 1); //get a random string
		strcat(str,salty);		
		MD5(str, strlen(str),result); //hash salted string
		char testy[44]; // container for the conversion
		char buff[6]; //buffer while we convert
		//		getting result into a working var
		for(i = 0; i < MD5_DIGEST_LENGTH; i++) 
		{		//take unsigned char and make to char
			snprintf(buff, sizeof(buff), "%02X", (unsigned char)result[i]);
			strcat(testy,buff);//write the char buffer to the working var
		}
		for(i=1;i<=32;i++){ //parse working var for the extra prechars
			testy[i-1]=testy[i];
		}
		testy[32]='\0';
		// character searching		
		while(n<33){ 
				log[0]++;
				n++; // load next char in result
				m++; //laod next char in buzz
				while(testy[n] == buzzword[m]){
					log[m]++;
					n++;
					m++;
					if(m ==  8){
						printf("\n  ***FOUND***\n");
						found = 1;
						printf("%s : %s",str,testy);
						printf("\n  ***FOUND***\n");
						break;
						} //if for final match
				} //while for continued finding
			}// char match end
			n++; //goto next char in result because no match on cur char;
			m=0; //start from first char in buzzword
		}//END OF entire result parsing / while
		n=0;
		buff[1] = '\0';
		testy[1] = '\0';
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
