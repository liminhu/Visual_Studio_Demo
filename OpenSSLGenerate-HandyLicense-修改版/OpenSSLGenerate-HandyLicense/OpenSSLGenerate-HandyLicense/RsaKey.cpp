#include "stdafx.h"
#include "RsaKey.h"
#include "MyUtil.h"

int generate_key_files(const char *pub_keyfile, const char *pri_keyfile){
	RSA *rsa = NULL;
	RAND_seed(rnd_seed, sizeof(rnd_seed));
	rsa = RSA_generate_key(RSA_KEY_LENGTH, RSA_F4, NULL, NULL);
	if (rsa == NULL)
	{
		printf("RSA_generate_key error!\n");
		return -1;
	}
	// ��ʼ���ɹ�Կ�ļ�  
	BIO *bp = BIO_new(BIO_s_file());
	if (NULL == bp)
	{
		printf("generate_key bio file  error!\n");
		return -1;
	}

	if (BIO_write_filename(bp, (void *)pub_keyfile) <= 0)
	{
		printf("BIO_write_filename error!\n");
		return -1;
	}

	if (PEM_write_bio_RSAPublicKey(bp, rsa) != 1)
	{
		printf("PEM_write_bio_RSAPublicKey error!\n");
		return -1;
	}

	// ��Կ�ļ����ɳɹ����ͷ���Դ  
	printf("Create public key ok!\n");
	BIO_free_all(bp);

	// ����˽Կ�ļ�  
	bp = BIO_new_file(pri_keyfile, "w+");
	if (NULL == bp)
	{
		printf("generate_key bio file error2!\n");
		return -1;
	}
	//EVP_aes_128_cbc(),
	if (PEM_write_bio_RSAPrivateKey(bp, rsa, EVP_aes_128_cbc(), NULL, NULL,NULL,NULL) != 1)
	{
		printf("PEM_write_bio_RSAPublicKey error!\n");
		return -1;
	}
	// �ͷ���Դ  
	printf("Create private key ok!\n");
	BIO_free_all(bp);
	// ����˽Կ�ļ�  
	bp = BIO_new_file(pri_keyfile, "w+");
	if (NULL == bp)
	{
		printf("generate_key bio file error2!\n");
		return -1;
	}

	RSA_free(rsa);
	return 0;
}


int generate_key_files(const char *pub_keyfile, const char *pri_keyfile, const unsigned char *passwd, int passwd_len)
{
	RSA *rsa = NULL;
	RAND_seed(rnd_seed, sizeof(rnd_seed));
	rsa = RSA_generate_key(RSA_KEY_LENGTH, RSA_F4, NULL, NULL);
	if (rsa == NULL)
	{
		printf("RSA_generate_key error!\n");
		return -1;
	}
	// ��ʼ���ɹ�Կ�ļ�  
	BIO *bp = BIO_new(BIO_s_file());
	if (NULL == bp)
	{
		printf("generate_key bio file new error!\n");
		return -1;
	}

	if (BIO_write_filename(bp, (void *)pub_keyfile) <= 0)
	{
		printf("BIO_write_filename error!\n");
		return -1;
	}

	if (PEM_write_bio_RSAPublicKey(bp, rsa) != 1)
	{
		printf("PEM_write_bio_RSAPublicKey error!\n");
		return -1;
	}

	// ��Կ�ļ����ɳɹ����ͷ���Դ  
	printf("Create public key ok!\n");
	BIO_free_all(bp);

	// ����˽Կ�ļ�  
	bp = BIO_new_file(pri_keyfile, "w+");
	if (NULL == bp)
	{
		printf("generate_key bio file new error2!\n");
		return -1;
	}
	if (PEM_write_bio_RSAPrivateKey(bp, rsa,
		EVP_aes_128_cbc(), (unsigned char *)passwd,
		passwd_len, NULL, NULL) != 1)
	{
		printf("PEM_write_bio_RSAPublicKey error!\n");
		return -1;
	}
	// �ͷ���Դ  
	printf("Create private key ok!\n");
	BIO_free_all(bp);
	RSA_free(rsa);
	return 0;
}


