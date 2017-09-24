#include "stdafx.h"
#include "testDemo.h"


int getKeyValue(char * input, byte value, int i){
	char  num[10];
	memset(num, 0, 10);
	if (i % 2 != 0){
		num[0] = value;
		strcat(input, num);
	}
	else{
		int high = value / 10;
		int low = value % 10;
		_itoa(high, num, 10);
		if (high > 0)
			strcat(input, num);
		_itoa(low, num, 10);
		strcat(input, num);
	}
	return 0;
}
int * generateKey(char * imei, char * aaa, char* getKey){
	int i = 0;
	for (i = 0; i < strlen(imei); i++){
		if (i % 2 == 0){
			getKeyValue(getKey, (byte)(imei[i] ^ aaa[i]), i);
		}
		else{
			if (i % 3 == 0){
				getKeyValue(getKey, imei[i], i);
			}
			else{
				getKeyValue(getKey, aaa[i], i);
			}
		}
	}
	return 0;
}
char *getSignHexStrByPlainText(char * plainText, int need_signStr_len){
	char *signStrArray = (plainText + need_signStr_len);
	char *signArray = strtok(signStrArray, ",");
	char *sign = strtok(NULL, "#");
	return sign;
}
char *extractionImei(char * inputData){
    strtok(inputData, "#");
	char *secondStr = strtok(NULL, "#");
	strtok(secondStr, ",");
	return strtok(NULL, "#");
}
char *extractionImeiMethodTow(char *inputData){
	char *imeiStr = strstr(inputData, "#1,");
	char *imei = NULL;
	if (imeiStr != NULL){
		imei = strtok(imeiStr + 3, "#");
	}
	return imei;
}
int *generateLicense(char* initData, char *aaa, char *imei, EVP_PKEY *evpKey, char*licenseName){
	printf("\n\n---\t私钥签名过程\t---");
	char * content = initData;
	printf("\n签名原串%d：%s", strlen(initData),content);
	int sign_len = 0;
	unsigned char * signStr = signature((unsigned char *)initData, strlen(initData), sign_len, evpKey);
	printf("\n\nsign_value:\n\n");
	printfOutResult(signStr, sign_len);
	printf("\n签名串base64结果：\n%s\n\n", base64_encode((char *)signStr, sign_len));
	int last_needDataLen = strlen(initData) + sign_len * 2 + 30;
	char *last_needData = (char *)malloc(last_needDataLen);
	memset(last_needData, 0, last_needDataLen);
	strcpy(last_needData, initData);
	strcat(last_needData, "7,");
	char* sign_value_hex = stringToHexString(signStr, sign_len);
	//printf("\n%d\n%s", strlen(sign_value_hex), sign_value_hex);
	strcat(last_needData, sign_value_hex);
	strcat(last_needData, "#");
	char* key = (char *)malloc(GEN_KEY_LEN);
	memset(key, 0, GEN_KEY_LEN);
	generateKey(imei, aaa, key);
	key[16] = '\0';
	char *iv = key;
	char space[] = { 0x04, 0x04, 0x04, 0x04, '\0' };
	char * ciphertext = NULL;
	int ciphertext_len = 0;
	strcat(last_needData, space);
	printf("\n%s\n", last_needData);
	unsigned char * r = encrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)last_needData, ciphertext_len, (unsigned char *)ciphertext);
	char * handy_license = base64_encode((char *)r, ciphertext_len);
	int replace_len = strlen(handy_license);
	char *replaceBlank_handy_license = replaceBlank(handy_license, replace_len);
	printf("\n生成密文如下:\n%s\n\n", replaceBlank_handy_license);
	char * fileName = licenseName;
	char * newLineStr = "\r\n";
	char * handy = "Nemo Handy-A";
	char * plaintext = replaceBlank_handy_license;
	char *sb = (char *)malloc(2048);
	memset(sb, 0, 2048);
	strcat(sb, handy);
	strcat(sb, newLineStr);
	strcat(sb, "imei:");
	strcat(sb, imei);
	strcat(sb, newLineStr);
	strcat(sb, aaa);
	strcat(sb, newLineStr);
	strcat(sb, plaintext);
	printf("生成证书文件如下:\n\n%s\n\n", sb);
	wirteDataToFile(fileName, sb);
	free(sb);
	free(last_needData);

	return 0;
}
int signatureVerifyLicense(EVP_PKEY *evpKey, char*licenseName){
	char *fileData = readDataFromFileByLine(licenseName);
	int len = strlen(fileData);
	fileData = replaceBlank(fileData, len);
	char *nemoHandy = strtok(fileData, ";");
	char *imeiStr = strtok(NULL, ";");
	char *aaa = strtok(NULL, ";");
	char *initData = strtok(NULL, ";");
	char *imei_before = strtok(imeiStr, ":");
	char *imei = strtok(NULL, ";");
	char* key = (char *)malloc(GEN_KEY_LEN);
	memset(key, 0, GEN_KEY_LEN);
	generateKey(imei, aaa, key);
	key[16] = '\0';
	char *iv = key;
	unsigned char *testData = NULL;
	int  initData_len = 0;
	testData = (unsigned char *)base64_decode((const char *)initData, strlen(initData), initData_len);
	printfOutResult(testData, initData_len);
	unsigned char * final = NULL;
	int ciphertext_len = 0;  //ciphertext: 密文  plaintext,明文
	unsigned char plaintext[MAX_CHAR_SIZE];
	memset(plaintext, 0, MAX_CHAR_SIZE);
	int plain_len = 0;
	final = decrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)testData, &initData_len, plaintext, plain_len);
	//printf("%s\n[%d]\n\n", final, strlen((char *)final));
	//printfOutResult(final, plain_len);
	printf("\n\n原始串：%s\n\n原始串长度: %d", final, plain_len);
	int need_signStrLen = 0x129;
	char *need_sign_data = (char *)malloc(need_signStrLen + 1);
	strncpy(need_sign_data, (char *)final, need_signStrLen);
	need_sign_data[need_signStrLen] = '\0';
	printf("\n\n签名串：%s\n\n签名串长度: %d", need_sign_data, need_signStrLen);
	char *signHexStr = getSignHexStrByPlainText((char *)final, need_signStrLen);
	int sign_value_len = strlen(signHexStr) / 2;
	printf("\n检验值的hex-结果：len=%d\n", sign_value_len);
	unsigned char * sign_value = (unsigned char *)hexStringToString(signHexStr, strlen(signHexStr));
	printfOutResult(sign_value, strlen(signHexStr) / 2);
	printf("\n\n_____________________________________________________");
	printf("\n\n---\t公钥校验过程\t---\n");
	signatureVerify((unsigned char *)need_sign_data, need_signStrLen, sign_value, sign_value_len, evpKey);
	printf("\n\n");
	return 0;
}
int getInitFileDataLines(char * initData){
	int lineNumber = 0;
	char *firstLine = strtok(initData, ";");
	while (firstLine != NULL){
		lineNumber++;
		free(firstLine);
		firstLine= strtok(NULL, ";");
	}
	return lineNumber;
}
int 	newGenLicenseAndSignature(char *newInitData, char *input_imei, EVP_PKEY *pub_key, EVP_PKEY *pri_key){
	char *initData = (char *)malloc(strlen(newInitData) + 1);
	memset(initData, 0, strlen(newInitData) + 1);
	strcpy(initData, newInitData);
	printf("initData-%d:\n\n%s\n\n", initData);
	char *imei = extractionImeiMethodTow(initData);
	printf("\n\nimei:\n%s\n\n", imei);
	char *aaa = generateRandomNum(16);
	printf("\n\n随机数：%s\n\n", aaa);
	if (!strcmp(input_imei, imei)){
		char *licenName = (char *)malloc(50);
		memset(licenName, 0, 50);
		strcpy(licenName, "./handyLicense/handyLicense-");
		strcat(licenName, imei);
		generateLicense(newInitData, aaa, imei, pri_key, licenName);
		signatureVerifyLicense(pub_key, licenName);
		free(licenName);
	}
	free(initData);
	return 0;
}


