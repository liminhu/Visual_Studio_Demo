#include "stdafx.h"
#include "MyBase64.h"


/************************************************************************/
/* 
base64实现原理：它是用64个可打印字符表示二进制所有数据方法。由于2的6次方等于64，所以可以用每6个位元为一个单元，
对应某个可打印字符。我们知道三个字节有24个位元，就可以刚好对应于4个Base64单元，即3个字节需要用4个Base64的可打印字符来表示。
*/
/************************************************************************/
char *base64_encode(const char*data, int data_len)
{
	int prepare = 0;
	int ret_len;
	int temp = 0;
	char *ret = NULL;
	char *f = NULL;
	int tmp = 0;
	char changed[4];
	int i = 0;
	ret_len = data_len / 3;
	temp = data_len % 3;
	if (temp > 0)
	{
		ret_len += 1;
	}
	ret_len = ret_len * 4 + 1;
	ret = (char *)malloc(ret_len);
	if (ret == NULL)
	{
		printf("No enough memory.\n");
		exit(0);
	}
	memset(ret, 0, ret_len);
	f = ret;
	while (tmp < data_len)
	{
		temp = 0;
		prepare = 0;
		memset(changed, '\0', 4);
		while (temp < 3)
		{
			if (tmp >= data_len)
			{
				break;
			}
			prepare = ((prepare << 8) | (data[tmp] & 0xFF));
			tmp++;
			temp++;
		}
		prepare = (prepare << ((3 - temp) * 8));
		for (i = 0; i < 4; i++)
		{
			if (temp < i)
			{
				changed[i] = 0x40;
			}
             else
             {
				 changed[i] = (prepare >> ((3 - i) * 6)) & 0x3F;
              }
			*f = base[changed[i]];
			f++;
		}
	}
	*f = '\0';
	return ret;
}

static  char find_pos(char ch)
{
	char *ptr = (char *)strrchr(base, ch);  //查找字符在指定字符串中从正面开始的最后一次出现的位置
	return (ptr - base);
}



char *base64_decode(const char*data, int data_len, int &ori_len){
	int ret_len = (data_len / 4) * 3;
	int equal_count = 0;
	char *ret = NULL;
	char *f = NULL;
	int tmp = 0;
	int temp = 0;
	char need[3];
	int prepare = 0;
	int i = 0;
	if (*(data + data_len - 1) == '=')
	{
		equal_count += 1;
	}
	if (*(data + data_len - 2) == '=')
	{
		equal_count += 1;
	}
	if (*(data + data_len - 3) == '=')
	{
		equal_count += 1;
	}
	switch (equal_count)
	{
	case 0:
		ret_len += 4;
		break;
	case 1:
		ret_len += 4;
		break;
	case 2:
		ret_len += 3;
		break;
	case 3:
		ret_len += 2;
		break;
	}
	ret = (char *)malloc(ret_len);
	if (ret == NULL)
	{
		printf("No enough memory.\n");
		exit(0);
	}
	memset(ret, 0, ret_len);
	f = ret;
	while (tmp < (data_len - equal_count))
	{
		temp = 0;
		prepare = 0;
		memset(need, 0, 4);
		while (temp < 4)
		{
			if (tmp >= (data_len - equal_count))
			{
				break;
			}
			prepare = (prepare << 6) | (find_pos(data[tmp]));
			temp++;
			tmp++;
		}
		prepare = prepare << ((4 - temp) * 6);
		for (i = 0; i < 3; i++)
		{
			if (i == temp)
			{
				break;
			}
			*f = (char)((prepare >> ((2 - i) * 8)) & 0xFF);
			f++;
		}
	}
	*f = '\0';
	ori_len = f - ret-1;
	return ret;
}


char *base64_decode(const char*data, int data_len)
{
	int ret_len = (data_len / 4) * 3;
	int equal_count = 0;
	char *ret = NULL;
	char *f = NULL;
	int tmp = 0;
	int temp = 0;
	char need[3];
	int prepare = 0;
	int i = 0;
	if (*(data + data_len - 1) == '=')
	{
		equal_count += 1;
	}
	if (*(data + data_len - 2) == '=')
	{
		equal_count += 1;
	}
	if (*(data + data_len - 3) == '=')
	{
		equal_count += 1;
	}
	switch (equal_count)
	{
	case 0:
		ret_len += 4;
		break;
	case 1:
		ret_len += 4;
		break;
	case 2:
		ret_len += 3;
		break;
	case 3:
		ret_len += 2;
		break;
	}
	ret = (char *)malloc(ret_len);
	if (ret == NULL)
	{
		printf("No enough memory.\n");
		exit(0);
	}
	memset(ret, 0, ret_len);
	f = ret;
	while (tmp < (data_len -equal_count))
	{
		temp = 0;
		prepare = 0;
		memset(need, 0, 4);
		while (temp < 4)
		{
			if (tmp >= (data_len - equal_count))
			{
				break;
			}
			prepare = (prepare << 6) | (find_pos(data[tmp]));
			temp++;
			tmp++;
		}
		prepare = prepare << ((4 - temp) * 6);
		for (i = 0; i < 3; i++)
		{
			if (i == temp)
			{
				break;
			}
			*f = (char)((prepare >> ((2 - i) * 8)) & 0xFF);
			f++;
		}
	}
	*f = '\0';
	return ret;
}


