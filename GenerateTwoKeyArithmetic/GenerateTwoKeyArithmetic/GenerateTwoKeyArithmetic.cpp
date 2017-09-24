// GenerateTwoKeyArithmetic.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sub_94180.h"

int _tmain(int argc, _TCHAR* argv[])
{
	/*char *inputData1Hex = "8525BA3A366BCF181A5CA1ABE8E5D338";
	char *inputData2Hex = "C10FEDBB014D008E441B40FA4F707D14";
	char *inputData3Hex = "A8238D9760F92A4A31678A30A7E434408CB7F44759DED6C3640457481F7F2D83"; */

	//char *inputData1Hex = "57D83DA48F62899A5E65A79AF288389A";
	//char *inputData2Hex = "9B58507640013E4BABEA43283C296FEC";
	//char *inputData3Hex = "226717311D8AFCE06B5254A26CD5DAF427458859F1F8B7CB440F472DC579C0E6";//"226717311D8AFCE06B5254A26CD5DAF4E2FDBF7B40C86F36885F3E2CE909060C"; 


	/*char *inputData1Hex = "94D4E851058F199FB962B5642D2979BA";
	char *inputData2Hex = "D9535F35A4587119A2562F2775A6D61F";
	char *inputData3Hex = "6BDEA49C97D9F8094CC764D3BE94B88A3B66813C1A03FEA3767D887E3C75F9FD"; 
*/

	char *inputData1Hex = "DCCF6F56EFD17144568324BB16C13FC2";
	char *inputData2Hex = "D8AF1F026A64CDA930C45AA8EA8216DE";
	char *inputData3Hex = "16400E4062F2201A1A43E8E2164A7B06253FEB0CFD437650BD7E7761AF2D8215";


	char *result = (char *)malloc(32);
	memset(result, 0, 32);
	int len = generateMiddleData_94180_fun(inputData1Hex, inputData2Hex, inputData3Hex, result);
	char *temp = stringToHexString((unsigned char *)result, len);
	printf("\n\nfun_94180_32_result:\n%s\n\n", temp);
	generateNeedKey(result);


	printf("*************************************\n\n");
	printf("test opt method:\n");
	char * initData = "0123456789ABCDEFFEDCBA9876543210F0E1D2C30002000000000000715A0706720F5B5A0257067F450405054E0E0F063636363636363636363636363636363636363636363636363636363636363636363636363636363636363636";
	char *data = hexStringToString(initData, strlen(initData));
	char *result1 = getLastKeyResult_4F1B0_opt(data, data + 28);
	printfOutResult((unsigned char *)result1, 92);
	return 0;
}

