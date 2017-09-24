#include "stdafx.h"
#include <sys/utime.h>
#include <Windows.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct ElementData {
	char* a0;
	char* a1;
	char* a2;
	int a3;
	int a4;
	int a5;
	char* a6;
	char* a7;
} ElementData;

char * sub_F128(ElementData inputData);


int _tmain1(int argc, _TCHAR* argv[]){
	printf("\nHello world!!! \n\n");
	                 //  020KqU2fE6IuO0aHjI8A589w0000Ajrkf5A1AchvY00000000000000003wUVhvRPs@@000000000OqcP8RNnzgni001vmK15001b8eh2zI4Ns2NxfC3TS7b18FdNZb2xJ7oyS8 = 7
	//char* a0 = "00000000863077028536351460001014143573PB3VVCR2w8fiiCsZE50jIA==120086168313359520151110052703p000700010001000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	//char* a2 = "aZ8RyZRWxcJno2cBcwQDAHYjmZoOC5Gi";
	char* a0 = "020KqU2fE6IuO0aHjI8A589w0000Ajrkf5A1AchvY00000000000000003wUVhvRPs@@000000000OqcP8RNnzgni001vmK15001b8eh2zI4Ns2NxfC3TS7b18FdNZb2xJ7oyS8=7";
	char* a2 = "xcJno2cBcwQDoOC5GiAHYjmZaZ8RyZRW";
	//char* a7 = "3c3f786d6c2076657273696f6e3d27312e302720656e636f64696e673d275554462d3827207374616e64616c6f6e653d2779657327203f3e3c6368617267655f726571756573743e3c73646b76657273696f6e3e31323030313030303c2f73646b76657273696f6e3e3c747970653e353c2f747970653e3c72657175657374747970653e313c2f72657175657374747970653e3c637069643e3639393031383c2f637069643e3c6369643e31303135343836303c2f6369643e3c636869643e3330323330303234303030303030303c2f636869643e3c696d73693e3436303030313031343134333537333c2f696d73693e3c696d65693e3836333037373032383533363335313c2f696d65693e3c73646b73657373696f6e69643e6b4e655837784b534a686957366962313c2f73646b73657373696f6e69643e3c61706b7374617475733e703c2f61706b7374617475733e3c7265717565737454696d653e323031352d31312d31322031373a34303a32383c2f7265717565737454696d653e3c6370706172616d3e3c2f6370706172616d3e3c2f6368617267655f726571756573743e30303030303030303836333037373032383533363335313436303030313031343134333537335042335656435232773866696943735a4535306a49413d3d343634333834373238363433313034383230313531313132303934303238703030303130303030303030313030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030304c4843444c4747634239316854726f31633559376b4c65444e706f3d";
	//char* a7 = "3c3f786d6c2076657273696f6e3d27312e302720656e636f64696e673d275554462d3827207374616e64616c6f6e653d2779657327203f3e3c6368617267655f726571756573743e3c73646b76657273696f6e3e31323030313030303c2f73646b76657273696f6e3e3c747970653e353c2f747970653e3c72657175657374747970653e313c2f72657175657374747970653e3c637069643e3639393031383c2f637069643e3c6369643e31303135343836303c2f6369643e3c636869643e3330323330303234303030303030303c2f636869643e3c696d73693e3436303030313031343134333537333c2f696d73693e3c696d65693e3836333037373032383533363335313c2f696d65693e3c73646b73657373696f6e69643e3547455272524f3630586c596d3431743c2f73646b73657373696f6e69643e3c61706b7374617475733e703c2f61706b7374617475733e3c7265717565737454696d653e323031352d31312d31302031333a32373a30333c2f7265717565737454696d653e3c6370706172616d3e3c2f6370706172616d3e3c2f6368617267655f726571756573743e30303030303030303836333037373032383533363335313436303030313031343134333537335042335656435232773866696943735a4535306a49413d3d313230303836313638333133333539353230313531313130303532373033703030303730303031303030313030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030306b376b322f51656747795a4d71795335674c5978785a35554c68633d";
	char* result = (char*)malloc(2096);
	ElementData input;
	input.a0 = a0;
	input.a1 = result;
	input.a2 = "0753554956420868";
	input.a3 = 0x20;
	input.a4 = 112;
	input.a5 = 0x13E;
	input.a6 = result;

	char a[] = { 0x27, 0xb7, 0x0c, 0x56, 0x2c, 0x28, 0xbb, 0x5e, 0x8c, 0x59, 0xfc, 0x30, 0x49, 0x63, 0xcc, 0x09, 0x86, 0x9d, 0xed, 0x97, 0x38, 0x1c, 0xaf, 0x8d, 0xc8, 0x69, 0xed, 0x66, 0x33, 0xa7, 0x94, 0x31, 0x2b, 0xdb, 0x31, 0x30, 0x98, 0xe2, 0x70, 0x62, 0x7d, 0x8c, 0x2f, 0x85, 0xcb, 0x6b, 0xb2, 0xf5, 0xcc, 0xcb, 0xe4, 0xe6, 0x48, 0x2d, 0xcd, 0x42, 0x52, 0x7e, 0xb0, 0x51, 0xaf, 0x45, 0x4e, 0xe0, 0x4d, 0x4d, 0x87, 0x63, 0x17, 0xc4, 0x02, 0xa1, 0x33, 0xe2, 0x1c, 0xce, 0x4f, 0x0d, 0x8f, 0x34, 0xc8, 0x0c, 0xfe, 0x38, 0xb0, 0x6e, 0xb9, 0xf8, 0x5a, 0x08, 0x53, 0x1a, 0x9c, 0xa6, 0xe0, 0xb7, 0x30, 0xb4, 0xd8, 0xc8, 0x67, 0x1e, 0x62, 0x83, 0xd9, 0x81, 0x55, 0xc0, 0xed, 0xfb, 0xd2, 0xf4 };
	input.a7 = a;
	sub_F128(input);
	return 0;
}

