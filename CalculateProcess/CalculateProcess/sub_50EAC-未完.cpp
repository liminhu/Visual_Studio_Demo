#include "stdafx.h"
#include <sys/utime.h>
#include <Windows.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int  sub_50EAC(char *a1, char *a2);
inline unsigned int __ROR4__(unsigned int value, int count) { return _rotr(value, count); }


int _tmain_50EAC(int argc, _TCHAR* argv[]){
	printf("Hello World!!!");
	char a1[] = {
		0x61, 0x38, 0x63, 0x35, 0x30, 9, 0x15, 0xCA, 0xFC, 0x6B,
		0x20, 0xB5, 0x3A, 0x1C, 0xA9, 0xC6, 0x23, 0xF, 0xC1, 0x27,
		0x90, 8, 0, 0, 0, 0, 0, 0, 0x33, 0x30,
		0x33, 0x30, 0x33, 0x30, 0x33, 0x30, 0x33, 0x30, 0x33, 0x30,
		0x33, 0x30, 0x33, 0x30, 0x33, 0x30, 0x33, 0x36, 0x33, 0x33,
		0x33, 0x30, 0x33, 0x37, 0x33, 0x37, 0x33, 0x30, 0x33, 0x32,
		0x33, 0x38, 0x33, 0x35, 0x33, 0x33, 0x33, 0x36, 0x33, 0x33,
		0x33, 0x35, 0x33, 0x31, 0x33, 0x34, 0x33, 0x36, 0x33, 0x30,
		0x33, 0x30, 0x33, 0x30, 0x33, 0x31, 0x33, 0x30, 0x33, 0x31,
		0x33, 0x34, 0x33, 0x34
	};
	char * a2 = (char *)malloc(32);
	memset(a2, 0, 32);
	strcpy(a2, "dksldk");
//	sub_50EAC(a1, a2);
	printf("\n\nresult:\t %s\n\n", a2);
	return 0;
}

unsigned int sub_50E74(int a1)
{
	int v1;
	int v2; 
	int v3; 
	v2 = __ROR4__(a1, 24);
	v1 = v2;
	v3 = __ROR4__(a1, 8);
	return v1 & 0xFF00FF | v3 & 0xFF00FF00;
}

/*
int  SHA256_5C5A8(char *a1, char *a2)
{
	char * v2;
	unsigned int v3; 
	int v4; // r1@1
	int v5; // r2@1
	char v6; // cf@1
	unsigned int v7; // r3@3
	int v8; // r3@5
	int v9; // r6@5
	char * v10; // r5@5
	int v11; // r3@7
	int v12; // r2@7
	char v13; // r0@8
	int v14; // r1@9
	int v15; // r4@14
	int v16; // r3@14
	char v17; // r2@15
	int v18; // r1@16

	v2 = a2;
	v3 = *(unsigned int *)(a2 + 32);
	v4 = 8 * *a1;
	v5 = v4 + v3;
	v6 = v4 + v3 >= v4;
	*(v2 + 32) = v4 + v3;
	if (v4 + v3 < v4)
		v5 = *(v2 + 36);
	v7 = v3 >> 3;
	if (!v6)
		*(v2 + 36) = v5 + 1;
	v8 = v7 & 0x3F;
	*(v2 + 36) += *a1 >> 29;
	v9 = 64 - v8;
	v10 = a1;
	if (*a1 >= 64 - v8)
	{
		v11 = v2 + v8;
		v12 = 0;
		while (1)
		{
			v14 = v11 + v12;
			if (v12 >= v9)
				break;
			v13 = *(*(v10 + 4) + v12++);
			*(v14 + 40) = v13;
		}
		SHA256_6E1A0(v2, v2 + 40);
		while (v9 < *v10 - 63)
		{
			SHA256_6E1A0(v2, *(v10 + 4) + v9);
			v9 += 64;
		}
		v8 = 0;
	}
	else
	{
		v9 = 0;
	}
	v15 = v2 + v8;
	v16 = 0;
	while (1)
	{
		v18 = v15 + v16;
		if (v16 >= *v10 - v9)
			break;
		v17 = *(*(v10 + 4) + v9 + v16++);
		*(v18 + 40) = v17;
	}
	return 0;
}
*/

int  sub_50EAC(char *a1, char *a2){
    char* v2; 
	char* v3;
	int v4; 
	unsigned int v5;
	int v6;
	int v7; 
	unsigned int v8;
	int v9; 
	char* v10; 
	char* v12; 
	int v13; 
	char *v14;
	unsigned int v15; 
	unsigned int v16; 

	v2 = a1;
	v3 = a2;
	v12=(char *)malloc(64);
	memset(v12, 0, 0x40u);
	v4 = *(unsigned int *)(v2 + 32);
	v12[0] = -128;
	v16 = sub_50E74(v4);
	v5 = sub_50E74(*(unsigned int *)(v2 + 36));
	v6 = (*(unsigned int *)(v2 + 32) >> 3) & 0x3F;
	if (v6 > 55)
		v7 = 120 - v6;
	else
		v7 = 56 - v6;
	v13 = v7;
	v14 = v12;
	v15 = v5;
//	SHA256_5C5A8(&v13, v2);
//	v14 = &v15;
	v13 = 8;
//	SHA256_5C5A8(&v13, v2);
	*(unsigned int *)v3 = sub_50E74(*(unsigned int *)v2);
	*(unsigned int *)(v3 + 4) = sub_50E74(*(unsigned int *)(v2 + 4));
	*(unsigned int *)(v3 + 8) = sub_50E74(*(unsigned int *)(v2 + 8));
	*(unsigned int *)(v3 + 12) = sub_50E74(*(unsigned int *)(v2 + 12));
	*(unsigned int *)(v3 + 16) = sub_50E74(*(unsigned int *)(v2 + 16));
	*(unsigned int *)(v3 + 20) = sub_50E74(*(unsigned int *)(v2 + 20));
	*(unsigned int *)(v3 + 24) = sub_50E74(*(unsigned int *)(v2 + 24));
	v8 = sub_50E74(*(unsigned int *)(v2 + 28));
	v9 = 0;
	v10 = v2 + 39;
	*(v3 + 28) = v8;
	*v2 = 0;
	*(v2 + 4) = 0;
	*(v2 + 8) = 0;
	*(v2 + 12) = 0;
	*(v2 + 16) = 0;
	*(v2 + 20) = 0;
	*(v2 + 24) = 0;
	*(v2 + 28) = 0;
	*(v2 + 32) = 0;
	*(v2 + 36) = 0;
	do
	{
		++v9;
		*(v10++ + 1)=0;
	} while (v9 != 64);
	return 0;
}