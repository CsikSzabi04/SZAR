#include <iostream>
#include <stdlib.h>
#include <time.h>

int main() {
	srand(time(NULL));
	int t[10];
	int min, max;

	const char* fmtMin = "Adja meg a min erteket: ";
	const char* fmtMax = "Adja meg a max erteket: ";
	const char* fmtIntRead = "%d";
	_asm {
		CIKLUS_DO:
			mov esi, esp;

			//printf("Adja meg a min erteket: ");
			//scanf_s("%d", &min);
			push fmtMin;
			call dword ptr printf;

			lea eax, min;  //&min értékét tárolja az eax-ben
			push eax;
			push fmtIntRead;
			call dword ptr scanf;

			//printf("Adja meg a max erteket: ");
			//scanf_s("%d", &max);
			push fmtMax;
			call dword ptr printf;

			lea eax, max;  //&max értékét tárolja az eax-ben
			push eax;
			push fmtIntRead;
			call dword ptr scanf;

			mov esp, esi;

			//Do-nak While része //while(max <=min || min < 10 || min > 1000 || max < 10 || max > 1000);
			mov eax, max;
			cmp eax, min;
			jle CIKLUS_DO;
			cmp min, 1;
			jl CIKLUS_DO;
			cmp min, 1000;
			jg CIKLUS_DO;
			cmp max, 1;
			jl CIKLUS_DO;
			cmp max, 1000;
			jg CIKLUS_DO;
	}

	//for (int i = 10; i > 0; i--) t[10-i] = rand() % (max - min + 1) + min;
	_asm {
		mov ecx, 10;       // int i = 10;
		mov edi, 0;
		CIKLUS_PUSH:
			rdrand eax;    //random számot generál
			mov ebx, max;  //ebx = max;
			sub ebx, min;  // (max - min)
			inc ebx;       // (max-min+1)
			mov edx, 0;
			idiv ebx;      // edx = %(max-min+1);
			add edx, min;  // edx + min

			mov t[edi], edx;
			add edi, 4;

		loop CIKLUS_PUSH;
	}

	//for (int i = 10; i > 0; i--) printf("%d\t", t[10 - i]);
	const char* fmtIntPrint = "%d\t";
	_asm {
		mov ecx, 10;       // int i = 10;
		mov edi, 0;
		CIKLUS_PRINT:
			push ecx;
			mov esi, esp;

			push t[edi];
			push fmtIntPrint;
			call dword ptr printf;

			add edi, 4;

			mov esp, esi;
			pop ecx;
		loop CIKLUS_PRINT;
	}

	return 0;
}