EVP_PKEY* open_public_key(const char *keyfile)
{
	EVP_PKEY* key = NULL;
	RSA *rsa = NULL;
	OpenSSL_add_all_algorithms();
	BIO *bp = BIO_new(BIO_s_file());
	BIO_read_filename(bp, keyfile);
	if (NULL == bp)
	{
		printf("open_public_key bio file new error!\n");
		return NULL;
	}

	rsa = PEM_read_bio_RSAPublicKey(bp, NULL, NULL, NULL);
	if (rsa == NULL)
	{
		printf("open_public_key failed to PEM_read_bio_RSAPublicKey!\n");
		BIO_free(bp);
		RSA_free(rsa);
		return NULL;
	}

	//printf("open_public_key success to PEM_read_bio_RSAPublicKey!\n");
	key = EVP_PKEY_new();
	if (NULL == key)
	{
		printf("open_public_key EVP_PKEY_new failed\n");
		RSA_free(rsa);

		return NULL;
	}

	EVP_PKEY_assign_RSA(key, rsa);
	return key;
}

EVP_PKEY* open_private_key(const char *keyfile){
	EVP_PKEY* key = NULL;
	RSA *rsa = NULL;
	OpenSSL_add_all_algorithms();
	BIO *bp = NULL;
	bp = BIO_new_file(keyfile, "rb");
	if (NULL == bp)
	{
		printf("open_private_key bio file new error!\n");
		return NULL;
	}
   //PEM_read_bio_RSAPublicKey
	rsa = PEM_read_bio_RSAPrivateKey(bp, NULL, NULL, NULL);
	if (rsa == NULL)
	{
		printf("open_private_key failed to PEM_read_bio_RSAPrivateKey!\n");
		BIO_free(bp);
		RSA_free(rsa);
		return NULL;
	}

//	printf("open_private_key success to PEM_read_bio_RSAPrivateKey!\n");
	key = EVP_PKEY_new();
	if (NULL == key)
	{
		printf("open_private_key EVP_PKEY_new failed\n");
		RSA_free(rsa);
		return NULL;
	}
	EVP_PKEY_assign_RSA(key, rsa);
	return key;
}


EVP_PKEY* open_private_key(const char *keyfile, const unsigned char *passwd)
{
	EVP_PKEY* key = NULL;
	RSA *rsa = RSA_new();
	OpenSSL_add_all_algorithms();
	BIO *bp = NULL;
	bp = BIO_new_file(keyfile, "rb");
	if (NULL == bp)
	{
		printf("open_private_key bio file new error!\n");
		return NULL;
	}
	rsa = PEM_read_bio_RSAPrivateKey(bp, &rsa, NULL, (void *)passwd);
	if (rsa == NULL)
	{
		printf("open_private_key failed to PEM_read_bio_RSAPrivateKey!\n");
		BIO_free(bp);
		RSA_free(rsa);
		return NULL;
	}

	//printf("open_private_key success to PEM_read_bio_RSAPrivateKey!\n");
	key = EVP_PKEY_new();
	if (NULL == key)
	{
		printf("open_private_key EVP_PKEY_new failed\n");
		RSA_free(rsa);
		return NULL;
	}
	EVP_PKEY_assign_RSA(key, rsa);
	return key;
}