int 	newGenLicenseAndSignatureUpdate(char *newInitData, EVP_PKEY *pub_key, EVP_PKEY *pri_key){
	char *initData = (char *)malloc(strlen(newInitData) + 1);
	memset(initData, 0, strlen(newInitData) + 1);
	strcpy(initData, newInitData);
	printf("\ninitData:%s\n\n", initData);
	char *imei = extractionImeiMethodTow(initData);
	printf("\n\nimei:\n%s\n\n", imei);
	char *aaa = generateRandomNum(16);
	printf("\n\n随机数：%s\n\n", aaa);
	char *licenName = (char *)malloc(128);
	memset(licenName, 0, 128);
	strcpy(licenName, "./handyLicense/handyLicense-");
	strcat(licenName, imei);
	strcat(licenName, "-");
	strcat(licenName, aaa);
	generateLicense(newInitData, aaa, imei, pri_key, licenName);
	signatureVerifyLicense(pub_key, licenName);
	free(licenName);
	free(initData);
	free(aaa);
	return 0;
}

int  genLicenseAndSignature(char *newInitData, char *licenName, int i, char *input_imei){
	printf("\n\ndjaksfkda");
	char *name = (char *)malloc(strlen(licenName) + 1);
	strcpy(name, licenName);
	char *initData = (char *)malloc(strlen(newInitData) + 1);
	memset(initData, 0, strlen(newInitData) + 1);
	strcpy(initData, newInitData);
	printf("initData-%d:\n\n%s\n\n", i + 1, initData);
	//char *imei = extractionImei(initData);
	char *imei = extractionImeiMethodTow(initData);
	printf("\n\nimei:\n%s\n\n", imei);
	char *aaa = generateRandomNum(16);
	printf("\n\n随机数：%s\n\n", aaa);
	//strcat(licenName, imei);
	//generateLicense(newInitData, aaa, imei, pri_key, strcat(licenName, inputImei));
	//if (!strcmp(input_imei, imei)){
	 //  	generateLicense(newInitData, aaa, imei, pri_key, strcat(licenName, imei));
		//signatureVerifyLicense(pub_key, licenName);

	return 0;
}

