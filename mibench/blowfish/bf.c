#include <stdio.h>
#include "blowfish.h"

int main(int argc, char *argv[])
{
	BF_KEY key;
	unsigned char ukey[100];
	unsigned char indata[100],outdata[100],ivec[8];
	int num=0;
	int by=0,i=0;
	int encordec=-1;
	char *cp,ch;
	FILE *fp,*fp2;

    for (int i = 0; i < 8; i++) { ivec[i] = 0; }

    #ifdef ENCODE
        #ifdef LARGE
        char fin[100] = "data/mibench/bf_enc_large.asc";
        #else
        char fin[100] = "data/mibench/bf_enc_small.asc";
        #endif
        encordec = 1;
    #else
        #ifdef LARGE
        char fin[100] = "data/mibench/bf_dec_large.enc";
        #else
        char fin[100] = "data/mibench/bf_dec_small.enc";
        #endif
        encordec = 0;
    #endif

/* Read the key */
char cpval[100] = "1234567890abcdeffedcba0987654321";
cp = cpval;
while(i < 64 && *cp)    /* the maximum key length is 32 bytes and   */
{                       /* hence at most 64 hexadecimal digits      */
	ch = toupper(*cp++);            /* process a hexadecimal digit  */
	if(ch >= '0' && ch <= '9')
		by = (by << 4) + ch - '0';
	else if(ch >= 'A' && ch <= 'F')
		by = (by << 4) + ch - 'A' + 10;
	else                            /* error if not hexadecimal     */
	{
		printf("key must be in hexadecimal notation\n");
		exit(-1);
	}

	/* store a key byte for each pair of hexadecimal digits         */
	if(i++ & 1)
		ukey[i / 2 - 1] = by & 0xff;
}

BF_set_key(&key,8,ukey);

if(*cp)
{
	printf("Bad key value.\n");
	exit(-1);
}

fp = fopen(fin, "r");
// fp2 = fopen(fout, "w");
fp2 = NULL;

i=0;
while(!feof(fp))
{
	int j;
	while(!feof(fp) && i<40)
		indata[i++]=getc(fp);

	BF_cfb64_encrypt(indata,outdata,i,&key,ivec,&num,encordec);
    i = 0;
}

fclose(fp);

// close(fp2);
return 0;
// exit(1);
}

