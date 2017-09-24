#include "stdafx.h"
#include <sys/utime.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "md5.h"
#include <string.h>






int  getMD5Result(char * str, char *temp){
	md5_state_t s;
	md5_init(&s);
	md5_append(&s, (const unsigned char *)str, strlen(str));
	unsigned char result[17] = { 0 };
	char result_rev[32] = { 0 };
	md5_finish(&s, (unsigned char *)result);
	memset(temp, 0, 300);
	char*  st = temp;
	int i = 0;
	for (i = 0; i<16; i++, st += 2)
	{
		sprintf(st, "%02x", result[i]);
	}
	return 1;
}





char * generate_uri_token(char * a1, char * a2){
	char dest_rand[5];
	char nptr[2];
	char temp[300];
	char table[] = "93f518ea06c42b7d";
	time_t timer;
	struct tm *tblock;
	timer = time(NULL);
	srand((unsigned int)time);       //srand48和drand48是Unix库函数，drand48的作用是产生[0,1]之间均匀分布的随机数，采用了线性同余法和48位整数运算来产生伪随机序列
	int random = rand() % 0xFFFF;
//	printf("%d\n", random);
	sprintf_s(dest_rand, "%04x", random);
	sprintf(dest_rand, "%c%c%c%c", table[random >> 12 & 0xf], table[random >> 8 & 0xf], table[random >> 4 & 0xf], table[random & 0xf]);
	//printf("%s\n", dest_rand);

	//memset(temp, 0, 300);
	//for (int i = 0; i < strlen(dest_rand); i++){
	//	char  ch = dest[i];
	//	nptr[0] = ch;
	////	LOBYTE(nptr[0]) = ch;
	//	int n = strtol((const char *)nptr, 0, 16);
	////	printf("%d\n", n);
	//	temp[i] = str[n];
	//}
	//printf("%s", temp);

	char tt[8];
	char test[300] = "bdd3";
	strcpy(tt, "4bb5");
	strcat_s(test, a1); 
	strcpy_s(temp, test);
	printf("%s\n", temp);
	getMD5Result(test,temp);
	_strrev(temp);
	getMD5Result(temp,test);
	strcat(test, a2);
	getMD5Result(test, temp);
	printf("\n\n%s", temp);
	char* out = (char *)malloc(13 * sizeof(char));
	memset(out, 0, 13);
	sprintf(out, "%c%c%.3s%c%.2s%c%.2s%c%.4s", temp[0], tt[0], &temp[1], tt[1], &temp[4], tt[2], &temp[6], tt[3], &temp[8]);
	printf("\n%s\n\n", out);
	return out;
}


/*
int _tmain(int argc, _TCHAR* argv[])
{   
	char a1[] = "00c422a8d19627e941b5fb43fd6b80c0a132a884faecc0f233b7aa5117bdf6b7";
	char a2[] = "mgjandroid722MAM360866499020343445911322e3-5c96-4d87-9765-e960b8337efaMAM3607224.4.21b2628cb31a4a4e0fe1f19afdedc7b91d11972014430120237.2.2.1509150022014501";
	generate_uri_token(a1, a2); //24f03b22bdd5ae7b
	return 0;
}
*/