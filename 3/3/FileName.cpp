#include <iostream>

int main() {
	/*
	int a; // => 4B = 32bit, -2milliárd ... +2 milliárd
	unsigned int a; //4bit=32bit, 0 ... 4milliárd
	*/
	_asm {
		mov eax, 0;
		mov al, 120;
		mov ah, 135;
		add al, ah;
		add ax, bx;
	}

	/*
	char  1B :  
	short 2B :
	int   4B :
	long  8B :
	*/

	return 0;
}