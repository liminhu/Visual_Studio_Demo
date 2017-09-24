#ifndef  __RSAKEY_H_
#define __RSAKEY_H_

#include <stdio.h>  
#include <openssl/evp.h>  
//#include <crypto/evp/evp_locl.h> 
#include <openssl/crypto.h>
#include <openssl/rand.h>  
#include <openssl/rsa.h>  
#include <openssl/pem.h>

#include <openssl/aes.h>  
#include<openssl/x509.h>
#include<openssl/pkcs7.h>

#define EVP_AES_CBC EVP_aes_128_cbc()
#define RSA_KEY_LENGTH 1024  
static const char rnd_seed[] = "string to make the random number generator initialized";

#ifdef WIN32  
#define PRIVATE_KEY_FILE "rsa_priv.key"  
#define PUBLIC_KEY_FILE "rsa_pub.key"  
#else   // non-win32 system  
#define PRIVATE_KEY_FILE "/tmp/avit.data.tmp1"  
#define PUBLIC_KEY_FILE  "/tmp/avit.data.tmp2"  
#endif  

#define RSA_PRIKEY_PSW "123"  
#define GEN_KEY_LEN 20


#ifdef WIN32  
#pragma comment(lib, "libeay32.lib")  
#pragma comment(lib, "ssleay32.lib")  
#endif  

EVP_PKEY* generate_private_key();
// ���ɹ�Կ�ļ���˽Կ�ļ���˽Կ�ļ���������  
int generate_key_files(const char *pub_keyfile, const char *pri_keyfile);


// ���ɹ�Կ�ļ���˽Կ�ļ���˽Կ�ļ�������  
int generate_key_files(const char *pub_keyfile, const char *pri_keyfile, const unsigned char *passwd, int passwd_len);

// �򿪹�Կ�ļ�������EVP_PKEY�ṹ��ָ��  
EVP_PKEY* open_public_key(const char *keyfile);

// ��˽Կ�ļ�������EVP_PKEY�ṹ��ָ��  
EVP_PKEY* open_private_key(const char *keyfile, const unsigned char *passwd);

EVP_PKEY* open_private_key(const char *keyfile);


// ʹ����Կ���ܣ����ַ�װ��ʽֻ���ù�Կ���ܣ�˽Կ���ܣ�����key�����ǹ�Կ  
int rsa_key_encrypt(EVP_PKEY *key, const unsigned char *orig_data, size_t orig_data_len,
	unsigned char *enc_data, size_t &enc_data_len);

// ʹ����Կ���ܣ����ַ�װ��ʽֻ���ù�Կ���ܣ�˽Կ���ܣ�����key������˽Կ  
//int rsa_key_decrypt(EVP_PKEY *key, const unsigned char *enc_data, size_t enc_data_len,
//	unsigned char *orig_data, size_t &orig_data_len, const unsigned char *passwd);

int rsa_key_decrypt(EVP_PKEY *key, const unsigned char *enc_data, size_t enc_data_len,
	unsigned char *orig_data, size_t &orig_data_len);


unsigned char *encrypt_text(unsigned char *iv, unsigned char *key, unsigned char *plaintext, int &ciphertext_len, unsigned char *ciphertext);
unsigned char *decrypt_text(unsigned char *iv, unsigned char *key, unsigned char *ciphertext, int *ciphertext_len, unsigned char* plaintext, int &plain_len);

EVP_PKEY * getEvpPublicKeyByCharArray(unsigned char * publicKeyStr,  int pub_key_len);
EVP_PKEY * getEvpPrivateKeyByCharArray(unsigned char * priKeyStr, int pri_key_len);

int signatureVerify(unsigned char *signStr, int singStr_len, unsigned char *sign_value, int sign_value_len, EVP_PKEY  *evpKey);
//����ǩ��ֵ
unsigned char *signature(unsigned char *signStr, int singStr_len, int &sign_value_len, EVP_PKEY  *evpKey);

#endif