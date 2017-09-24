#include "stdafx.h"
#include "MyUtil.h"


unsigned int __ROR4__(unsigned int value, int count) { return _rotr(value, count); }

int unsignedStringCopy(unsigned char *dest, unsigned char * src,  int len){
	for (int i = 0; i < len; i++){
		dest[i] = src[i];
	}
	return 0;
}



void printfOutResult(unsigned char *  data, int len){
	printf("\n");
	for (int i = 0; i < len; i++){
		printf("%.02x ", data[i] & 0xFF);
		if (i != 0 && (i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n");
}
int wirteDataToFile(char * fileName, char * data)
{
	FILE *fp;
	if ((fp = fopen(fileName, "wb")) == NULL){
		printf("\n创建%s文件失败", fileName);
		exit(0);
	}
	fwrite(data, sizeof(char), strlen(data), fp);
	fclose(fp);
	return 0;
}


char *hexStringToString(char *src, int src_len)
{
	char *dest = NULL;
	src = _strupr(src);
	if (strlen(src) <= 1 || strlen(src) % 2 != 0){
		printf("\n hexStringToString change error !!!\n\n");
		exit(0);
	}
	else
	{
		dest = (char  *)malloc(src_len / 2 + 1);
		memset(dest, 0, src_len / 2 + 1);
		for (int i = 0; i < strlen(src); i = i + 2)
		{
			dest[i / 2] = ((src[i] < 64 ? src[i] - 48 : src[i] - 55) * 16) + (src[i + 1] < 64 ? src[i + 1] - 48 : src[i + 1] - 55);
		}
		printf("\n");
	}
	return dest;
}

char * stringToHexString(unsigned char *src, int src_len){
	unsigned char *hex_str = NULL;
	char result[3];
	if (src_len > 0){
		hex_str = (unsigned char *)malloc(2 * src_len);
		memset(hex_str, 0, 2 * src_len);
	}
	for(int i = 0;  i < src_len;  i++){
		sprintf(result, "%02x",src[i]);
		strcat((char *)hex_str, result);
	}
	//printf("\n%s", hex_str);
	return (char *)hex_str;
}


 char *replaceBlank(char * inputData, int &len){
    char * replace = ( char *)malloc(len);
	int k = len,j=0;
	for (int i = 0; i < len; i++){
		if (inputData[i] == '\r' || inputData[i] == '\n' || inputData[i] == ' ' || inputData[i] == '\t'){
			k--;
		}
		else{
			replace[j] = inputData[i];
			j++;
		}
	}
	free(inputData);
	len = k;
	replace[k] = '\0';
	return replace;
}

 char *readDataFromFileByLine(char *fileName){
	 FILE* fp = NULL; //
	 if ((fp = fopen(fileName, "r")) == NULL) //判断文件是否存在及可
	 {
		 printf("file open error!");
		 exit(0);
		 //return NULL;
	 }
	 fseek(fp, 0, SEEK_END);
	 int file_size = ftell(fp);
	 fseek(fp, 0, SEEK_SET);
	 char* tmp = (char*)malloc((file_size + 10) * sizeof(char));
	 memset(tmp, 0, file_size + 10);
	 char*temp_read_data = (char*)malloc((file_size + 10) * sizeof(char));
	 int len = 0;
	 fgets(temp_read_data, file_size, fp);  //读取一行,并定位到下一行
	 while (!feof(fp))
	 {
		 len = strlen(temp_read_data);
		 strncat(tmp, temp_read_data, len);
		 strcat(tmp, ";");
		 fgets(temp_read_data, file_size, fp);  //读取一行,并定位到下一行
	 }
	 len = strlen(temp_read_data);
	 strncat(tmp, temp_read_data, len);
	// strcat(tmp, ";");
	 fclose(fp);
	 free(temp_read_data);
	 return tmp;
 }
 char *readDataFromFile(char *fileName){
	 FILE* fp = NULL; //
	 if ((fp = fopen(fileName, "r")) == NULL) //判断文件是否存在及可
	 {
		 printf("file open error!");
		 return NULL;
	 }
	 fseek(fp, 0, SEEK_END);
	 int file_size = ftell(fp);
	 fseek(fp, 0, SEEK_SET);
	 char* tmp = (char*)malloc((file_size + 1) * sizeof(char));
	 memset(tmp, 0, file_size + 1);
	 fread(tmp, file_size, sizeof(char), fp);
	 fclose(fp);
	 return tmp;
 }

 int  getFileDataLineNumber(char *fileName){
	 FILE* fp = NULL; //
	 if ((fp = fopen(fileName, "r")) == NULL) //判断文件是否存在及可
	 {
		 printf("file open error!");
		 exit(0);
		 //return NULL;
	 }
	 int fileLineNum = 0;
	 fseek(fp, 0, SEEK_END);
	 int file_size = ftell(fp);
	 fseek(fp, 0, SEEK_SET);
	 char*temp_read_data = (char*)malloc((file_size + 10) * sizeof(char));
	 int len = 0;
	 fgets(temp_read_data, file_size, fp);  //读取一行,并定位到下一行
	 while (!feof(fp))
	 {
		 fileLineNum++;
		 fgets(temp_read_data, file_size, fp);  //读取一行,并定位到下一行
	 }
	 fclose(fp);
	 free(temp_read_data);
	 return fileLineNum;
 }
 char *readDataFromFileByAssignLine(char *fileName, int lineNum){
	 FILE* fp = NULL; //
	 if ((fp = fopen(fileName, "r")) == NULL) //判断文件是否存在及可
	 {
		 printf("file open error!");
		 exit(0);
		 //return NULL;
	 }
	 int currentLineNum = 1;
	 fseek(fp, 0, SEEK_END);
	 int file_size = ftell(fp);
	 fseek(fp, 0, SEEK_SET);
	 char*temp_read_data = (char*)malloc((file_size + 10) * sizeof(char));
	 memset(temp_read_data, 0, file_size + 10);
	 int len = 0;
	 fgets(temp_read_data, file_size, fp);  //读取一行,并定位到下一行
	 while (!feof(fp))
	 { 
		 if (currentLineNum==lineNum)
			 break; 
		 else
		 {
			 currentLineNum++;
		 }
		 memset(temp_read_data, 0, file_size + 10);
		 fgets(temp_read_data, file_size, fp);  //读取一行,并定位到下一行
	 }
	 fclose(fp);
//	 free(temp_read_data);
	 return temp_read_data;
 }

 int createDirectory(char *filePathName){
	 int k = _access(filePathName, 0);
	 if (!_access(filePathName, 0)){
		 printf("\n文件夹%s已存在！",filePathName);
		 return 0;
	 }
	 else{
		 int status = 0;
		 _mkdir(filePathName);
		 printf("\n文件夹%s创建成功！", filePathName);
	 }
	 return 1;
 }
 char *generateRandomNum(int number){
	 char *needRandom = (char *)malloc(number + 1);
	 memset(needRandom, 0, number + 1);
	 srand((unsigned)time(NULL));
	 int num = 0;
	 char numStr[3];
	 for (int i = 0; i < number; i++){
		    num=rand() % 10;
			 _itoa(num, numStr, 10);
			 strncat(needRandom, numStr, 1);
	 }
	 return needRandom;
 }

 char * reverse_string(char *input_str){
	 int len = strlen(input_str);
	 char *result = (char *)malloc(len + 1);
	 memset(result, 0, len + 1);
	 for (int i = len - 1,j=0; i >= 0; i--,j++){
		 result[j] = input_str[i];
	 }
	 return result;
 }



 int newUnstring(){
	 char *dataHex = "2FC335AAF1AA8C63AAA9648C80AB7D92A96448C335AAF1AA8C63AAA9648C5063AA2020C34CAA7B1E7D48D251";
	 char *data = hexStringToString(dataHex, strlen(dataHex));
	 char *result = (char *)malloc(0xFF);
	 memset(result, 0, 0xFF);
	 int len = strlen(dataHex) / 2;
	 int a1 = 0;
	 for (int i = 0; i < len; i++){
		 a1 = data[i];
		 result[i] = -11 * a1 ^ 0xD3;

	 }
	 printf("原始数据hex值如下：%s\n\n", dataHex);
	 printf("\n\n最终的结果为：\n\n%s\n\n", result);
	 free(result);
	 printf("\n\n");
	 return 0;
 }