char * Encbase64(char * orgdata, unsigned long orglen, unsigned long *newlen)
{
	char *p = NULL, *ret = NULL;
	int tlen = 0;
	if (orgdata == NULL || orglen == 0)
		return NULL;
	tlen = orglen / 3;
	if (tlen % 3 != 0) tlen++;
	tlen = tlen * 4;
	*newlen = tlen;
	if ((ret = (char *)malloc(tlen + 1)) == NULL)
		return NULL;
	memset(ret, 0, tlen + 1);
	p = orgdata; tlen = orglen;

	int i = 0, j = 0;
	while (tlen>0)
	{
		Udata.c[0] = Udata.c[1] = Udata.c[2] = 0;
		for (i = 0; i<3; i++)
		{
			if (tlen<1) break;
			Udata.c[i] = (char)*p;
			tlen--;
			p++;
		}
		if (i == 0) break;
		switch (i)
		{
		case 1:
			/*ret[j++]=_Base[Udata.Sdata.d];
			ret[j++]=_Base[Udata.Sdata.c];
			ret[j++]=_Base[64];
			ret[j++]=_Base[64];*/
			ret[j++] = _Base[Udata.c[0] >> 2];
			ret[j++] = _Base[((Udata.c[0] & 0x03) << 4) | ((Udata.c[1] & 0xf0) >> 4)];
			ret[j++] = _Base[64];
			ret[j++] = _Base[64];
			break;
		case 2:
			/*ret[j++]=_Base[Udata.Sdata.d];
			ret[j++]=_Base[Udata.Sdata.c];
			ret[j++]=_Base[Udata.Sdata.b];
			ret[j++]=_Base[64];*/
			ret[j++] = _Base[Udata.c[0] >> 2];
			ret[j++] = _Base[((Udata.c[0] & 0x03) << 4) | ((Udata.c[1] & 0xf0) >> 4)];
			ret[j++] = _Base[((Udata.c[1] & 0x0f) << 2) | ((Udata.c[2] & 0xc0) >> 6)];
			ret[j++] = _Base[64];
			break;
		case 3:
			/*ret[j++]=_Base[Udata.Sdata.d];
			ret[j++]=_Base[Udata.Sdata.c];
			ret[j++]=_Base[Udata.Sdata.b];
			ret[j++]=_Base[Udata.Sdata.a];*/
			ret[j++] = _Base[Udata.c[0] >> 2];
			ret[j++] = _Base[((Udata.c[0] & 0x03) << 4) | ((Udata.c[1] & 0xf0) >> 4)];
			ret[j++] = _Base[((Udata.c[1] & 0x0f) << 2) | ((Udata.c[2] & 0xc0) >> 6)];
			ret[j++] = _Base[Udata.c[2] & 0x3f];
			break;
		default:
			break;
		}
	}
	ret[j] = '\0';
	return ret;
}

char * Decbase64(char * orgdata, unsigned long orglen)
{
	char *p, *ret;
	int len;
	char ch[4] = { 0 };
	char *pos[4];
	int  offset[4];
	if (orgdata == NULL || orglen == 0)
	{
		return NULL;
	}
	len = orglen * 3 / 4;
	if ((ret = (char *)malloc(len + 1)) == NULL)
	{
		return NULL;
	}
	p = orgdata;
	len = orglen;
	int j = 0;

	while (len>0)
	{
		int i = 0;
		while (i<4)
		{
			if (len>0)
			{
				ch[i] = *p;
				p++;
				len--;
				if ((pos[i] = (char *)strchr(_Base, ch[i])) == NULL)
				{
					return NULL;
				}
				offset[i] = pos[i] - _Base;

			}
			i++;
		}
		if (ch[0] == '=' || ch[1] == '=' || (ch[2] == '='&&ch[3] != '='))
		{
			return NULL;
		}
		ret[j++] = (unsigned char)(offset[0] << 2 | offset[1] >> 4);
		ret[j++] = offset[2] == 64 ? '\0' : (unsigned char)(offset[1] << 4 | offset[2] >> 2);
		ret[j++] = offset[3] == 64 ? '\0' : (unsigned char)((offset[2] << 6 & 0xc0) | offset[3]);
	}
	ret[j] = '\0';
	return ret;
}