int test1_rsa_key()
{
		char origin_text[] = "hello world!";
		char enc_text[512] = "begin_enc_text";
		char dec_text[512] = "begin_dec_text";
		size_t enc_len = 512;
		size_t dec_len = 512;
		//生成公钥和私钥文件  
	//	generate_key_files(PUBLIC_KEY_FILE, PRIVATE_KEY_FILE, (const unsigned char *)RSA_PRIKEY_PSW, strlen((char *)RSA_PRIKEY_PSW));
		EVP_PKEY *pub_key = open_public_key(PUBLIC_KEY_FILE);
		EVP_PKEY *pri_key = open_private_key(PRIVATE_KEY_FILE, (const unsigned char *)RSA_PRIKEY_PSW);
		printf("\n");
		rsa_key_encrypt(pub_key, (const unsigned char *)&origin_text, sizeof(origin_text), (unsigned char *)enc_text, enc_len);
		printf("\n密文为 enc_tex: %s\n", enc_text);
		printfOutResult((unsigned char *)enc_text, enc_len);
		rsa_key_decrypt(pri_key, (const unsigned char *)enc_text, enc_len,
			(unsigned char *)dec_text, dec_len);
		printf("\n\n原文dec_tex: %s\n", dec_text);
		return 0;
}
int test2_generate_license()
{
	char * fileName = "handy.license";
	char * newLineStr = "\r\n";
	char * handy = "Nemo Handy-A";
	char * plaintext = "ULcsJxzForUPnESIx2sm5tOxC5J5ZmhBpQGl53+jB4eRo70Ddk04FwZ0g/aFF9QZFY/rD+7QUe5MK6cWZYA9IhiUaP6gpvONgAJjGWpuIH0dkiNw/fvI2AoaFYUFaG5iZ3tGBsm+/T4lWPKGHp/BYY2rVgSkRfYyRlFvjtdkHNYAX5kkLb2nO5STKjcih9vsX91RmRq6trAMfu2WJk3+ICdpM2rRdXCkidAtFav4awAHKy7actZ9uW4sOczcNi6l+QUKX1Zz4hHjSkbj9Uf6CWUJciLU+6OV8OaqqySU1oMDA8nj6u82G6F/KEVgsYQk9Wl84wjDPuJ8x/ltPikljXQSaHqoXDgV8rrMP3JXqCpJQSl2e22YVesp9uhYsI+2Wq61VAEf7yPUvIIktEba0fzb3c7Ck3IZywiCFFFetba4VXfCJCktCQXwsBYKr+vA5UrEMj8CDm8xcgxrD4v1bnQj6WMmN6Tir8JtWd73fVraIqexPnbmj4XPSgllXvzkN7UOHvUKXEn5q3nZa0DfcXXflBHYICXHs079PLXaU2YOOHQgE2NqJ4o28IDOoWnsgAIZ9J1800rPj6rcOTb0tO9C4Z73M4CeOo0BSmGswYagrRR+ufQNusWt6z2j/2mTI3Qg2BKZxXnenVfbItVNzTWUmQFmDLEnpPm93vH6WWcg6J/JqBT/sit4pq4f7sNpEvSJfzDz77wigs6KGRgc5v41mgdDZxFkF8Tw3guF9NE=";
	char * imei = "359471060237567";    //"356845051207403"; //
    char *aaa = "8781470884165120"; // "7362135407032643";
	char *sb = (char *)malloc(2048);
	memset(sb, 0, 2048);
	strcat(sb, handy);
	strcat(sb, newLineStr);
	strcat(sb, "imei:");
	strcat(sb,  imei);
	strcat(sb, newLineStr);
	strcat(sb, aaa);
	strcat(sb, newLineStr);
	strcat(sb, plaintext);
     printf("生成证书文件如下:\n\n%s\n" ,sb);
	// wirteDataToFile(fileName, sb);
	 char* key = (char *)malloc(GEN_KEY_LEN);
	 memset(key, 0, GEN_KEY_LEN);
	 generateKey(imei, aaa, key);
	 key[16] = '\0';
	 printf("生成key: %s\n", key);
	// FileReadAndWriteUtil.writeDataToFile(fileName, sb.toString());
	return 0;
}
int test3_decrypt_text(){
	char * ciphertext = "KAYWv/kMxrk5Be6X9dKqP7afPxU7gjWnz8EJBmeQ2hIlauVLzOafWwRKkIX54SN9lLAu4J+Spt76fW+pvHGTKDT2fstlOPoZIV0y5XPzeipWkUehAncuaZYWox80uOJc4R6y7XO+MNrOyAQaJWM+lcrB86IXJd2pYF+g/xirkPH0nIo/ebn/qvO6+DS/4abPqCyBnHJ5vhF/OpifYwgwKcz9TiGsq4ERzaCzpU0B9K1B4+LS5yhTUSYBuAamai9IliGxNFnWKfDs/0QmHLI6vofc/YfIgDKfvCoOHQGgCNpCVgxcLIB+tx1oOS+m/3ui71Piwd3xSP8puOf+j2MQ96uEhJ3FEv8TbrYMuRYXNv1V+yYpSO16/cdVNv6eYv1jaaOq1bDDfxSEbFSX7QHiAviSZIBTgMpA4k3GoK6fduPUrJLXwjG5qk/8XFtTB4lVVhm4+1h3EWoHVDVpxpEEFEh3U/igQ/jpjuyPlN5AyKkRR7AX4BRHisCK/srt6o4R37NnnkKmLjLq6GTJC9bMDTSI9REaurF0DIXN3rrBO1oKf89YHB0UafIFMM++lzb6iPYkBb0x/Wb/BWZr2i5f85lRjTrNFcuFPRH////////////////////9////f/////9///////f//f/f3/3///////////////7///////+///8=";// GorgeousSeparateLineGUIMAOBATCHNO = 2016003GUIMAOGIUMIEDI = 355905073519317";
		//"ULcsJxzForUPnESIx2sm5tOxC5J5ZmhBpQGl53+jB4eRo70Ddk04FwZ0g/aFF9QZFY/rD+7QUe5MK6cWZYA9IhiUaP6gpvONgAJjGWpuIH0dkiNw/fvI2AoaFYUFaG5iZ3tGBsm+/T4lWPKGHp/BYY2rVgSkRfYyRlFvjtdkHNYAX5kkLb2nO5STKjcih9vsX91RmRq6trAMfu2WJk3+ICdpM2rRdXCkidAtFav4awAHKy7actZ9uW4sOczcNi6l+QUKX1Zz4hHjSkbj9Uf6CWUJciLU+6OV8OaqqySU1oMDA8nj6u82G6F/KEVgsYQk9Wl84wjDPuJ8x/ltPikljXQSaHqoXDgV8rrMP3JXqCpJQSl2e22YVesp9uhYsI+2Wq61VAEf7yPUvIIktEba0fzb3c7Ck3IZywiCFFFetba4VXfCJCktCQXwsBYKr+vA5UrEMj8CDm8xcgxrD4v1bnQj6WMmN6Tir8JtWd73fVraIqexPnbmj4XPSgllXvzkN7UOHvUKXEn5q3nZa0DfcXXflBHYICXHs079PLXaU2YOOHQgE2NqJ4o28IDOoWnsgAIZ9J1800rPj6rcOTb0tO9C4Z73M4CeOo0BSmGswYagrRR+ufQNusWt6z2j/2mTI3Qg2BKZxXnenVfbItVNzTWUmQFmDLEnpPm93vH6WWcg6J/JqBT/sit4pq4f7sNpEvSJfzDz77wigs6KGRgc5v41mgdDZxFkF8Tw3guF9NE=";
	char * imei = "355905073519317";  // "359471060237567";     //
	char *aaa = "9880222b04fda300f76f52ef6976d010"; // "7362135407032643";
	unsigned char *testData = NULL;
	int len = 0;
	testData = (unsigned char *)base64_decode((const char *)ciphertext, strlen(ciphertext), len);
	 printfOutResult(testData, len);
	// testData=(unsigned char *)base64_encode((const  char *)testData, len);
	 char* key = (char *)malloc(GEN_KEY_LEN);
	 memset(key, 0, GEN_KEY_LEN);
	 generateKey(imei, aaa, key);
	 key[16] = '\0';
	 char *iv = key;
	 unsigned char * final = NULL;
	 int ciphertext_len = 0;  //ciphertext: 密文  plaintext,明文
	 unsigned char plaintext[MAX_CHAR_SIZE];
	 memset(plaintext, 0, MAX_CHAR_SIZE);
	 int plain_len = 0;
	 final = decrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)testData, &len, plaintext, plain_len);
	 printf("%s\n[%d]\n\n", final, strlen((char *)final));
	 printfOutResult(final, plain_len);
	return 0;
}
int test4_sign(char * input){
	char * ciphertext = input;//"ULcsJxzForUPnESIx2sm5tOxC5J5ZmhBpQGl53+jB4eRo70Ddk04FwZ0g/aFF9QZFY/rD+7QUe5MK6cWZYA9IhiUaP6gpvONgAJjGWpuIH0dkiNw/fvI2AoaFYUFaG5iZ3tGBsm+/T4lWPKGHp/BYY2rVgSkRfYyRlFvjtdkHNYAX5kkLb2nO5STKjcih9vsX91RmRq6trAMfu2WJk3+ICdpM2rRdXCkidAtFav4awAHKy7actZ9uW4sOczcNi6l+QUKX1Zz4hHjSkbj9Uf6CWUJciLU+6OV8OaqqySU1oMDA8nj6u82G6F/KEVgsYQk9Wl84wjDPuJ8x/ltPikljXQSaHqoXDgV8rrMP3JXqCpJQSl2e22YVesp9uhYsI+2Wq61VAEf7yPUvIIktEba0fzb3c7Ck3IZywiCFFFetba4VXfCJCktCQXwsBYKr+vA5UrEMj8CDm8xcgxrD4v1bnQj6WMmN6Tir8JtWd73fVraIqexPnbmj4XPSgllXvzkN7UOHvUKXEn5q3nZa0DfcXXflBHYICXHs079PLXaU2YOOHQgE2NqJ4o28IDOoWnsgAIZ9J1800rPj6rcOTb0tO9C4Z73M4CeOo0BSmGswYagrRR+ufQNusWt6z2j/2mTI3Qg2BKZxXnenVfbItVNzTWUmQFmDLEnpPm93vH6WWcg6J/JqBT/sit4pq4f7sNpEvSJfzDz77wigs6KGRgc5v41mgdDZxFkF8Tw3guF9NE=";
	char * imei ="359471060237567";     //为主//   "356845051207403";
	char *aaa = "8781470884165120"; // "7362135407032643";
	unsigned char *testData = NULL;
	int len = 0;
	testData = (unsigned char *)base64_decode((const char *)ciphertext, strlen(ciphertext), len);
	printfOutResult(testData, len);
	// testData=(unsigned char *)base64_encode((const  char *)testData, len);
	char* key = (char *)malloc(GEN_KEY_LEN);
	memset(key, 0, GEN_KEY_LEN);
	generateKey(imei, aaa, key);
	key[16] = '\0';
	char *iv = key;
	unsigned char * final = NULL;
	int ciphertext_len = 0;  //ciphertext: 密文  plaintext,明文
	unsigned char plaintext[MAX_CHAR_SIZE];
	memset(plaintext, 0, MAX_CHAR_SIZE);
	int plain_len = 0;
	final = decrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)testData, &len, plaintext, plain_len);
	printf("%s\n[%d]\n\n", final, strlen((char *)final));
	printfOutResult(final, plain_len);
	int signStrLen = 0x129;
	char * signStr = (char *)malloc(signStrLen+1);
	memset(signStr, 0, signStrLen + 1);
	strncpy(signStr, (char *)final, signStrLen);
	printf("\n\n签名串：%s\n\n签名串长度: %d",signStr, signStrLen);
	printf("\n\n_____________________________________________________");
	printf("\n\n---\t公钥校验过程\t---\n");
	char * sign_value = "8CA85C67A16A63B54A1E5F173CD5939FAF9D511F32A261B2C95C4B446B1EEBE724D4E0547CF1E034FE02CE8BDC39278148858D38744099DA9C42A118D9A17401F8D9D371BFA27D6215D5D55D7C1F09C33F5BBCC399063A316B3B5C2AB62D74DA5DABCA8BDFC9A823542982D1B77D12D1A88ECB8D09CFA7947CBC004336C8C4BA";
	char *publicKey = "30819F300D06092A864886F70D010101050003818D0030818902818100AEF569995CFFCF03BE3B2200883D5416D6679377004881EA157E2B340ED728E4C13DF2283BB25914ABB9FC0C5E89C972BD7E9F0DF2C3491FDA534A26EEBEC15F9823FA29884A1B052A89350E3CE8E4AC1CEE98F53B4DBB9B728A7DB885E0EAF26F9160596DE115FBCDC9031F76DD6D3410EE5F7491C5F98ADF14203FFC012A110203010001";
	char *pubStr = hexStringToString(publicKey, strlen(publicKey));
	printfOutResult((unsigned char *)pubStr, strlen(publicKey)/2);
	//printfOutResult((unsigned char *)publicKey, strlen(publicKey) /2);
	EVP_PKEY * pub_key = getEvpPublicKeyByCharArray((unsigned char *)pubStr, strlen(publicKey) / 2);
	signatureVerify((unsigned char *)signStr, strlen((char *)signStr), (unsigned char *)hexStringToString(sign_value, strlen(sign_value)), strlen(sign_value)/2, pub_key);
	return 0;
}
int test5_encrypt(){
	char * initData = "xxxxxxxxxxxxxxxx3,6EC54A61#1,359471060237567#2,##6,0#6,1#6,3#6,16#6,17#6,18#6,19#6,20#6,21#6,22#6,23#6,24#6,25#6,26#6,27#6,28#6,29#6,30#6,31#6,32#6,33#6,37#6,39#6,40#4,sIbuTAmbhJw/3uCX8wyCRv/VzWjzNZQpGDFBs/SdI9JqThokWkGgQT8czGUgtDV4mhf7pDFTrMRKi+N+Omc0ddSBX8+PWJpEhBivE8kaQUfp4vcZPP9msqbOTeNlSnub#7,8CA85C67A16A63B54A1E5F173CD5939FAF9D511F32A261B2C95C4B446B1EEBE724D4E0547CF1E034FE02CE8BDC39278148858D38744099DA9C42A118D9A17401F8D9D371BFA27D6215D5D55D7C1F09C33F5BBCC399063A316B3B5C2AB62D74DA5DABCA8BDFC9A823542982D1B77D12D1A88ECB8D09CFA7947CBC004336C8C4BA";
	char * imei = "359471060237567";  
	char *aaa = "8781470884165120"; 
	char* key = (char *)malloc(GEN_KEY_LEN);
	memset(key, 0, GEN_KEY_LEN);
	generateKey(imei, aaa, key);
	key[16] = '\0';
	char *iv = key;
	char * ciphertext = NULL;
	int ciphertext_len = 0;
	unsigned char * r=encrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)initData, ciphertext_len , (unsigned char *)ciphertext);
	printf("\n\nresult:\n\n%s\n\n", base64_encode((char *)r, ciphertext_len));
