// crytion.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
#include <string.h>

#define MAXLEN 1024

//异或混淆
char* encrypt(char* source, int pass)
{
	int source_length = strlen(source);

	char* tmp_str = (char*)malloc((source_length + 1) * sizeof(char));
	memset(tmp_str, 0, source_length + 1);

	for (int i = 0; i < source_length; ++i)
	{
		tmp_str[i] = source[i]^pass;
		if (tmp_str[i] == 0)              // 要考虑到XOR等于0的情况，如果等于0，就相当
		{                                // 于字符串就提前结束了， 这是不可以的。
			tmp_str[i] = source[i];      // 因此tmp_str[i]等于0的时候，保持原文不变
		}
	}
	tmp_str[source_length] = 0;

	return tmp_str;
}

//取反混淆
char* encrypt1(char* source)
{
	int source_length = strlen(source);

	char* tmp_str = (char*)malloc((source_length + 1) * sizeof(char));
	memset(tmp_str, 0, source_length + 1);

	for (int i = 0; i < source_length; ++i)
	{
		tmp_str[i] = ~source[i];
	}
	tmp_str[source_length] = 0;

	return tmp_str;
}



int main(int argc, char* argv[])
{
	//char* s = "There is a kind of hush all over the world tonight...";
	//char* pass = "hello";

	//char* encrypted_text = encrypt(s, pass);
	//printf("Encrypted text is:\n%s\n", encrypted_text);

	//char* decrypted_text = encrypt(encrypted_text, pass);
	//printf("Decrypted text is:\n%s\n", decrypted_text);

	//free(encrypted_text);
	//free(decrypted_text);

	//getchar();
	int type = 0;
	if (argc < 3)
	{
		printf("usage: %s %s/n", argv[0], "infile outfile");
		exit(1);
	}
	int key = 16;
	if (argc >= 4){
		type = atoi(argv[3]);
	}
	FILE * outfile, *infile;
	outfile = fopen(argv[2], "wb");
	infile = fopen(argv[1], "rb");
	char buf[MAXLEN];

	if (infile == NULL)
	{
		printf("%s, %s", argv[1], "not exit/n");
		exit(1);
	}

	int rc;
	while ((rc = fread(buf, 1, MAXLEN, infile)) != 0)
	{
		char tmp[MAXLEN];
		if (type > 0){
			strcpy(tmp,encrypt(buf, key));
		}
		else{
			strcpy(tmp, encrypt1(buf));
		}
		fwrite(tmp, 1, rc, outfile);
	}
	//int count;
	//while (!feof(infile))
	//{
	//	count = fread(buf, 1, 1024, infile);
	//	for (int i = 0; i <count; i++)
	//		buf[i] = ~buf[i];
	//	fwrite(buf, 1, count, outfile);
	//}
	fclose(infile);
	fclose(outfile);
	//system("PAUSE");
	return 0;
}

