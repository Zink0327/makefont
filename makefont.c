/*----------Makefont main function----------
Copyright (C) 2023 by Zink
Makefont is free software; you can redistribute it and/or modify it 
under the MIT license; either this version, or (at your option) any
later version. See the MIT license for more details.
This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
or FITNESS FOR A PARTICULAR PURPOSE.
some basic information :
Version : 1.1
Complier : GNU GCC Compiler
*/

#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *fp0, *fp1;
	if (argc < 3) {
		puts("usage>makefont source.txt font.bin");
		return 1;
	}
	fp0 = fopen(argv[1], "rb");
	fp1 = fopen(argv[2], "wb");
	if (fp0 == NULL) {
		puts("can't open input file.");
		return 2;
	}
	if (fp1 == NULL) {
		puts("can't open output file.");
		return 3;
	}
	int counter = 0, count = 0;
	fprintf(fp1,"unsigned char font[256][16] = {\n");
	fprintf(fp1,"   {");
	do {
	   	if(counter >= 16)
            	{
               	 fprintf(fp1,"\n");
               	 counter = 0;
               	 if(count <= 255)
               	 {
       	 		fprintf(fp1,"   {");
               	 }
          	}

		char s[12];
		int i;
		if (fgets(s, 12, fp0) != NULL && (s[0] == '*' || s[0] == '.')) {
			i  = (s[0] == '*') << 7;
			i |= (s[1] == '*') << 6;
			i |= (s[2] == '*') << 5;
			i |= (s[3] == '*') << 4;
			i |= (s[4] == '*') << 3;
			i |= (s[5] == '*') << 2;
			i |= (s[6] == '*') << 1;
			i |= (s[7] == '*')     ;

			if(counter >= 15)
			{
             	  	 fprintf(fp1,"0x%02x",i);
             	  	 if(count >= 255)
            	   	 {
                   		 fprintf(fp1,"} /* 0x%02x */", count);
            	  	  }
             	   	else
             	  	 {
              	      		fprintf(fp1,"}, /* 0x%02x */", count);
               		 }
             	   count++;
           	 }
          	  else
            	{
             	   fprintf(fp1,"0x%02x,",i);
          	  }
         	   counter = counter + 1;

		}


	} while (!feof(fp0));
	fprintf(fp1,"};");
	fclose(fp0);
	fclose(fp1);
	return 0;
}
