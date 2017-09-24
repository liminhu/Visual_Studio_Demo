// VS_NewGenerateSMSVer0308.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "test.h"

int _tmain(int argc, _TCHAR* argv[])
{
	char *initHex = "40000000000000000123456789ABCDEFFEDCBA9876543210";
	char *init = hexStringToString(initHex, strlen(initHex));

	char *result = (char *)malloc(32);
	memset(result, 0, 32);

	strcat(result, init);

	char *inputDataHex = "34353031303035333435346433313336343739303166303461353132333035388000000000000000000000000000000000000000000000000001000000000000";
	char*data = hexStringToString(inputDataHex, strlen(inputDataHex));
	Cid_md5_2B128(result, data);
	return 0;
}

