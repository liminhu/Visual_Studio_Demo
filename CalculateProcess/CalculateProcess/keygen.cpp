#include "stdafx.h"
#include <sys/utime.h>
#include <Windows.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


char * create_key_table(){
	char * table = new char[0x100];
	int i;
	for (i = 0; i < 0x100; i++){
		table[i] = 0x80;
	}

	for (i = 0; i < 26; i++){
		table[i + 65] = i;
	}

	char * tmp = table + 0x61;
	for (; i < 52; i++, tmp++){
		*tmp = i;
	}

	tmp = table + 0x30;
	for (; i < 62; i++, tmp++){
		*tmp = i;
	}

	table[0x2B] = 62;
	table[0x2F] = 63;
	table[0x3D] = 0;

	return table;
}


int find_value_in_table(char * table, char val){
	int i;
	for (i = 0; i < 0x100; i++){
		if (table[i] == val){
			return i;
		}
	}
	return 0;
}

char * name_to_key(char * name, int * pkey_len)
{
	char s4[4];
	int len = strlen(name);
	if (len % 3 != 0){
		int new_len = len + (3 - len % 3) + 1;
		char * new_name = new char[new_len];
		memset(new_name, 0, new_len);
		strcpy(new_name, name);
		name = new_name;
		len = new_len;
	}
	int key_len = len / 3 * 4;
	char * key = new char[key_len + 1];
	memset(key, 0, key_len + 1);
	char * table = create_key_table();
	int i, j;
	char * pname = name;
	char * pkey = key;
	for (i = 0; i < strlen(name); i += 3){
		s4[0] = pname[0] >> 2;
		s4[1] = ((pname[0] & 0x3) << 4) | (pname[1] >> 4);
		s4[2] = ((pname[1] & 0xF) << 2) | (pname[2] >> 6);
		s4[3] = pname[2] & 0x3F;
		pname += 3;
		for (j = 0; j < 4; j++){
			int tmp = find_value_in_table(table, s4[j]);
			pkey[j] = (char)tmp;
		}
		pkey += 4;
	}
	*pkey_len = key_len;
	delete[] table;
	return key;
}

char * key_to_name(char * key, int *name_len)
{
	int i;
	int len = strlen(key);
	if (len < 9){
		return NULL;
	}
	int j = 0;

	char * name = new char[len];

	char * table = create_key_table();

	char s4[4];
	i = 0;
	int new_len = 0;
	char * pname = name;
	for (i = 0; i < len - 3; i += 4){
		for (j = 0; j < 4; j++){
			char tmp = table[*(key + i + j)];
			if (tmp & 0x80){
				s4[j] = 0;
			}
			else{
				s4[j] = tmp;
			}
		}
		new_len += 3;
		pname[0] = s4[1] >> 4 | s4[0] << 2;
		pname[1] = s4[1] << 4 | s4[2] >> 2;
		pname[2] = s4[2] << 6 | s4[3];
		pname += 3;
	}
	*name_len = new_len;
	delete[] table;
	return name;
}

char * make_key(char * key){
	int len = strlen(key);
	char * new_key = new char[len + 4];
	memset(new_key, 0, len + 4);
	int i, j = 0;
	for (i = 0; i < len; i++){
		if (i == 3 || i == 6 || i == 9){
			new_key[j++] = '-';
		}

		new_key[j++] = key[i];
	}
	new_key[j] = 0;
	return new_key;
}


int my1_tmain(int argc, _TCHAR* argv[])
{
	char * account = "hulimi";
		if (argc < 2){
		printf("Usage : %s username", account);
		return 0;
	}
	
	unsigned int name_len = strlen(account);
	if (name_len - 6 > 14){
		printf("Too Long or Too Short username. 6 < length(username) < 21");
		return -1;
	}

	int key_len;
	char * key = name_to_key(account, &key_len);
	char * new_key = make_key(key);
	delete[] key;
	printf("Username : %s\n", account);
	printf("Key      : %s\n", new_key);

	delete[] new_key;
	return 0;
}