EVP_PKEY* generate_private_key()
{
	EVP_PKEY* key = NULL;
	RSA *rsa = RSA_new();
	OpenSSL_add_all_algorithms();
	/*BIO *bp = NULL;
	bp = BIO_new(BIO_s_mem());
	BIO_puts(bp, private_key_str);
	//bp = BIO_new_mem_buf((void *)private_key_str, strlen(private_key_str));
	if (NULL == bp)
	{
		printf("open_private_key bio file new error!\n");
		return NULL;
	}
	*/
	FILE *file = NULL;
	char* fileName = "privateKey.keystore";
	char *pri_key_data = "-----BEGIN RSA PRIVATE KEY-----\nMIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBALMDBrfXX9Glf/nrar6Oq9vI4uiY\nzfZlnYQ2G3LFrPNbfE3kIsXTu+3Jv68UrqdhbvtCcGojExhQSl6VykfUJKtg0jfvOhuQXzc6mEA4\n0CgermB7sTpOTX6YZZotth072oy+1V/Ze+87u7ax/VHAoDiYe2T9a2lm4dxXHxaq+aCvAgMBAAEC\ngYAitWyBCsZuXLuClq28wub5l2q/lJkitDMlZmRODZvqF4vzgk9nshUXFu4OoWD33UFqgEhRm/lg\n1niE/GAbKzvsl6raXB+1SNakJx6S772VkKK7YqPiVbeJTAGXoozQElsTqWVnfqd01YMT/KQA3Ql2\n8xpRrN1G/U1mPO+1hsS6eQJBAN1NxjSBwPvHYRnAqnBaTo8beLTxR6FhsTb7Pf4/QgmI/nD9tIfd\nP13DaezAkXmvC61aLob1g6PYFcUXZSTnyJMCQQDPE9NRoqC4F69+C3X8WNARRS4j4Y131ocEuWbM\nt8aF4fwh8TJmK4+NjB+6lH+gZ9FXfd7SgqIJyNAXyGyshiT1AkEAr6PAgX/R2IJ/UF8XZqBl5TKa\ndJFilnTgn5B7vUQbd1HhD3BsTcCNQC+N7DdRvk/tZqJCdx54Yhtn+8r7nXTQPQJAbJ4xkfiD5QxH\neQ357UuImAZ5lUiSM/HLEKdPTMJ413EaF5O0o/LlcZG2ct/BshnCrOnRHwp2hDtZK6BtoHEcoQJB\nAKISh7minv5I70GHog48Yv0Jo6P7rDSLOZF7Qrr1L83eexjjxZzoVeNxHMmBmwnTjaXsL3Qcvm/+\n7U8MOiEFHxI=\n-----END RSA PRIVATE KEY-----\n";
	/*if (NULL == (file = fopen(fileName, "rb")))
	{
		printf("%s private key file not exist!\n", fileName);
		wirteDataToFile(fileName, pri_key_data);
		file = fopen(fileName, "rb");
	//	return NULL;
	}*/
	BIO *bp = NULL;
	bp = BIO_new(BIO_s_mem());
	BIO_puts(bp, pri_key_data);

/*	if ((rsa = PEM_read_RSAPrivateKey(file, NULL, NULL, NULL)) == NULL)
	{
	//	ERR_print_errors_fp(stdout);
	
		printf("open_private_key failed to PEM_read_RSAPrivateKey!\n");
		return NULL;
	}
	fclose(file);
*/

	rsa = PEM_read_bio_RSAPrivateKey(bp, &rsa, NULL, NULL);
	if (rsa == NULL)
	{
		printf("open_private_key failed to PEM_read_bio_RSAPrivateKey!\n");
		BIO_free(bp);
		RSA_free(rsa);
		return NULL;
	}

	//printf("open_private_key success to PEM_read_bio_RSAPrivateKey!\n");
	key = EVP_PKEY_new();
	if (NULL == key)
	{
		printf("open_private_key EVP_PKEY_new failed\n");
		RSA_free(rsa);
		return NULL;
	}
	EVP_PKEY_assign_RSA(key, rsa);
	return key;
}










int rsa_key_encrypt(EVP_PKEY *key, const unsigned char *orig_data, size_t orig_data_len,
	unsigned char *enc_data, size_t &enc_data_len)
{
	EVP_PKEY_CTX *ctx = NULL;
	OpenSSL_add_all_ciphers();

	ctx = EVP_PKEY_CTX_new(key, NULL);
	if (NULL == ctx)
	{
		printf("ras_pubkey_encryptfailed to open ctx.\n");
		EVP_PKEY_free(key);
		return -1;
	}

	if (EVP_PKEY_encrypt_init(ctx) <= 0)
	{
		printf("ras_pubkey_encryptfailed to EVP_PKEY_encrypt_init.\n");
		EVP_PKEY_free(key);
		return -1;
	}

	if (EVP_PKEY_encrypt(ctx,
		enc_data,
		&enc_data_len,
		orig_data,
		orig_data_len) <= 0)
	{
		printf("ras_pubkey_encrypt failed to EVP_PKEY_encrypt.\n");
		EVP_PKEY_CTX_free(ctx);
		EVP_PKEY_free(key);

		return -1;
	}

	EVP_PKEY_CTX_free(ctx);
	EVP_PKEY_free(key);
	return 0;
}

