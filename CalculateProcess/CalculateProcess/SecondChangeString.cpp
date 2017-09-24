#include "stdafx.h"
#include <sys/utime.h>
#include <Windows.h>
#include <stdlib.h>



//int _tmain(int argc, _TCHAR* argv[])
//{
//	char* getNewArray(char* str, int length);
//	char parameter[] = "aZ8RyZRWxcJno2cBcwQDAHYjmZoOC5Gi";   //key
//	getNewArray(parameter, 3);
//
//	return 0;
//}

char* getNewArray(char* str, int length){
	char temp[300];
	//printf("%d\n\n",sizeof(char));
	char * needOutput = (char *)malloc(1024 * sizeof(char));
	memset(needOutput, 0, 1024);
	memset(temp, 0, 300);
	strcat_s(temp, 300, str);
	strcat_s(temp, 300, str); 
	strcat_s(temp, 300, str);
	strcat_s(temp, 300, str);
	strcat_s(temp, 300, str);
	strcat_s(temp, 300, str);
	strcat_s(temp, 300, str);
	strcat_s(temp, 300, str);

	int i = 0,k;
	for (i = 0, k=0; i < 1024; i += 4,k++){
		needOutput[i] = k;
	}
	
	printf("\n\n第一次初始化1K空间：\n");
	for (i = 0; i < 1024; i++){
		if (i % 16 == 0 && i != 0){
			printf("\n");
		}
		if (needOutput[i] != 0){
			printf("%2x ", needOutput[i] & 0x000000FF);
		}
		else{
			printf("00 ");
		}
	}

	


	int x, y, z ,keep=0;
	for (k = 0; k < 256; k++){
		x = needOutput[k * 4];
		y = temp[k];
		z = (x + keep + y) % 256;
		keep = z;
		int t = needOutput[4 * k];
		needOutput[4*k]=needOutput[4 * z];
		needOutput[4 * z] = t;
	}

	
	printf("\n\n变化1K空间后：\n");
	for (i = 0; i < 1024; i++){
	if (i % 16 == 0 && i!=0){
	printf("\n");
	}
	if (needOutput[i] != 0){
	printf("%2x ", needOutput[i] & 0x000000FF);
	}
	else{
	printf("00 ");
	}
	}
	
	


	char input[] = "863077028536351460000640798962PB3VVCR2w8fiiCsZE50jIA==779497899514471120150826103350p0000000000002tDpNyvxuE/hYVk+jyt60/XCNRg=";
	char * output = (char *)malloc(125 * sizeof(char));
	memset(output, 0, 125);
	int v107 = 0,v71;
	int v86 = 0,v87=0,v26;
	for (k = 0; k < 125; k++){
		v71 = v86 + 1;
		x = needOutput[v71 * 4]; //v72
		v86++;
		v87 = (v87 + x) & 0x000000ff;
		v71 = v71 * 4;
		needOutput[v71] = needOutput[4 * v87];
	//	printf("%d,%d", 4 * keep, needOutput[y]);
		needOutput[4 * v87] = x & 0x000000ff;
		int www = (((x & 0x000000ff) + needOutput[v71]) & 0x000000ff) * 4;
		v107 = needOutput[www];

	//	printf("%02x ", v107);
		output[k] = (input[k] ^ v107) & 0x000000ff;  
		v26 = output[k];
		int v27 = ((v26 - 32) & 0xFFu) > 0x5E || (unsigned int)(v26 - 96) <= 0;
		int v68 = output[k] & 0x000000ff;
		if (v27 != 0){
			v68 = (v68 ^ v107) & 0x000000ff;
			output[k] = v68;
		}
	//	printf("%02x ", v68);
	}
	//for (i = 0; i < 125; i++){
	printf("\n\n最后的结果：\n%s\n\n", output);
	//}



	return needOutput;
}