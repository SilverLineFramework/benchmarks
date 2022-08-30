#include <stdio.h>
#include "blowfish.h"

int
benchmark_main(int argc, char *argv[])
{
	BF_KEY key;
	unsigned char ukey[100];
	unsigned char indata[40],outdata[40],ivec[8];
	int num;
	int by=0,i=0;
	int encordec=-1;
	char *cp,ch;
	FILE *fp,*fp2;

    #ifdef ENCODE
        #ifdef LARGE
        char fin[80] = "data/mibench/security/input_large.asc";
        #else
        char fin[80] = "data/mibench/security/input_small.asc";
        #endif
        encordec = 1;
    #else
        #ifdef LARGE
        char fin[80] = "data/mibench/security/output_large_bf.enc";
        #else
        char fin[80] = "data/mibench/security/output_small_bf.enc";
        #endif
        encordec = 0;
    #endif

/* Read the key */
char cpval[80] = "1234567890abcdeffedcba0987654321";
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

/* open the input and output files */
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

    if(fp2 != NULL) {
	for(j=0;j<i;j++)
	{
		/*printf("%c",outdata[j]);*/
		fputc(outdata[j],fp2);
	}
    }
	i=0;
}

close(fp);
// close(fp2);
return 0;
// exit(1);
}