//˽Կ��������
int rsa_key_decrypt(EVP_PKEY *key, const unsigned char *enc_data, size_t enc_data_len,
	unsigned char *orig_data, size_t &orig_data_len)
{
	EVP_PKEY_CTX *ctx = NULL;
	OpenSSL_add_all_ciphers();

	ctx = EVP_PKEY_CTX_new(key, NULL);
	if (NULL == ctx)
	{
		printf("ras_prikey_decryptfailed to open ctx.\n");
		EVP_PKEY_free(key);
		return -1;
	}

	if (EVP_PKEY_decrypt_init(ctx) <= 0)
	{
		printf("ras_prikey_decryptfailed to EVP_PKEY_decrypt_init.\n");
		EVP_PKEY_free(key);
		return -1;
	}

	if (EVP_PKEY_decrypt(ctx,
		orig_data,
		&orig_data_len,
		enc_data,
		enc_data_len) <= 0)
	{
		printf("ras_prikey_decryptfailed to EVP_PKEY_decrypt.\n");
		EVP_PKEY_CTX_free(ctx);
		EVP_PKEY_free(key);
		return -1;
	}
	EVP_PKEY_CTX_free(ctx);
	EVP_PKEY_free(key);
	return 0;

}



/************************************************************************/
/*
iv����ǰ�ĳ�ʼ����
key: �ܳ�
plaintext: ����

һ����˵���ӽ���ʱ�㷨���õ���Կ�������û�����������ַ���������Ϊ�㷨
ʹ�õ���Կ����Ҫ���ǹ̶��ģ�ͨ��Ϊ64λ��128λ�����û��Լ���������볤��
��ȷ��������һ�㶼��Ҫ���û������������б任��ӳ�䵽һ���̶�������Կ
�ϣ�Ȼ���㷨��ʹ�ø���Կ���ܣ������㷨���õ���Կ���û�������һ���ǲ�ͬ��

*/
/************************************************************************/
unsigned char *encrypt_text(unsigned char *iv, unsigned char *key, unsigned char *plaintext, int &ciphertext_len, unsigned char *ciphertext) {
	//�����㷨�������ĽṹEVP_CIPHER_CTX������ṹ�ǽ����㷨ǰ��ϵͳ����ָ�����㷨�ṩ��
	EVP_CIPHER_CTX en;
	//opensslʹ����ͳһ��EVP_CIPHER�㷨�ṹ���ܺõط�װ�˸��ֶԳƼ����㷨��ʵ�����㷨�Ķ��󻯡�
	EVP_CIPHER_CTX_init(&en);
	const EVP_CIPHER *cipher_type;
	int input_len = 0;
	cipher_type = EVP_AES_CBC;
	//init cipher  
	int rv=EVP_EncryptInit_ex(&en, cipher_type, NULL, key, iv);
	if (rv != 1){
		printf("ERROR in EVP_EncryptInit_ex! \n");
		return NULL;
	}
	// We add 1 because we're encrypting a string, which has a NULL terminator  
	// and want that NULL terminator to be present when we decrypt.  
	//  input_len = strlen(plaintext) + 1;  
	input_len = strlen((char *)plaintext);
	int block_size = cipher_type->block_size;
	int data_len = input_len;
	if (data_len % block_size != 0){
		data_len = data_len + (block_size - (data_len % block_size));
	}
    unsigned char *datatext = (unsigned char *)malloc(data_len);
	memset(datatext, 0, data_len);
	strncpy((char *)datatext, (char *)plaintext, input_len);
	//printfOutResult(datatext, input_len);
	// This function works on binary data, not strings.  So we cast our  
	// string to an unsigned char * and tell it that the length is the string  
	// length + 1 byte for the null terminator.  
	int bytes_written = 0;
	//encrypt  
	ciphertext = (unsigned char *)malloc(2048);
	memset(ciphertext, 0, 2048);
	rv = EVP_EncryptUpdate(&en,
		ciphertext, &bytes_written,
		(unsigned char *)datatext, input_len);
	if (rv!=1 ){
		printf("ERROR in EVP_EncryptUpdate! \n");
		return NULL;
	}
	ciphertext_len += bytes_written;

	//do padding  
	if (!EVP_EncryptFinal_ex(&en,
		ciphertext + bytes_written,
		&bytes_written)){
		printf("ERROR in EVP_EncryptFinal_ex \n");
		return NULL;
	}
	ciphertext_len += bytes_written;
//	printf("\nencrypt string:\n ");
	//cleanup  
	EVP_CIPHER_CTX_cleanup(&en);
    unsigned char *data= (unsigned char *)malloc(ciphertext_len);
	memset(data, 0, ciphertext_len);
	for (int i = 0; i < ciphertext_len; i++){
		data[i] = ciphertext[i];
	}
	//printfOutResult(data, ciphertext_len);
	free(ciphertext);
	ciphertext = data;
	//printfOutResult(ciphertext, ciphertext_len);
	return data;
}





