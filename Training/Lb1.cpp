//	Пример программа отображения регистров процессора

//#include "stdafx.h"	// precompiled header
#include <iostream>	// стандартный библиотечный заголовочный файл для работы с потоками ввода-вывода (input-output streams)
#include <cstring>

using namespace std;

struct nameReg {
	char Name[4];
};


int main()
{
	system("chcp 1251 > nul");
	int	RegCPU[8]; // объявление вектора (массива) на восемь целочесленных переменных по 4-е байта 
	nameReg* nameRegs = new nameReg[8];


	strcpy_s(nameRegs[0].Name, "EAX");
	strcpy_s(nameRegs[1].Name, "EBX");
	strcpy_s(nameRegs[2].Name, "ECX");
	strcpy_s(nameRegs[3].Name, "EDX");
	strcpy_s(nameRegs[4].Name, "ESI");
	strcpy_s(nameRegs[5].Name, "EDI");
	strcpy_s(nameRegs[6].Name, "EBP");
	strcpy_s(nameRegs[7].Name, "ESP");


	//cout << "    EAX      " << "    EBX      " << "    ECX      "  << endl;	// заголовок для последующего вывода

	for (int i = 0; i < 8; i++) {
		cout << "     " << nameRegs[i].Name << "      ";
	}
	cout << endl;

	_asm {
		mov RegCPU, EAX	// запись в RegCPU[0]
		mov RegCPU + 4, EBX 	// запись в RegCPU[1] (смещение +4)
		mov RegCPU + 8, ECX     // запись в regCPU[2] – смещение +8, и.т.д.
		mov RegCPU + 12, EDX
		mov RegCPU + 16, ESI
		mov RegCPU + 20, EDI
		mov RegCPU + 24, EBP
		mov RegCPU + 28, ESP

	};


	//cout << RegCPU[0] << "   " << RegCPU[1] << "   " << RegCPU[2] << endl;	// вывод (по умолчанию) в десятичной форме
	for (int i = 0; i < 8; i++) {
		cout << " " << RegCPU[i] << "     ";
	}
	cout << endl;

	//cout << hex << "  " << RegCPU[0] << "     " << RegCPU[1] << "    " << RegCPU[2];	// вывод в шестнадцатеричной форме
	for (int i = 0; i < 8; i++) {
		cout << hex << "   " << RegCPU[i] << "    ";
	}
	cout << endl;
	// Достаточно вывода в шестнадцатеричной форме.

	int x = 2;
	cout << "Введи переменную x = ";
	cin >> x;

	__asm {
		add x, 5
	}

	cout << dec << "Псоле сложениея x = " << x << endl;

	//cout << RegCPU[0] << "   " << RegCPU[1] << "   " << RegCPU[2] << endl;	// вывод (по умолчанию) в десятичной форме
	for (int i = 0; i < 8; i++) {
		cout << " " << RegCPU[i] << "     ";
	}
	cout << endl;

	//cout << hex << "  " << RegCPU[0] << "     " << RegCPU[1] << "    " << RegCPU[2];	// вывод в шестнадцатеричной форме
	for (int i = 0; i < 8; i++) {
		cout << hex << "   " << RegCPU[i] << "    ";
	}
	cout << endl;
	// Достаточно вывода в шестнадцатеричной форме.

	__asm {
		add EAX, x
		mov RegCPU, EAX
	}

	cout << dec << "EAX + x = " << RegCPU[0] << endl;
	delete[] nameRegs;

	cin.get();
	return 0;
}
