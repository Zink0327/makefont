/*----------Makefont main function----------
Copyright (C) 2023 by Zink
Makefont is free software; you can redistribute it and/or modify it under the MIT license; either this version, or (at your option) any later version. See the MIT license for more details.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
some basic information :
Version : 1.1
Complier : GNU GCC Compiler
*/

#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp0, *fp1;
	if (argc < 3) 
	{
		puts("usage:makefont source.txt font.h");
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
	char *buf = NULL, *num = NULL;
	fputs("char font [256][16] = {\n",fp1); /* write array head */
	

	for(int b = 0; b < 255; ++b)
	{
		fputs("	{", fp1);
		/* find 'char' */
		while(1)
		{
			if(fgets(buf, 12, fp0) != NULL && (buf[0] == 'c' && buf[1] == 'h' && buf[2] == 'a' && buf[3] == 'r'))
			{
				num[0]=buf[5];
				num[1]=buf[6];
				num[2]=buf[7];
				num[3]=buf[8];
				break;
			}
		}
		char i, fd, sd, ascii_num[4];

		/* read the font structure, and write them into the c array */

		if (fgets(buf, 12, fp0) != NULL && (buf[0] == '*' || buf[0] == '.')) 
		{
				
			i  = (buf[0] == '*') << 7;
			i |= (buf[1] == '*') << 6;
			i |= (buf[2] == '*') << 5;
			i |= (buf[3] == '*') << 4;
			i |= (buf[4] == '*') << 3;
			i |= (buf[5] == '*') << 2;
			i |= (buf[6] == '*') << 1;
			i |= (buf[7] == '*');
				
			fprintf(fp1, "0x%x", i);
		}

		for(int c = 0; c < 15; ++c)
		{
			if (fgets(buf, 12, fp0) != NULL && (buf[0] == '*' || buf[0] == '.')) 
			{
				fputs(", ",fp1);
				i  = (buf[0] == '*') << 7;
				i |= (buf[1] == '*') << 6;
				i |= (buf[2] == '*') << 5;
				i |= (buf[3] == '*') << 4;
				i |= (buf[4] == '*') << 3;
				i |= (buf[5] == '*') << 2;
				i |= (buf[6] == '*') << 1;
				i |= (buf[7] == '*');
				
				fprintf(fp1, "0x%x", i);
			}
		}

		fputs(" }, ", fp1);
		fputs("/*", fp1);
		fputs(num, fp1);
		fputs("*/ \n", fp1);
	}	

	fputs("	{", fp1);
	/* find 'char' */
	while(1)
	{
		if(fgets(buf, 12, fp0) != NULL && (buf[0] == 'c' && buf[1] == 'h' && buf[2] == 'a' && buf[3] == 'r'))
		{
			num[0]=buf[5];
			num[1]=buf[6];
			num[2]=buf[7];
			break;
		}
	}
	char i, fd, sd, ascii_num[4];

	/* read the font structure, and write them into the c array */

	if (fgets(buf, 12, fp0) != NULL && (buf[0] == '*' || buf[0] == '.')) 
	{
				
		i  = (buf[0] == '*') << 7;
		i |= (buf[1] == '*') << 6;
		i |= (buf[2] == '*') << 5;
		i |= (buf[3] == '*') << 4;
		i |= (buf[4] == '*') << 3;
		i |= (buf[5] == '*') << 2;
		i |= (buf[6] == '*') << 1;
		i |= (buf[7] == '*');
				
		fprintf(fp1, "0x%x", i);
	}

	for(int c = 0; c < 15; ++c)
	{
		if (fgets(buf, 12, fp0) != NULL && (buf[0] == '*' || buf[0] == '.')) 
		{
			fputs(", ",fp1);
			i  = (buf[0] == '*') << 7;
			i |= (buf[1] == '*') << 6;
			i |= (buf[2] == '*') << 5;
			i |= (buf[3] == '*') << 4;
			i |= (buf[4] == '*') << 3;
			i |= (buf[5] == '*') << 2;
			i |= (buf[6] == '*') << 1;
			i |= (buf[7] == '*');
				
			fprintf(fp1, "0x%x", i);
		}
	}

	fputs(" } ", fp1);

	fputs("/*", fp1);
	fputs(num, fp1);
	fputs("*/ \n", fp1);
	fputs("};",fp1);
	fclose(fp0);
	fclose(fp1);
	return 0;
}
