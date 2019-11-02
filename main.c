/******************************************************************
*               Informatics & Computer Technologies               *
*******************************************************************
*                           LAB # 3                               *
*******************************************************************
* Project Type :win 32 Console Application                        *
* Project Name :LAB_3_PLHL                                        *
* File Name    :main.c                                            *
* Language     :C MVS 2017                                        *
* Programmers  :Dmitry Volkov, Alexey Tolochny                    *
* Group        :M3O-208B-18                                       *
* Modified by  :Dmitry Volkov                                     *
* Created      :18.10.19                                          *
* Last Revision:31.10.19                                          *
* Comment      : the program centers text, (N + delta) - size of modified string  *
*                  N - length of max string in sourse txt         *
*                  delta - setting by user (>0);                  *
*                  '\t' replased by 5 spaces                      *
*******************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>

int i = 0;	//counter
/*************************** prototypes ***************************/
//determine of max line
int dmxline(FILE* in)
{
	int dN = 0;		//right border
	int dtemp = 0;	//var for compare
	char dc = 0;	//var for reading from the file

	while (!feof(in))
	{
		dtemp = 0;
		dc = 0;

		while ((dc != '\n') && (!feof(in)))
		{
			dc = fgetc(in);
			if (dc == '\t')	dtemp += 5;
			dtemp++;
		}
		dtemp--;
		if (dtemp > dN)	dN = dtemp;
	}
	return dN;
}
//cleaning of char*
void cler_line(char* cArr, int cN)
{
	for (i = 0; i < cN; i++) cArr[i] = '\0';
}
//put spaces into char*
void put_sp(char* pArr, int pN)
{
	for (i = 0; i < pN; i++) pArr[i] = ' ';
}
//swap \t into spaces
void sw_tab(char* sArr)
{
	int g;
	int ei = 0;
	int tabi = 0;
	int end_of_search = 0;
	while (end_of_search != 1)
	{
		while (sArr[ei + 1] != '\0') ei++;
		while ((sArr[tabi] != '\t') && (sArr[tabi] != '\0')) tabi++;
		if (tabi > ei) end_of_search = 1;
		for (int i = ei; i > tabi; i--) sArr[i + 4] = sArr[i];
		if (end_of_search != 1)
		{
			g = tabi;
			for (int i = 0; i < 5; i++)
			{
				sArr[g] = ' ';
				g++;
			}
		}
	}
}
/**************************** main() ******************************/
int main()
{
	setlocale(LC_ALL, "rus");
	FILE *input = fopen("C:\\Users\\dmitr\\Desktop\\ÏßÂÓ\\3 ÑÅÌ\\ËÐ_3 ÏßÂÓ\\LAB_3 PLHL\\LAB_3 PLHL\\data.txt", "rt");

	char* clp;		//clipboard
	char* spaces;	//
	int N;			//size of clp 
	int delta = 5;	//
	int numsp;		//number of spaces

	if (input == NULL)
	{
		printf("ERROR_1: file not found");
		system("pause");
		return 1;
	}
	if (fgetc(input) == EOF)
	{
		printf("ERROR_2: file is empty");
		system("pause");
		return 2;
	}

	printf("Add the delta: ");
	scanf("%i", &delta);
	printf("delta = %i\n", delta);
	if (delta <= 0)
	{
		printf("ERROR_3: delta must be > 0\n");
		system("pause");
		return 3;
	}
	if (delta == 1) delta++;
	rewind(input);

	N = dmxline(input);
	N = N + delta;
	rewind(input);

	clp = malloc(N);
	spaces = malloc(N);
	do
	{
		cler_line(clp, N);
		cler_line(spaces, N);

		fgets(clp, N, input);
		sw_tab(clp);
		if (!feof(input))
			for (i = 0; i < N; i++)
				if (clp[i] == '\n')
					clp[i] = '\0';

		numsp = N - strlen(clp);
		numsp = numsp / 2;
		if (numsp != 0)
		{
			put_sp(spaces, numsp);
			printf("%s", spaces);
			printf("%s", clp);
			printf("%s\n", spaces);
		}
		else printf("%s", clp);
	} while (!feof(input));
	fclose(input);

	system("pause");
	return 0;
}
/*************************** end of main() ************************/