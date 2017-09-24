#include "stdafx.h"
#include "ToolUtil.h"
#include "testDemo.h"

/*
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
int  generateKey(char * imei, char * aaa, char* getKey){
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


char *extractionImeiMethodTow(char *inputData){
	char *imeiStr = strstr(inputData, "#1,");
	char *imei = NULL;
	if (imeiStr != NULL){
		imei = strtok(imeiStr + 3, "#");
	}
	return imei;
}
int *generateLicense(char* initData, char *aaa, char *imei, EVP_PKEY *evpKey, char*licenseName){
//	printf("\n\n---\t私钥签名过程\t---");
	char * content = initData;
//	printf("\n签名原串%d：%s", strlen(initData), content);
	int sign_len = 0;
	unsigned char * signStr = signature((unsigned char *)initData, strlen(initData), sign_len, evpKey);
//	printf("\n\nsign_value:\n\n");
//	printfOutResult(signStr, sign_len);
//	printf("\n签名串base64结果：\n%s\n\n", base64_encode((char *)signStr, sign_len));
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
//	printf("\n%s\n", last_needData);
	unsigned char * r = encrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)last_needData, ciphertext_len, (unsigned char *)ciphertext);
	char * handy_license = base64_encode((char *)r, ciphertext_len);
	int replace_len = strlen(handy_license);
	char *replaceBlank_handy_license = replaceBlank(handy_license, replace_len);
//	printf("\n生成密文如下:\n%s\n\n", replaceBlank_handy_license);
	char * fileName = licenseName;
	char * newLineStr = "\r\n";
	char * handy = "Nemo Handy-A";
	char * plaintext = replaceBlank_handy_license;
	char *sb = (char *)malloc(1024);
	memset(sb, 0, 1024);
	strcat(sb, handy);
	strcat(sb, newLineStr);
	strcat(sb, "imei:");
	strcat(sb, imei);
	strcat(sb, newLineStr);
	strcat(sb, aaa);
	strcat(sb, newLineStr);
	strcat(sb, plaintext);
//	printf("生成证书文件如下:\n\n%s\n\n", sb);
//	printf("\n\nfileName ： %s", fileName);
	wirteDataToFile(fileName, sb);
	free(sb);
	free(last_needData);
	free(signStr);
	free(r);
	return 0;
}
char *getSignHexStrByPlainText(char * plainText, int need_signStr_len){
	char *signStrArray = (plainText + need_signStr_len);
	char *signArray = strtok(signStrArray, ",");
	char *sign = strtok(NULL, "#");
	return sign;
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
//	printfOutResult(testData, initData_len);
	unsigned char * final = NULL;
	int ciphertext_len = 0;  //ciphertext: 密文  plaintext,明文
	unsigned char plaintext[MAX_CHAR_SIZE];
	memset(plaintext, 0, MAX_CHAR_SIZE);
	int plain_len = 0;
	final = decrypt_text((unsigned char *)iv, (unsigned char *)key, (unsigned char *)testData, &initData_len, plaintext, plain_len);
	//printf("%s\n[%d]\n\n", final, strlen((char *)final));
	//printfOutResult(final, plain_len);
//	printf("\n\n原始串：%s\n\n原始串长度: %d", final, plain_len);
	int need_signStrLen = 0x129;
	char *need_sign_data = (char *)malloc(need_signStrLen + 1);
	strncpy(need_sign_data, (char *)final, need_signStrLen);
	need_sign_data[need_signStrLen] = '\0';
	//printf("\n\n签名串：%s\n\n签名串长度: %d", need_sign_data, need_signStrLen);
	char * decyptlicenFileName = "handy.license.decrypt";
	char *file = (char *)malloc(128);
	memset(file, 0, 128);
	memcpy(file, decyptlicenFileName, strlen(decyptlicenFileName));
	strcat(file, "-");
	strcat(file, imei);
	strcat(file, "-");
	strcat(file, aaa);
	wirteDataToFile(file, need_sign_data);

	char *signHexStr = getSignHexStrByPlainText((char *)final, need_signStrLen);
	int sign_value_len = strlen(signHexStr) / 2;
//	printf("\n检验值的hex-结果：len=%d\n", sign_value_len);
	unsigned char * sign_value = (unsigned char *)hexStringToString(signHexStr, strlen(signHexStr));
//	printfOutResult(sign_value, strlen(signHexStr) / 2);
//	printf("\n\n_____________________________________________________");
//	printf("\n\n---\t公钥校验过程\t---\n");
	signatureVerify((unsigned char *)need_sign_data, need_signStrLen, sign_value, sign_value_len, evpKey);
//	printf("\n\n");
	return 0;
}
int 	newGenLicense(char *newInitData,  EVP_PKEY *pri_key){
	char *initData = (char *)malloc(strlen(newInitData) + 1);
	memset(initData, 0, strlen(newInitData) + 1);
	strcpy(initData, newInitData);
	//printf("\ninitData:%s\n\n", initData);
	char *imei = extractionImeiMethodTow(initData);
	//printf("\n\nimei:\n%s\n\n", imei);
	char *aaa = generateRandomNum(16);
	//printf("\n\n随机数：%s\n\n", aaa);
	char *licenName = (char *)malloc(1024);
	memset(licenName, 0, 1024);
	strcpy(licenName, "./handyLicense/handyLicense-");
	strcat(licenName, imei);
	strcat(licenName, "-");
	strcat(licenName, aaa);
	generateLicense(newInitData, aaa, imei, pri_key, licenName);
	free(licenName);
	free(initData);
	free(aaa);
	return 0;
}

int 	newGenLicenseAndSignatureVerify(char *newInitData, EVP_PKEY *pub_key, EVP_PKEY *pri_key){
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


int generateLicenseReadDataFromFile(char *fileName, EVP_PKEY *pri_key){
	char *filePathName = "./handyLicense";
	createDirectory(filePathName);
	int fileLineNum = getFileDataLineNumber(fileName);
//	printf("\nfile-line: %d\n\n\n", fileLineNum);
	//从第一行开始读取初始化数据
	for (int i = 1; i <= fileLineNum; i++){
		char * initDataFromFile = readDataFromFileByAssignLine(fileName, i);
		int initDataReplaceBlankLen = strlen(initDataFromFile);
		initDataFromFile = replaceBlank(initDataFromFile, initDataReplaceBlankLen);
	//	printf("\n\ninitData,lineNum:%d : %s", i, initDataFromFile);
		newGenLicense(initDataFromFile, pri_key);
		printf("\n证书%d生成\n", i);
		free(initDataFromFile);
		//Sleep(2000);
	}
	return 0;
}


int generateLicenseReadDataFromFile(char *fileName){
	char *filePathName = "handyLicense";
	createDirectory(filePathName);
	int fileLineNum = getFileDataLineNumber(fileName);
	//printf("\nfile-line: %d\n\n\n",fileLineNum);
	//从第一行开始读取初始化数据
	for (int i = 1; i <= fileLineNum; i++){
		//printf("\n\nfileName %s\n", PRIVATE_KEY_FILE);
		EVP_PKEY *pri_key = open_private_key(PRIVATE_KEY_FILE, (const unsigned char *)RSA_PRIKEY_PSW);
		char * initDataFromFile = readDataFromFileByAssignLine(fileName, i);
		int initDataReplaceBlankLen = strlen(initDataFromFile);
		initDataFromFile = replaceBlank(initDataFromFile, initDataReplaceBlankLen);
	//	printf("\n\ninitData,lineNum:%d : %s", i, initDataFromFile);
		newGenLicense(initDataFromFile, pri_key);
		free(initDataFromFile);
		//Sleep(2000);
	}
	return 0;
}

*/