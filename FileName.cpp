#include <iostream>

int main() {

	//1.)
	int a, b, c;

	_asm{
		add a, eax;
	}

	//2.)
	int b, c;
	_asm {
		//1 megoldas
		mov eax, b;
		mov ebx, c;
		mov b, ebx;
		mov c, eax;

		//2 megoldas
		mov ebx, b;
		mov ecx, c;
		mov b, ecx;
		mov c, ebx;
	}

	//3.)
	int x, y;

	x = x + y;
	y = x - y;
	x = x - y;

	_asm {
		mov eax, x;
		add eax, y;
		mov x, eax;

		sub eax, y;
		mov y, eax;

		sub eax, y;
		mov x, eax;
	}

	//4.)
	int d, e;

	d = d / e;
	_asm {
		mov d, 120;
		mov e, 58;
		
		mov eax, d;
		mov edx, e;

		div d, e;
	}
	
	//5.)
	int f, h;
	_asm {
		sub EDI, EDI;
		and EDI, 0;
		xor EDI, EDI;
		shr EDI, 0;
	}

	//7.)
	_asm {
		sar edx, 19;
	}

	//8.)
	_asm {
		mov al, 255;
		mov ah, 100;
		mul ah;

		mov n, ax;
	}

	//9.)
	int a, b, c;

	_asm{
		mov eax, a;
		add eax, b;
		mov ebx, 10;
		imul ebx;
		mov ebx, 100;
		idiv ebx;
		mov eax, c;
	}

	//10.)
	int a, b, c, C;

	_asm {
		mov eax, c;
		not eax;
		and eax, b;
		or eax, a;
		xor eax, c;
		mov eax, C;
	}
	

	return 0;
}