//AES128������ģʽΪ��CBC���˽����㷨ģʽ����Ҫ�Ĳ���Ϊ��16�ֽڵĽ���key��16�ֽڵ�IV����ʼ��������
unsigned char *decrypt_text(unsigned char *iv, unsigned char *key, unsigned char *ciphertext, int *ciphertext_len, unsigned char* plaintext, int &plain_len) {
	plain_len = 0;
	EVP_CIPHER_CTX de;
	EVP_CIPHER_CTX_init(&de);
	const EVP_CIPHER *cipher_type;
	int bytes_written = 0;
	int update_len = 0;
	cipher_type =EVP_AES_CBC; 

	int rv;
	//  rc = EVP_CIPHER_CTX_set_key_length(&de, strlen(pstRedirectConf->key));  
	//EVP_DecryptInit_ex(&de, cipher_type, NULL, key, iv);
	rv = EVP_DecryptInit_ex(&de, cipher_type, NULL, key, iv);
	if (rv!=1){
		printf("\t ERROR in EVP_DecryptInit_ex \n");
		EVP_CIPHER_CTX_cleanup(&de);
		return NULL;
	}
	int plaintext_len = 0;
	rv = EVP_DecryptUpdate(&de,
		plaintext, &update_len,
		ciphertext, *ciphertext_len);
	if (rv!=1){
		printf("ERROR in EVP_DecryptUpdate\n");
		EVP_CIPHER_CTX_cleanup(&de);
		return NULL;
	}
	rv = EVP_DecryptFinal_ex(&de,
		plaintext + update_len, &bytes_written);
	bytes_written += update_len;
	plain_len = bytes_written;
	*(plaintext + bytes_written) = '\0';
	EVP_CIPHER_CTX_cleanup(&de);
	return plaintext;
}

int  this_test();

EVP_PKEY * getEvpPublicKeyByCharArray(unsigned char * publicKeyStr, int pub_key_len){
	X509_PUBKEY  *p = d2i_X509_PUBKEY(NULL, (const unsigned char**)&publicKeyStr, pub_key_len);
	pub_key_len=p->public_key->length;
	//printfOutResult((unsigned char *)p->public_key->data, pub_key_len);
	RSA *rsa = d2i_RSAPublicKey(NULL, (const unsigned char**)&p->public_key->data, p->public_key->length);
	if (rsa == NULL)
	{
		printf("open_public_key failed to d2i_RSAPublicKey!\n");
		RSA_free(rsa);
		return NULL;
	}
	//printf("open_public_key success to d2i_RSAPublicKey!\n");
	EVP_PKEY*  key = EVP_PKEY_new();
	if (NULL == key)
	{
		printf("open_public_key EVP_PKEY_new failed\n");
		RSA_free(rsa);
		return NULL;
	}
	EVP_PKEY_assign_RSA(key, rsa);
	return  key;
}



EVP_PKEY * getEvpPrivateKeyByCharArray(unsigned char * priKeyStr, int pri_key_len){
	/*//Pksr_PUBKEY  *p = d2i_R
	//pub_key_len = p->public_key->length;
	//printfOutResult((unsigned char *)p->public_key->data, pub_key_len);
	RSA *rsa = d2i_RSAPublicKey(NULL, (const unsigned char**)&p->public_key->data, p->public_key->length);
	if (rsa == NULL)
	{
		printf("open_public_key failed to d2i_RSAPublicKey!\n");
		RSA_free(rsa);
		return NULL;
	}
	//printf("open_public_key success to d2i_RSAPublicKey!\n");
	EVP_PKEY*  key = EVP_PKEY_new();
	if (NULL == key)
	{
		printf("open_public_key EVP_PKEY_new failed\n");
		RSA_free(rsa);
		return NULL;
	}
	EVP_PKEY_assign_RSA(key, rsa);
	
	return  key;

	*/
	return NULL;
}





