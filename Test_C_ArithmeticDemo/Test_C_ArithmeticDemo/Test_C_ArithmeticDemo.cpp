// Test_C_ArithmeticDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TestArithmetic.h"
#include "MyUtil.h"




int _tmain(int argc, _TCHAR* argv[])
{

	char a = 2u;
	int b = 1;
	scanf("%c", &a);
	scanf("%d", &b);
	if (b <= (3 - b))
    	printf("%c", a);
	else
		printf("%d", b);
	system("pause");
	return 0;
	//test_gen_sub_5F020_key12();
	//test_key();
	//unstring();
	//return 0;
}

