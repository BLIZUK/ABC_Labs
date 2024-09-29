//	������ ��������� ����������� ��������� ����������

//#include "stdafx.h"	// precompiled header
#include <iostream>	// ����������� ������������ ������������ ���� ��� ������ � �������� �����-������ (input-output streams)
#include <cstring>

using namespace std;

struct nameReg {
	char Name[4];
};


int main()
{
	system("chcp 1251 > nul");
	int	RegCPU[8]; // ���������� ������� (�������) �� ������ ������������� ���������� �� 4-� ����� 
	nameReg* nameRegs = new nameReg[8];


	strcpy_s(nameRegs[0].Name, "EAX");
	strcpy_s(nameRegs[1].Name, "EBX");
	strcpy_s(nameRegs[2].Name, "ECX");
	strcpy_s(nameRegs[3].Name, "EDX");
	strcpy_s(nameRegs[4].Name, "ESI");
	strcpy_s(nameRegs[5].Name, "EDI");
	strcpy_s(nameRegs[6].Name, "EBP");
	strcpy_s(nameRegs[7].Name, "ESP");


	//cout << "    EAX      " << "    EBX      " << "    ECX      "  << endl;	// ��������� ��� ������������ ������

	for (int i = 0; i < 8; i++) {
		cout << "     " << nameRegs[i].Name << "      ";
	}
	cout << endl;

	_asm {
		mov RegCPU, EAX	// ������ � RegCPU[0]
		mov RegCPU + 4, EBX 	// ������ � RegCPU[1] (�������� +4)
		mov RegCPU + 8, ECX     // ������ � regCPU[2] � �������� +8, �.�.�.
		mov RegCPU + 12, EDX
		mov RegCPU + 16, ESI
		mov RegCPU + 20, EDI
		mov RegCPU + 24, EBP
		mov RegCPU + 28, ESP

	};


	//cout << RegCPU[0] << "   " << RegCPU[1] << "   " << RegCPU[2] << endl;	// ����� (�� ���������) � ���������� �����
	for (int i = 0; i < 8; i++) {
		cout << " " << RegCPU[i] << "     ";
	}
	cout << endl;

	//cout << hex << "  " << RegCPU[0] << "     " << RegCPU[1] << "    " << RegCPU[2];	// ����� � ����������������� �����
	for (int i = 0; i < 8; i++) {
		cout << hex << "   " << RegCPU[i] << "    ";
	}
	cout << endl;
	// ���������� ������ � ����������������� �����.

	int x = 2;
	cout << "����� ���������� x = ";
	cin >> x;

	__asm {
		add x, 5
	}

	cout << dec << "����� ��������� x = " << x << endl;

	//cout << RegCPU[0] << "   " << RegCPU[1] << "   " << RegCPU[2] << endl;	// ����� (�� ���������) � ���������� �����
	for (int i = 0; i < 8; i++) {
		cout << " " << RegCPU[i] << "     ";
	}
	cout << endl;

	//cout << hex << "  " << RegCPU[0] << "     " << RegCPU[1] << "    " << RegCPU[2];	// ����� � ����������������� �����
	for (int i = 0; i < 8; i++) {
		cout << hex << "   " << RegCPU[i] << "    ";
	}
	cout << endl;
	// ���������� ������ � ����������������� �����.

	__asm {
		add EAX, x
		mov RegCPU, EAX
	}

	cout << dec << "EAX + x = " << RegCPU[0] << endl;
	delete[] nameRegs;

	cin.get();
	return 0;
}
