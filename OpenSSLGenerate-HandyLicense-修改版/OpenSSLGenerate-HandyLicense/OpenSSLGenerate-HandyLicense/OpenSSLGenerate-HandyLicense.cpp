// OpenSSLGenerate-HandyLicense.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
//#include "ToolUtil.h"
#include "testDemo.h"
 #include <sys/types.h>    
 #include <sys/stat.h>    
 #include <fcntl.h>

void printUsage(char* exeName){
	printf("usage:\n");
	printf("%s [fileName]\n", exeName);
	printf("default input FILE is ./init_data.txt[for encrypt]  and ./handy.license[for decrypt]\n");
	printf("output DIR is ./handyLicens\n");
}



int main(int argc, char **argv) {


	test3_decrypt_text();


/*	char *initDataFileName = "Handy_licStr_android.txt";
	char *licenFileName = "handy.license";
	char * decyptlicenFileName = "handy.license.decrypt";//+imei_randnum
	//printf("\n\n%s", argv[0]);
	EVP_PKEY *pri_key = generate_private_key();
	//char * pubkey_str=pub_key->pkey.ptr;
	char *pri_key1 = pri_key->pkey.ptr;
//	printfOutResult((unsigned char *)pubkey_str, pub_key->pkey.);
//	printfOutResult((unsigned char *)pri_key1, 100);
	char *pub_key_str = "30819F300D06092A864886F70D010101050003818D0030818902818100B30306B7D75FD1A57FF9EB6ABE8EABDBC8E2E898CDF6659D84361B72C5ACF35B7C4DE422C5D3BBEDC9BFAF14AEA7616EFB42706A231318504A5E95CA47D424AB60D237EF3A1B905F373A984038D0281EAE607BB13A4E4D7E98659A2DB61D3BDA8CBED55FD97BEF3BBBB6B1FD51C0A038987B64FD6B6966E1DC571F16AAF9A0AF0203010001";
	//char *pri_key_str = "30820277020100300D06092A864886F70D0101010500048202613082025D02010002818100B30306B7D75FD1A57FF9EB6ABE8EABDBC8E2E898CDF6659D84361B72C5ACF35B7C4DE422C5D3BBEDC9BFAF14AEA7616EFB42706A231318504A5E95CA47D424AB60D237EF3A1B905F373A984038D0281EAE607BB13A4E4D7E98659A2DB61D3BDA8CBED55FD97BEF3BBBB6B1FD51C0A038987B64FD6B6966E1DC571F16AAF9A0AF020301000102818022B56C810AC66E5CBB8296ADBCC2E6F9976ABF949922B4332566644E0D9BEA178BF3824F67B2151716EE0EA160F7DD416A8048519BF960D67884FC601B2B3BEC97AADA5C1FB548D6A4271E92EFBD9590A2BB62A3E255B7894C0197A28CD0125B13A965677EA774D58313FCA400DD0976F31A51ACDD46FD4D663CEFB586C4BA79024100DD4DC63481C0FBC76119C0AA705A4E8F1B78B4F147A161B136FB3DFE3F420988FE70FDB487DD3F5DC369ECC09179AF0BAD5A2E86F583A3D815C5176524E7C893024100CF13D351A2A0B817AF7E0B75FC58D011452E23E18D77D68704B966CCB7C685E1FC21F132662B8F8D8C1FBA947FA067D1577DDED282A209C8D017C86CAC8624F5024100AFA3C0817FD1D8827F505F1766A065E5329A7491629674E09F907BBD441B7751E10F706C4DC08D402F8DEC3751BE4FED66A242771E78621B67FBCAFB9D74D03D02406C9E3191F883E50C47790DF9ED4B8898067995489233F1CB10A74F4CC278D7711A1793B4A3F2E57191B672DFC1B219C2ACE9D11F0A76843B592BA06DA0711CA1024100A21287B9A29EFE48EF4187A20E3C62FD09A3A3FBAC348B39917B42BAF52FCDDE7B18E3C59CE855E3711CC9819B09D38DA5EC2F741CBE6FFEED4F0C3A21051F12";
	int pub_key_len = strlen(pub_key_str);
	//int pri_key_len = strlen(pri_key_str);
	char * pubKey=hexStringToString(pub_key_str, pub_key_len);
	//char *priKey = hexStringToString(pri_key_str, pri_key_len);
	EVP_PKEY *pub_key = getEvpPublicKeyByCharArray((unsigned char *)pubKey, pub_key_len / 2);
//	EVP_PKEY *pri_key = getEvpPrivateKeyByCharArray((unsigned char *)priKey, pri_key_len / 2);
	FILE *fp = NULL;
	if (argc == 1)
	{
		fp = fopen(initDataFileName, "r");
		if (fp == NULL){
			printf("\n文件\t%s\t不存在！", initDataFileName);
		}
		else{
			fclose(fp);
			//generateLicenseReadDataFromFile(initDataFileName, pri_key);
		}
		
		fp = fopen(licenFileName, "r");
		if (fp == NULL){
			printf("\n文件\t%s\t不存在！", licenFileName);
		}else{
			fclose(fp);
			signatureVerifyLicense(pub_key, licenFileName);
		}
	}
	else if (argc == 2)
	{
		FILE *fp = fopen(argv[1], "r");
		if (fp== NULL){
			printf("\n file %s open error!", argv[1]);
			exit(0);
		}
		else{
			printf("\n file %s open true !", argv[1]);
		}
		char * fileFirstLine = (char*)malloc(30);
		fread(fileFirstLine,1,30,fp);
		fclose(fp);
		if (strncmp(fileFirstLine,"Nemo Handy-A",12)==0){
			generateLicenseReadDataFromFile(argv[1], pri_key);
		}
		else if (strncmp(fileFirstLine, "xxxxxxxxxxxxxxxx3,6EC54A61#1,", 29) == 0){
			signatureVerifyLicense(pub_key, argv[1]);
		}else{
			printUsage(argv[0]);
		}
		
	}
	else{
		printUsage(argv[0]);
	}
	EVP_PKEY_free(pri_key);
	EVP_PKEY_free(pub_key);
	printf("\n\n");
	return 0;*/
}


/*

int fileIsExist(char * fileName){
if (!_access(fileName, 0)){
printf("\n文件%s已存在！", fileName);
return 0;
}
return 1;
}


int main(int argc, char **argv) {
char *initDataFileName = "./init_data.txt";
//char *imei = "359471060237567";
//test_digest();
//test1_rsa_key();
//test2_generate_license();
//test3_decrypt_text();
//test4_sign("");
//test5_encrypt();
//test6_userMyPublicKey();
//test7_getDataFromFile();
// test8_integrateTotal();
//test9_update1(initDataFileName,imei);
//test9_update2(initDataFileName, imei);
test10_update3(initDataFileName);
return 0;
}

*/