int signatureVerify(unsigned char *signStr, int singStr_len, unsigned char *sign_value, int sign_value_len, EVP_PKEY  *evpKey){
	EVP_MD_CTX  mdctx;   //ժҪ�㷨�����ı���
	int i;
	EVP_MD_CTX_init(&mdctx);  //��ʼ��ժҪ������
	//printf("\n\n ������֤ǩ��, wait  �� ����\n");
	//��������֤����
	int rv = EVP_VerifyInit_ex(&mdctx, EVP_sha1(), NULL);
	if (rv != 1)
	{
		printf("EVP_VerifyInit_ex err \n");
		//EVP_PKEY_free(evpKey);
		return 0;
	}
	rv = EVP_VerifyUpdate(&mdctx, signStr, singStr_len);
	if (rv != 1)
	{
		printf("EVP_VerifyUpdate  err \n");
		//EVP_PKEY_free(evpKey);
		return 0;
	}
	rv = EVP_VerifyFinal(&mdctx, sign_value, sign_value_len, evpKey);
	if (rv != 1)
	{
		printf("EVP_VerifyFinal  err \n");
		//EVP_PKEY_free(evpKey);
		return 0;
	}
	else{
		printf("\n\n ��֤ǩ����ȷ��������  \n\n");
	}
	//EVP_PKEY_free(evpKey);
	EVP_MD_CTX_cleanup(&mdctx);
	return 1;
}


unsigned char *signature(unsigned char *signStr, int singStr_len, int &sign_value_len, EVP_PKEY  *evpKey){
		EVP_MD_CTX  mdctx;   //ժҪ�㷨�����ı���
		EVP_MD_CTX_init(&mdctx);  //��ʼ��ժҪ������
	//	printf("\n\nEVP_SignInit_ex...");
		if (!EVP_SignInit_ex(&mdctx, EVP_sha1(), NULL))
		{
			printf("\nEVP_SignInit_ex err \n");
			//EVP_PKEY_free(evpKey);
			return NULL;
		}
		//printf("\n\nEVP_SignInit_ex...");
		//����ǩ����ժҪ��update
		int rv = EVP_SignUpdate(&mdctx, signStr, singStr_len);
		if (rv!=1)
		{
			printf("EVP_SignUpdate err \n");
			//EVP_PKEY_free(evpKey);
			return 0;
		}
		//printf("\n\nSignUpdate...");
		/* EVP_SignFinal���ã�int EVP_SignFinal(EVP_MD_CTX *ctx,unsigned char *sig,unsigned int *s, EVP_PKEY *pkey);
		����ǩ��ϵ�к�������ϢժҪ������ʼ��ͬ�ĵط�����ʵ���ú����ǽ�ǩ����������ϢժҪ�ṹctx����һ�ݣ�
		Ȼ�����EVP_DigestFinal_ex�����ϢժҪ������Ȼ��ʼ��ժҪ��Ϣ��˽Կpkey����ǩ��,����ǩ����Ϣ�����ڲ���sig���档
		�������s��ΪNULL����ô�ͻὫǩ����Ϣ���ݵĳ��ȣ���λ�ֽڣ������ڸò����У�ͨ��д���������EVP_PKEY_size(key)��
		��Ϊ������ʱ���ǿ�����һ��ctx�����ԣ�ԭ����ctx�ṹ�����Լ���ʹ��EVP_SignUpdate��EVP_SignFinal��������ɸ�����Ϣ��ǩ��������
		���������һ��Ҫʹ��EVP_MD_CTX_cleanup����������ͷ�ctx�ṹ������ͻ�����ڴ�й©��
		*/
		unsigned char * sign_value = (unsigned char *)malloc(0x80+100);
		memset(sign_value, 0, 0x80+100);
	//	printf("\n\nEVP_SignFinal:\n\n");
		rv = EVP_SignFinal(&mdctx, sign_value, (unsigned int *)(&sign_value_len), evpKey);
	//   printf("\n\nsign_value:\n\n");
	//	printfOutResult(sign_value, sign_value_len);
		if (rv != 1)   //ǩ�����
		{
			printf("EVP_SignFinal err \n");
			//EVP_PKEY_free(evpKey);
			return NULL;
		}
		return sign_value;
}




