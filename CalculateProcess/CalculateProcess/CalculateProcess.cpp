// CalculateProcess.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <sys/utime.h>
#include <Windows.h>
#include <stdlib.h>
#include "MyUtil.h"
#include "sub_94180.h"



int _tmain(int argc, _TCHAR* argv[])
{
	char *inputData1Hex = "57D83DA48F62899A5E65A79AF288389A";
	char *inputData3Hex = "9B58507640013E4BABEA43283C296FEC";
	char *inputData2Hex = "226717311D8AFCE06B5254A26CD5DAF4E2FDBF7B40C86F36885F3E2CE909060C";

	char *result = (char *)malloc(0xFC);
	memset(result, 0, 0xFC);
	char *inputData = hexStringToString(inputData1Hex, 32);
	int len=sub_97158_opt(inputData, result);
	char *temp = stringToHexString((unsigned char *)result, len);
//	printf("\n\ntemp1:\n%s\n\n", temp);
	////free(temp);
	sub_97048_opt(result);
	char *temp1 = stringToHexString((unsigned char *)result, len);
//	printf("\n\ntemp2:\n%s\n\n", temp1);
	
	
	char *result_16 = (char *)malloc(17);
	memset(result_16, 0, 17);
	char *result_last = (char *)malloc(33);
	memset(result_last, 0, 33);
	char *middle = result_last;


	char *result_temp= (char *)malloc(17);
	memset(result_temp, 0, 17);
  
   char *keep = (char *)malloc(17);
   memset(keep, 0, 17);
	for (int i = 0; i < 32; i=i +16){
		sub_97790_opt(inputData2Hex, i,  result_16);
		char *temp3 = stringToHexString((unsigned char *)result_16, 16);
		//printf("\n\ntemp3:\n%s\n\n", temp3);
		memcpy(result_temp, result_16, 16);
		if (i == 0){
			memcpy(keep, result_16, 16);
		}
		sub_9A360_opt(10, result_temp, result); //a2存结果
		char *temp4 = stringToHexString((unsigned char *)result_temp, 16);
		//printf("\n\ntemp4:\n%s\n\n", temp4);
		sub_98114_opt(inputData3Hex,  result_temp, keep, result, middle, i);
		char *temp5 = stringToHexString((unsigned char *)result_last, 32);
		printf("\n\ntemp5:\n%s\n\n", temp5);
		middle = middle+16;
	}
	return 0;
}