//	test4_sign(base64_encode((char *)r, ciphertext_len));
	return 0;
}
int test6_userMyPublicKey(){
	EVP_PKEY *pub_key = open_public_key(PUBLIC_KEY_FILE);
	EVP_PKEY *pri_key = open_private_key(PRIVATE_KEY_FILE, (const unsigned char *)RSA_PRIKEY_PSW);

	char* needData = "xxxxxxxxxxxxxxxx3,6EC54A61#1,359471060237567#2,##6,0#6,1#6,3#6,16#6,17#6,18#6,19#6,20#6,21#6,22#6,23#6,24#6,25#6,26#6,27#6,28#6,29#6,30#6,31#6,32#6,33#6,37#6,39#6,40#4,sIbuTAmbhJw/3uCX8wyCRv/VzWjzNZQpGDFBs/SdI9JqThokWkGgQT8czGUgtDV4mhf7pDFTrMRKi+N+Omc0ddSBX8+PWJpEhBivE8kaQUfp4vcZPP9msqbOTeNlSnub#";
	printf("\n\n---\t私钥签名过程\t---");
	char * content = needData;
	printf("\n签名原串：%s" , content);
	int sign_len = 0;
	unsigned char * signStr = signature((unsigned char *)needData, strlen(needData), sign_len, pri_key);
	printf("\n\nsign_value:\n\n");
	printfOutResult(signStr, sign_len);
	printf("\n签名串base64结果：\n%s\n\n" , base64_encode((char *)signStr,sign_len));
	int last_needDataLen = strlen(needData) + sign_len*2 + 30;
	char *last_needData = (char *)malloc(last_needDataLen);
	memset(last_needData, 0, last_needDataLen);
	strcpy(last_needData, needData);
	strcat(last_needData, "7,");
	char* sign_value_hex=stringToHexString(signStr, sign_len);
	//printf("\n%d\n%s", strlen(sign_value_hex), sign_value_hex);
	strcat(last_needData, sign_value_hex);
	strcat(last_needData, "#");
	char * imei = "359471060237567";
	char *aaa = "8781470884165120";
	char* key = (char *)malloc(GEN_KEY_LEN);
	memset(key, 0, GEN_KEY_LEN);
	generateKey(imei, aaa, key);
	key[16] = '\0';
	char *iv = key;
    char space[] ={0x04, 0x04, 0x04, 0x04, '\0'};
	char * ciphertext = NULL;
	int ciphertext_len = 0;
	strcat(last_needData, space);
	printf("\n%s\n", last_needData);
	unsigned char * r = encrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)last_needData, ciphertext_len, (unsigned char *)ciphertext);
	char * handy_license = base64_encode((char *)r, ciphertext_len);
	int replace_len = strlen(handy_license);
	char *replaceBlank_handy_license = replaceBlank(handy_license,replace_len);
	printf("\n生成密文如下:\n%s\n\n", replaceBlank_handy_license);
	char * fileName = "handy.license";
	char * newLineStr = "\r\n";
	char * handy = "Nemo Handy-A";
	char * plaintext = replaceBlank_handy_license;
	char *sb = (char *)malloc(2048);
	memset(sb, 0, 2048);
	strcat(sb, handy);
	strcat(sb, newLineStr);
	strcat(sb, "imei:");
	strcat(sb, imei);
	strcat(sb, newLineStr);
	strcat(sb, aaa);
	strcat(sb, newLineStr);
	strcat(sb, plaintext);
	printf("生成证书文件如下:\n\n%s\n\n", sb);
    //wirteDataToFile(fileName, sb);

	printf("\n\n_____________________________________________________");
	printf("\n\n---\t公钥校验过程\t---\n");
	signatureVerify((unsigned char *)content, strlen(needData), signStr, sign_len, pub_key);
	return 0;
}
int test7_getDataFromFile(){
	EVP_PKEY *pub_key = open_public_key(PUBLIC_KEY_FILE);
	EVP_PKEY *pri_key = open_private_key(PRIVATE_KEY_FILE, (const unsigned char *)RSA_PRIKEY_PSW);
	char * fileName = "handy.license";
	char *fileData = readDataFromFileByLine(fileName);
	//printf("%s", fileData);
	//printfOutResult((unsigned char *)fileData, strlen(fileData)); 
	int len = strlen(fileData);
	fileData=replaceBlank(fileData, len);
	char *nemoHandy = strtok(fileData, ";");
	char *imeiStr=strtok(NULL, ";");
	char *aaa = strtok(NULL, ";");
	char *initData = strtok(NULL, ";");
	char *imei_before= strtok(imeiStr, ":");
	char *imei = strtok(NULL, ";"); 
	//printf("\n\n%s", imei);
	char* key = (char *)malloc(GEN_KEY_LEN);
	memset(key, 0, GEN_KEY_LEN);
	generateKey(imei, aaa, key);
	key[16] = '\0';
	char *iv = key;
	unsigned char *testData = NULL;
	int  initData_len = 0;
	testData = (unsigned char *)base64_decode((const char *)initData, strlen(initData), initData_len);
	//printfOutResult(testData, initData_len);
	unsigned char * final = NULL;
	int ciphertext_len = 0;  //ciphertext: 密文  plaintext,明文
	unsigned char plaintext[MAX_CHAR_SIZE];
	memset(plaintext, 0, MAX_CHAR_SIZE);
	int plain_len = 0;
	final = decrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)testData, &initData_len, plaintext, plain_len);
	//printf("%s\n[%d]\n\n", final, strlen((char *)final));
	//printfOutResult(final, plain_len);
	printf("\n\n原始串：%s\n\n原始串长度: %d", final, plain_len);
	int need_signStrLen = 0x129;
	char *need_sign_data = (char *)malloc(need_signStrLen+1);
	strncpy(need_sign_data, (char *)final, need_signStrLen);
	need_sign_data[need_signStrLen] = '\0';
	printf("\n\n签名串：%s\n\n签名串长度: %d", need_sign_data, need_signStrLen);
	char *signHexStr = getSignHexStrByPlainText((char *)final, need_signStrLen);
	int sign_value_len = strlen(signHexStr) / 2;
	printf("\n检验值的hex-结果：len=%d\n", sign_value_len);
	unsigned char * sign_value = (unsigned char *)hexStringToString(signHexStr, strlen(signHexStr));
	printfOutResult(sign_value, strlen(signHexStr) / 2);
	printf("\n\n_____________________________________________________");
	printf("\n\n---\t公钥校验过程\t---\n");
	signatureVerify((unsigned char *)need_sign_data, need_signStrLen, sign_value, sign_value_len, pub_key);
	printf("\n\n");
	return 0;
}
int test8_integrateTotal(){
	char *fileName = "../data.txt";
	char *licenName = "../handy.license1";
	char *initDataFromFile = readDataFromFile(fileName);
	char *initData = (char *)malloc(strlen(initDataFromFile) + 1);
	memset(initData, 0, strlen(initDataFromFile) + 1);
	strcpy(initData, initDataFromFile);
	printf("initData:\n\n%s\n\n", initDataFromFile);
	char *imei = extractionImei(initDataFromFile);
	printf("\n\nimei:\n%s\n\n", imei);
	char *aaa = generateRandomNum(16);
	printf("\n\n随机数：%s\n\n", aaa);
	EVP_PKEY *pub_key = open_public_key(PUBLIC_KEY_FILE);
	EVP_PKEY *pri_key = open_private_key(PRIVATE_KEY_FILE, (const unsigned char *)RSA_PRIKEY_PSW);
	generateLicense(initData, aaa, imei, pri_key, licenName);
	signatureVerifyLicense(pub_key, licenName);
	return 0;
}

