/******************************************************************
*             ИНФОРМАТИКА И КОМПЬЮТЕРНЫЕ ТЕХНОЛОГИИ               *
*******************************************************************
*                    Лабораторная работа # 3                      *
*******************************************************************
* Project Type :win 32 Console Application                        *
* Project Name :LAB_3_PLHL                                        *
* File Name    :main.c                                            *
* Language     :C MVS 2017                                        *
* Programmers  :Дмитрий Волков, Алексей Толочный                  *
* Group        :М3О-208Б-18                                       *
* Modified by  :Дмитрий Волков                                    *
* Created      :18.10.19                                          *
* Last Revision:19.10.19                                          *
* Comment      : программа выравнивает текст по центру до длины   *
* (N + delta), где N - длина максимальной строки исходного текста *
*                  delta - задается пользователем (>0);           *
* '\t' заменяется на пять пробелов                                *
*******************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int i = 0;				//счетчик
const int NMAX = 100;	//максимальная длина буфера обмена
/******************************************************************/
int dmxline(FILE*);			//определение длины максимальной строки
void cler_str(char*,		//очистка строки
	int,				//индекс, с которого идет очистка
	int);				//индекс, до которого идет очистка
/******************************************************************/
int main()
{
	FILE *input = fopen("C:\\Users\\dmitr\\Desktop\\ПЯВУ\\3 СЕМ\\ЛР_3 ПЯВУ\\LAB_3_PLHL\\LAB_3_PLHL\\data.txt", "rt");
	FILE *output = fopen("C:\\Users\\dmitr\\Desktop\\ПЯВУ\\3 СЕМ\\ЛР_3 ПЯВУ\\LAB_3_PLHL\\LAB_3_PLHL\\res.txt", "wt");
	int N = -1;		//правая граница
	int el = -1;	//индекс конца строки
	int delta = -1;	//переменная задается пользоваетелем (delta > 0)
	char* clp;		//основной буфер обмена
	char* temp;		//временный буфер для выравнивания строки

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

	N = dmxline(input);
	N = N + delta;

	clp = malloc(NMAX);
	temp = malloc(NMAX);

	do 
	{
		fgets(clp, N, input);
		clp = strcat(clp, temp);
		cler_str(temp, 0, strlen(temp));

		//строка по размеру
		if (strlen(clp) == N)
		{
			fputs(clp, output);
		}
		//строка меньше
		else if (strlen(clp) < N)
		{
			if (feof(input) == 0)//если еще не конец файла
				strcat(clp, " ");

			strcat(temp, clp);

			if (feof(input) != 0)//если конец файла
			{
				fputs(temp, output);
				cler_str(temp, 0, strlen(temp));
			}
		}
		//строка больше
		else
		{
			el = strrchr(clp, ' ');
			//el = N;
			//while ((clp[el] != ' ')&&(el != 0))
			//	el--;
			if (el == NULL)
			{
				
				//clp.erase(el, 1);

				//tmpl = clp.substr(el, clp.size());
				if (feof(input) == 0)
					strcat(temp, " ");
				//clp.erase(el, clp.size());

				el = size_str(clp);
				while (el != 0)
					el--;
			}
			else
			{
				el = 0;
				while ((clp[el] != ' ') && (el != size_str(clp)))
					el++;

			}
		}
		cler_str(temp, 0, strlen(temp));

	} while (clp != EOF);

	fclose(input);
	fclose(output);

	system("pause");
	return 0;
}

int dmxline(FILE* in)
{
	int dN = 0;		//правая граница
	int dtemp = 0;	//переменная для сравнения
	char dc = 0;		//переменная для считывания из файла

	while (dc != EOF)
	{
		dtemp = 0;
		dc = 0;
		while ((dc != '\n')&&(dc != EOF))
		{
			dc = fgetc(in);
			dtemp++;
			if ((dc == '\n')||(dc == EOF))
				dtemp++;
		}
		if(dtemp > dN)
			dN = dtemp;
	}
	return dN;
}

//void cler_str(char *cArr, int cB, int cE)
//{
//	if (cE != cB)
//	{
//		for (i = cB; i < cE; i++)
//		{
//			cArr[i] = '\0';									
//		}
//	}
//	else
//	{
//		for (i = cB; i < strlen(cArr); i++)
//		{
//			cArr[i] = cArr[i++];
//		}
//	}
//}