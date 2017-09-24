#include <sys/utime.h>
#include <Windows.h>
#include <stdlib.h>

typedef  struct
{
	unsigned int  v1;
	unsigned int  v2;
	char * cid;
	unsigned int v4;
	unsigned int v5;
}ResultStruct;

typedef unsigned int    MN_SIZE;
typedef char            MN_CHAR;
typedef int             MN_INT;
typedef unsigned int    MN_UINT;
typedef long            MN_LONG;
typedef short           MN_SHORT;
typedef unsigned long   MN_DWORD;
typedef unsigned short  MN_WORD;
typedef unsigned char   MN_BYTE;
typedef unsigned char   MN_UTF8;
typedef unsigned short  MN_WCHAR;
typedef float           MN_FLOAT;
typedef double          MN_DOUBLE;
typedef void            MN_VOID;


static const MN_CHAR s_chBase64EncodingTable[64] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
	'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
	'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
	'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

char* sub_27C3C(ResultStruct result);