//test9: 有问题,产生原因是：生次公钥与私钥用完一次后会自动释放，下次使用要得新生成
int test9_update1(char * initDataFileName, char *inputImei){
	char *filePathName = "./handyLicense";
	createDirectory(filePathName);
	char *fileName = initDataFileName;
	char *initLicenName = "./handyLicense/handy.license-";
	char *licenName = (char *)malloc(strlen(initLicenName) + 20);
	memset(licenName, 0, strlen(initLicenName) + 20);
	strcpy(licenName, initLicenName);
	char *initDataFromFile = readDataFromFileByLine(fileName);
	int initDataLenBegin = strlen(initDataFromFile);
	//printf("\ninitData:%d\n\n%s\n\n", initDataLenBegin, initDataFromFile);
	int initDataLineNum = 0;
	int initDataReplaceBlankLen = initDataLenBegin;
	initDataFromFile=replaceBlank(initDataFromFile, initDataReplaceBlankLen);
	char *initData = (char *)malloc(strlen(initDataFromFile));
	memset(initData, 0, strlen(initDataFromFile) + 20);
	strncpy(initData, initDataFromFile,strlen(initDataFromFile));
	printf("\ninitData:%d\n\n%s\n\n", initDataReplaceBlankLen, initData);
	//printf("\ninitDataFromFile:%d\n\n%s\n\n", initDataReplaceBlankLen,initDataFromFile);
	initDataLineNum=initDataLenBegin - initDataReplaceBlankLen+1;
	char * newInitData = strtok(initDataFromFile, ";");
	printf("\ninitDataFromFile:\n%s\n\n",  initDataFromFile);
	int licenLen = strlen(initLicenName);
    int i = 0;
//	for (int i = 0; i < initDataLineNum; i++){
		//处理一行数据
		memset(licenName + licenLen, 0, 20);
		genLicenseAndSignature(newInitData, licenName, i, inputImei);
    	printf("\ninitData:%d\n\n%s\n\n", initDataReplaceBlankLen, newInitData);
		strncpy(newInitData, initData + strlen(newInitData)+1, strlen(newInitData));
		printf("\ninitData:%d\n\n%s\n\n", initDataReplaceBlankLen, initData + (initDataReplaceBlankLen*(i + 1)));
	//}
		system("pause");
	return 0;
}
int test9_update2(char * initDataFileName, char *inputImei){
	EVP_PKEY *pub_key = open_public_key(PUBLIC_KEY_FILE);
	EVP_PKEY *pri_key = open_private_key(PRIVATE_KEY_FILE, (const unsigned char *)RSA_PRIKEY_PSW);
	char *filePathName = "./handyLicense";
	createDirectory(filePathName);
	char *initDataFromFile = readDataFromFileByLine(initDataFileName);
	int initDataLenBegin = strlen(initDataFromFile);
	printf("\ninitDataFromFile:%d\n\n%s\n\n", initDataLenBegin, initDataFromFile);
	int initDataLineNum = 0;
	int initDataReplaceBlankLen = initDataLenBegin;
	initDataFromFile = replaceBlank(initDataFromFile, initDataReplaceBlankLen);
	char *initData = (char *)malloc(strlen(initDataFromFile));
	memset(initData, 0, strlen(initDataFromFile) + 20);
	strncpy(initData, initDataFromFile, strlen(initDataFromFile));
	printf("\ninitData:%d\n\n%s\n\n", initDataReplaceBlankLen, initData);
	//printf("\ninitDataFromFile:%d\n\n%s\n\n", initDataReplaceBlankLen,initDataFromFile);
	initDataLineNum = initDataLenBegin - initDataReplaceBlankLen + 1;
	char * newInitData = strtok(initData, ";");
	char *data_last = (char *)malloc(1024);
	memset(data_last, 0, 1024);
	printf("\n%s", newInitData);
	strcpy(data_last, newInitData);
	newGenLicenseAndSignature(data_last, inputImei, pub_key,pri_key);
	free(data_last);
	system("pause");
	return 0;
}
int test10_update3(char * initDataFileName){
	char *filePathName = "./handyLicense";
	createDirectory(filePathName);
	int fileLineNum=getFileDataLineNumber(initDataFileName);
	for (int i = 1; i <= fileLineNum; i++){
		EVP_PKEY *pub_key = open_public_key(PUBLIC_KEY_FILE);
		EVP_PKEY *pri_key = open_private_key(PRIVATE_KEY_FILE, (const unsigned char *)RSA_PRIKEY_PSW);
		char * initDataFromFile = readDataFromFileByAssignLine(initDataFileName, i);
		int initDataReplaceBlankLen = strlen(initDataFromFile);
		initDataFromFile = replaceBlank(initDataFromFile, initDataReplaceBlankLen);
		printf("\n\ninitData,lineNum:%d : %s", i, initDataFromFile);
		newGenLicenseAndSignatureUpdate(initDataFromFile,pub_key, pri_key);
		free(initDataFromFile);
		//Sleep(2000);
	}
	return 0;
}

