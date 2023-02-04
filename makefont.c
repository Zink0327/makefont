#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp0, *fp1;
	if (argc < 3) 
	{
		puts("usage>makefont source.txt font.bin");
		return 1;
	}
	fp0 = fopen((const char*)argv[1], "rb");
	fp1 = fopen((const char*)argv[2], "wb");
	if (fp0 == NULL) 
	{
		puts("can't open input file.");
		return 2;
	}
	if (fp1 == NULL) 
	{
		puts("can't open output file.");
		return 3;
	}
	/*
	for example:
	char 0x31
	........
	....*...
	...**...
	..*.*...
	....*...
	....*...
	....*...
	....*...
	....*...
	....*...
	....*...
	....*...
	....*...
	..*****.
	........
	........
	*/
	char *buf = NULL;
	*buf = "char font [16][256] = {\n";
	fputs("char font [16][256] = {\n",fp1); /* write array head */
	
	size_t count = 0;
	for(;;)
	{
		fputs("	{");
		/* find 'char' */
		while(1)
		{
			if(fgets(buf, 12, fp0) != NULL && (buf[0] == 'c' && buf[1] == 'h' && buf[2] == 'a' && buf[3] == 'r'))
			{
				break;
			}
		}
		char i, fd, sd, ascii_num[4];
		/* read the font structure */
		for(int c = 0; c < 16; ++c)
		{
			if (fgets(s, 12, fp0) != NULL && (s[0] == '*' || s[0] == '.')) 
			{
				
				i  = (s[0] == '*') << 7;
				i |= (s[1] == '*') << 6;
				i |= (s[2] == '*') << 5;
				i |= (s[3] == '*') << 4;
				i |= (s[4] == '*') << 3;
				i |= (s[5] == '*') << 2;
				i |= (s[6] == '*') << 1;
				i |= (s[7] == '*');
				
				hextoascii(i, fd, sd);
				ascii_num[0] = '0';
				ascii_num[1] = 'x';
				ascii_num[2] = fd;
				ascii_num[3] = sd;
				
				writefile(fp1,ascii_num);
			}
		}
	}
/*	do {
		char s[12];
		int i;
		if (fgets(s, 12, fp0) != NULL && (s[0] == ' ' || s[0] == '*' || s[0] == '.')) {
			i  = (s[0] == '*') << 7;
			i |= (s[1] == '*') << 6;
			i |= (s[2] == '*') << 5;
			i |= (s[3] == '*') << 4;
			i |= (s[4] == '*') << 3;
			i |= (s[5] == '*') << 2;
			i |= (s[6] == '*') << 1;
			i |= (s[7] == '*')     ;
			fputc(i, fp1);
		}
	} while (!feof(fp0));*/
	fputs("};",fp1);
	fclose(fp0);
	fclose(fp1);
	return 0;
}

void hextoascii(char i, char &fd, char &sd)
{
	fd = i%10;
	sd = i/10;

	if(fd <= 0x09 && fd >= 0x00) fd += 0x30;
	else if(fd >= 0x0a && fd <= 0x0f)fd += 0x37;
	else puts("input error");
	if(sd <= 0x09 && sd >= 0x00) sd += 0x30;
	else if(sd >= 0x0a && sd <= 0x0f)sd += 0x37;
	else puts("input error");
}

bool writefile(FILE *fp, void *str)
{
	size_t count = 0;
	for(; count < 1;)
	{
		count += fwrite(str, sizeof(str), 1, fp);
	}
	return true;
}

bool readaline(FILE *fp, char *str)
{
	size_t count = 0;
	char *buf = 0;
	for(int c = 0; buf[c] != '\n'; ++c )
	{
		count += fread(buf, sizeof(char), 1, fp);
	}
}