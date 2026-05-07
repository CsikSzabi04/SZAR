/*
1. Cseréljen fel két változót a verem segítségével
2. Adjon össze két számot az FPU segítségével!
3. Számolja ki egy másodrendû függvény determinánsát! (2p)
4. Írjon ki a képernyõre egy char értéket! (2p)
5. Kérjen be a képernyõrõl egy int értéket! (2p)
6. Adjon össze egy double és egy int értéket!
7. Képezze az eax gyökét!

8. Kérjen be egy értéket (N, N legen [1;100] intervallumban). Ez lesz az elemek darabszáma;
Kérjen be további két értéket (min és max), ahol
 - min < max
 - min, max [50;1000] intervallumban vannak
Töltsön fel egy tömböt a megadott (N) darabszámú véletlen számmal min és max között.
Ezután adja meg a számsor szórását!1. Cseréljen fel két változót a verem segítségével
2. Adjon össze két számot az FPU segítségével!
3. Számolja ki egy másodrendû függvény determinánsát! (2p)
4. Írjon ki a képernyõre egy char értéket! (2p)
5. Kérjen be a képernyõrõl egy int értéket! (2p)
6. Adjon össze egy double és egy int értéket!
7. Képezze az eax gyökét!

8. Kérjen be egy értéket (N, N legen [1;100] intervallumban). Ez lesz az elemek darabszáma;
Kérjen be további két értéket (min és max), ahol
 - min < max
 - min, max [50;1000] intervallumban vannak
Töltsön fel egy tömböt a megadott (N) darabszámú véletlen számmal min és max között.
Ezután adja meg a számsor szórását!
*/


#include <iostream>

int main() {
	//1
	int a1, b1;
	_asm {
		push a1;
		push b1;
		pop a1;
		pop b1;
	}

	//2
	double a2, b2;
	_asm {
		fld a2;
		fld b2;
		fadd;
	}

	//3
	int aa3, b3, c3;
	int _4 = 4;
	double resutls;
	_asm {
		fild b3;
		fild b3;
		fmul;
		fild _4;
		fild a3;
		fmul;
		fild c3;
		fmul;
		fsub;
		fsqrt;
		fstp results;
	}

	//4
	char a4;
	const char* fmt_char = "%c";
	_asm {
		push a4;
		push fmt_chat;
		call dword ptr printf;
		pop a4;
	}

	//5
	int a5;
	const char* fmt_int = "%d";
	_asm {
		lea eax, a5;
		push eax, a5;
		push eax;
		push fmt_int;
		call dword ptr scanf;
		mov esp, esi;
	}

	//6
	int a6;
	double b6;
	_asm {
		fild a6;
		fld b6;
		fadd;
	}

	//7
	int a7;
	_asm {
		mov a7, eax;
		fild a7; //cast int to double (3.0 pl)
		fsqrt;
	}

	//8 nagy feladat
	int N, min, max;
	int t[100];

	//8.1 printf("N="); scanf_s("%d", &N);
	const char* fmt_N = "N=";
	const char* fmt_read_int = "%d";
	_asm {
		mov esi, esp;

		push fmt_N;
		call dword ptr printf;

		lea eax, N;
		push eax;
		push fmt_read_int;
		call dword ptr scanf;

		mov esp, esi;
	}


	do {
		printf("min="); scanf_s("%d", &min);
		printf("max="); scanf_s("%d", &max);
	} while (max <= min || min < 50 || min > 1000 || max < 50 || max >1000);

	for (int i = 0; i < N; i++) t[i] = rand() % (max - min + 1) + min;

	double atl = 0;
	for (int i = 0; i < N; i++) atl += t[i];
	atl = atl / N;

	double sum = 0;
	for (int i = 0; i < N; i++) sum += (t[i] - atl) * (t[i] - atl);
	double var =sqrt(sum/N);
	
	printf("Szoras: %lf", var);

	return 0;
}