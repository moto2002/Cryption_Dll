// crytion.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include <iostream>
#include <string.h>

#define MAXLEN 1024

//������
char* encrypt(char* source, int pass)
{
	int source_length = strlen(source);

	char* tmp_str = (char*)malloc((source_length + 1) * sizeof(char));
	memset(tmp_str, 0, source_length + 1);

	for (int i = 0; i < source_length; ++i)
	{
		tmp_str[i] = source[i]^pass;
		if (tmp_str[i] == 0)              // Ҫ���ǵ�XOR����0��������������0�����൱
		{                                // ���ַ�������ǰ�����ˣ� ���ǲ����Եġ�
			tmp_str[i] = source[i];      // ���tmp_str[i]����0��ʱ�򣬱���ԭ�Ĳ���
		}
	}
	tmp_str[source_length] = 0;

	return tmp_str;
}

//ȡ������
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

