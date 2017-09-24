#ifndef   __MYBASE64_H_
#define  __MYBASE64_H_

   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>

const char _Base[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=" };

static union
{
	struct
	{
		unsigned long a : 6;
		unsigned long b : 6;
		unsigned long c : 6;
		unsigned long d : 6;
	}Sdata;
	unsigned char c[3];
}Udata;

char * Encbase64(char * orgdata, unsigned long orglen, unsigned long *newlen);

char * Decbase64(char * orgdata, unsigned long orglen);




//----------------ÀÏµÄ
    const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
	char *base64_encode(const char*data, int data_len);
	char *base64_decode(const char*data, int data_len);
	char *base64_decode(const char*data, int data_len, int &ori_len);
	
	static char find_pos(char ch);
#endif