#include "stdafx.h"
#include "MyUtil.h"


//unsigned int __ROR4__(unsigned int value, int count) { return _rotr(value, count); }

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

 int unstring(){
	 char *data = "74EC084074EC08403F00000000000000";
	 char *st = data;
	 unsigned int ch[300];
	 unsigned char c[300];
	 unsigned char new_c[300];
	 printf("原始数据如下：\n\n");
	 printf("十六进制 十进制   字符\n");
	 for (int i = 0; i<strlen(st); i = i + 2)
	 {
		 ch[i / 2] = ((st[i]<64 ? st[i] - 48 : st[i] - 55) * 16) + (st[i + 1]<64 ? st[i + 1] - 48 : st[i + 1] - 55);
		 c[i / 2] = ch[i / 2];
		 printf("  %c%c   ", st[i], st[i + 1]);
		 printf("  %5d", ch[i / 2]);
		 printf("  %5c\n", c[i / 2]);
	 }
	 printf("整个原始数据转成新的字符串是：\n\n");
	 printf("原始16进制数   转化后的数据\n\n");
	 for (int i = 0; i < strlen(st); i = i + 2){
		 printf("  %c%c   ", st[i], st[i + 1]);

		// new_c[i / 2] = (((185 + c[i/2]* 143 + 254 * (185 & (c[i/2] - 1) * 143)) & 0xFF) - 143) * 251 & 0xFF;
	   // int v7 = 167 * c[i / 2] & 0xFF;
		 new_c[i / 2] = (-0x9F * c[i / 2] - 0x9B + (2 * 0x9B | 2 * c[i / 2] * 0x9F)) & 0xFF;;
		 printf("%02x %10d \n", new_c[i / 2], new_c[i / 2]);
	 }


	 printf("\n\n最终的结果展示：\n\n");
	 for (int i = 0; i < strlen(st); i = i + 2){
		 printf("%c", new_c[i / 2]);
		 //	printf("%2x", new_c[i / 2]);
	 }
	 printf("\n\n");
	 return 0;
 }