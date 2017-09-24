#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "MyUtil.h"

int sub_97158_opt(char *inputData, char * result_a10);
int sub_97048_opt(char *result);
int sub_97790_opt(char *a1, int a2, char *a7);
int sub_9A360_opt(int a1, char *a2, char *a3);
int sub_98114_opt(char *v19, char *v18, char *v17, char *a4, char *result, int i);
//v19-16位长度
//a8-4K长度
//v18-16位长度
//v17-16位长度
//a10-4K长度
//a4-16长度
void sub_98114(char *v19, char  *a8, char *v18, char *v17, char *a10, char *a4, char *result, int i);

//a1=0xA;
//a2-16;
//a3-160+16;
//a4-800*4;
//a5-0xFF;
int sub_9A360(int a1, char *a2, char *a3, char *a4, char *a5);

//a1:输入串32位
//a2:0,16
//a5:4K
//a7:16
int sub_97790(char *a1, int a2, char * a5, char *a7);

//a6 - 4K,
//a10--FC --存结果 
//a1 - 16,
//a8 - 256 * A
//a9 - 0xFF
int sub_97158(char *inputData, char *a6, char *a8, char *a9, char * result_a10);

//result-0xFC
//a4-4K
int sub_97048(char *result);