char * sub_F128(ElementData inputData)
{
	char* tableData = (char *)malloc(0x100 * sizeof(char));
	for (int i = 0; i < 0x100; i++){
		tableData[i] = i & 0xFF;
	}

	printf("\n\n第一次初始化0xFF空间：\n");
	for (int i = 0; i < 0x100; i++){
		if (i % 16 == 0 && i != 0){
			printf("\n");
		}
		if (tableData[i] != 0){
			printf("%02x ", tableData[i] & 0xFF);
		}
		else{
			printf("00 ");
		}
	}
	char input_value, table_value, change_value;
	int  temp = 0;
	for (int i = 0; i < 0x100; i++)
	{
		temp = (temp + tableData[i]) & 0xFF;
		table_value = tableData[i];
		input_value = *(inputData.a2 + (i % strlen(inputData.a2)));
		temp = (input_value + temp) & 0xFF;
		change_value = tableData[temp];
		tableData[i] = change_value;
		tableData[temp] = table_value;
		tableData[i] = ((int)(change_value & 0xFF) + 0x69) % 0xFF; 
	}
	printf("\n\n初始化表后结果为：\n\n");
	for (int i = 0; i < 0x100; i++){
		if (i % 16 == 0 && i != 0){
			printf("\n");
		}
		if (tableData[i] != 0){
			printf("%02x ", tableData[i] & 0xFF);
		}
		else{
			printf("00 ");
		}
	}
	printf("\n\n");
	temp = 0;
	int var_238 = 0 , var_234=0;
	for (int i = 0; i < inputData.a4; i++)
	{
		var_238 = (var_238 + 1) & 0xFF;
		table_value = tableData[var_238];
		var_234 = (var_234 + table_value) & 0xFF;
		change_value = tableData[var_234];
		tableData[var_238] = change_value;
		tableData[var_234] = table_value;
		temp = (change_value + table_value) & 0xFF;
		*(inputData.a1 + i) = tableData[temp] ^ (*(inputData.a7 + i) );
	}
	printf("\n\n最终的结果为：%.*s\n\n", inputData.a4, inputData.a1);
	for (int i = 0; i < inputData.a4; i++)
	{
		
		if (i % 16 == 0 && i != 0){
			printf("\n");
		}
		printf("%02x ", *(inputData.a1 + i) & 0xFF);
	}
	printf("\n\n");
	return NULL;
}