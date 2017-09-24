#ifndef   __MYUTIL_H_
#define  __MYUTIL_H_

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <io.h>
#include <direct.h>

char *replaceBackslash(char * inputData);
void printfOutResult(unsigned char *data, int len);    //16���ƴ�ӡ����
int wirteDataToFile(char * fileName, char * data);  //������д���ļ�
char *readDataFromFileByLine(char *fileName);
char *readDataFromFile(char *fileName);
int createDirectory(char *filePathName);
int  getFileDataLineNumber(char *fileName);
char *readDataFromFileByAssignLine(char *fileName, int lineNum);
char *hexStringToString(char *src, int src_len);
char * stringToHexString(unsigned char *src, int src_len);
char *replaceBlank( char * inputData, int &len);
char *generateRandomNum(int number);

#endif