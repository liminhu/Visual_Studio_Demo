#include "RsaKey.h"
#include <stdio.h>
#include <stdlib.h>
#include "MyUtil.h"
#include "MyBase64.h"


#define MAX_CHAR_SIZE  1024

int test1_rsa_key();
int test2_generate_license();
int test3_decrypt_text();
int test4_sign(char *input);
int test5_encrypt();
int test6_userMyPublicKey();
int test7_getDataFromFile();
int test8_integrateTotal();
int test9_update1(char * initDataFileName, char *inputImei);
int test9_update2(char * initDataFileName, char *inputImei);
int test10_update3(char * initDataFileName);
