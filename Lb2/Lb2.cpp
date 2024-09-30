#include <iostream>
#include <intrin.h>
#include <cmath>
#include <chrono>


using namespace std;


void point2() {
	unsigned __int32 tick32_1, tick32_2, tick32_3, tick32_4; // �������� ���������� ���������� 32 ������.
	unsigned __int64 tick64_1, tick64_2, tick64_3, tick64_4; // �������� ���������� ���������� 64 ������.
	cout << "����� 2" << endl;
	cout << "���������� ������ ���������� � ������� ���������� ������ (��������� ���������� ������) - " << __rdtsc() << endl << endl;
	tick64_1 = __rdtsc(); // ������� __rdtsc() ���������� ���������� ������ ����� � 64 ������ �����.
	tick64_2 = __rdtsc();

	__asm {
		rdtsc				// ���������� rdtsc ��������� ->
		mov tick32_1, EAX	// -> ������� EAX �������� 32 ������ ->
		mov tick32_2, EDX	// -> ������� EDX �������� 32 ������.

		rdtsc
		mov tick32_3, EAX
		mov tick32_4, EDX

		mov EBX, EAX
		mov ECX, EDX

		push EBX  // ���������� ��������� � ����.
		push ECX
	}

	tick64_3 = ((unsigned __int64)tick32_2 << 32) | tick32_1;  // ����������� ���� 32 ������ ����� � ����� 64 ������ ����� ����� ->
	tick64_4 = ((unsigned __int64)tick32_4 << 32) | tick32_3;  // -> c����� ������� ����� �� 32 ���� �����	� �������� ���� ����� ������� ��������� ��� ("|").

	cout << "����� ������ ����������:\n���������� ������ ���������� ����������� � ���������� - " << "tick1 = | " << tick64_1 << " | tick2 = | " << tick64_2 << " |" << endl;
	cout << "���������� ������ ���������� ���������� �� ��������� -  " << "tick3 = | " << tick64_3 << " | tick4 = | " << tick64_4 << " | " << endl;
	cout << "������� �� ��������� - " << "| " << tick64_3 - tick64_1 << " | | " << tick64_4 - tick64_2 << " |" << endl << endl;

	__asm {
		pop EBX  // ���������� ��������� �� �����.
		pop ECX

		mov tick32_3, EBX
		mov tick32_4, ECX
	}

	tick64_3 = tick64_4;
	tick64_4 = ((unsigned __int64)tick32_4 << 32) | tick32_3;

	cout << "���������� �������� ������ ���������� ���������� �� ��������� �� ���������� �� � ���� � ����� ���������� �� ����.\n";
	cout << "tick4 �� = | " << tick64_3 << " |; ����� ���������� �� ����� = | " << tick64_4 << " |" << endl;
	cout << "������� ��������� - " << tick64_3 - tick64_4 << endl;
	cout << "\n---------------------------------------------------------------------------------------------------------------";

}


void point3() {
	unsigned __int32 tick32_1, tick32_2, tick32_3, tick32_4; // �������� ���������� ���������� 32 ������.
	unsigned __int64 tick64_1, tick64_2; // �������� ���������� ���������� 64 ������.
	cout << "\n\n����� 3" << endl;
	for (int i = 0; i < 2; i++) {
		__asm {
			rdtsc
			mov tick32_1, EAX
			mov tick32_2, EDX
			cmp i, 0            // ��������� ����� i � 0 ->
			jg subprogramm		// -> jg - ���� (i > 0) -> "�������" � ����� subprogramm, ����� ���������� ���������� ������������ �������.

			empty_subprogramm :  // ������ ������������.
			jmp nextStep		// "������" � ����� nextStep

				subprogramm :		// ������������ � ������������.
			mov BX, 20
				mov CX, 50
				add BX, 4333
				add CX, 1234567
				mul CX
				sub CX, BX

				nextStep :
			rdtsc
				mov tick32_3, EAX
				mov tick32_4, EDX
		}
		tick64_1 = ((unsigned __int64)tick32_2 << 32) | tick32_1;  // ����������� ���� 32 ������ ����� � ����� 64 ������ ����� ����� ->
		tick64_2 = ((unsigned __int64)tick32_4 << 32) | tick32_3;  // -> c����� ������� ����� �� 32 ���� �����	� �������� ���� ����� ������� ��������� ��� ("|").
		if (i == 0) {
			cout << "���������� ������ ���������� �� ���������� ������ ������������ - | " << tick64_1 << " | " << endl;
			cout << "���������� ������ ���������� ����� ���������� ������ ������������ - | " << tick64_2 << " | " << endl;
		}
		else {
			cout << "���������� ������ ���������� �� ���������� ������������ - | " << tick64_1 << " | " << endl;
			cout << "���������� ������ ���������� ����� ���������� ������������ - | " << tick64_2 << " | " << endl;
		}

	}
	cout << "\n---------------------------------------------------------------------------------------------------------------";
}


long double point4(const int counter, const double FREQ, int flag) {
	unsigned __int32 tick32_1, tick32_2, tick32_3, tick32_4; // �������� ���������� ���������� 32 ������.
	unsigned __int64 tick64_1, tick64_2; // �������� ���������� ���������� 64 ������.
	long double time;
	int i = 0;

	__asm {
		rdtsc				// ���������� rdtsc ��������� ->
		mov tick32_1, EAX	// -> ������� EAX �������� 32 ������ ->
		mov tick32_2, EDX	// -> ������� EDX �������� 32 ������.
	};

	tick64_1 = ((unsigned __int64)tick32_2 << 32) | tick32_1;

	__asm {

		mov ecx, counter  // �������� �������� ���������� � ������� ECX
		xor eax, eax      // ��������� �������� EAX
		cycle_start :
		inc eax           // ���������� �������� � �������� EAX �� 1
			loop cycle_start  // ������� � �����, ���� ECX �� ������ �������
			mov i, eax        // ���������� �������� EAX � ���������� i
			rdtsc				// ���������� rdtsc ��������� ->
			mov tick32_3, EAX	// -> ������� EAX �������� 32 ������ ->
			mov tick32_4, EDX	// -> ������� EDX �������� 32 ������.
	};

	tick64_2 = ((unsigned __int64)tick32_4 << 32) | tick32_3;
	//time = ((tick64_2 - tick64_1) / pow(10, 8)) / FREQ;
	time = ((tick64_2 - tick64_1) * 1000) / FREQ;
	if (flag) {
		unsigned __int64 t = (tick64_2 - tick64_1) / 10 / time;
		return t;
	}
	else return time;
}


void point5(const int counter, const double FREQ) {
	cout << "\n����� 5" << endl;
	auto start = chrono::high_resolution_clock::now();
	unsigned __int64 t = point4(counter, FREQ, 1);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	cout << "���������� �������� = " << counter << endl;
	cout << "����� ���������� �����: " << duration / pow(10, 6) << " �����������" << endl;
	unsigned long long freq = point4(counter, FREQ, 1);
	cout << "i5 1155G7 FREQ ~ " << freq << endl;
}


int main() {
	double FREQ = 2.5e9;
	int counter_1 = pow(10, 2), counter_2 = pow(10, 5), counter_3 = pow(10, 7);
	system("chcp 1251 > nul");

	point2();
	point3();
	cout << "\n\n����� 4, ������� ������ - (10^2)" << endl;
	cout << "����� ����������� �� ���� - " << point4(counter_1, FREQ, 0) << " �����������.";
	cout << "\n����� 4, ������� ������ - (10^5)" << endl;
	cout << "����� ����������� �� ���� - " << point4(counter_2, FREQ, 0) << " �����������.";
	cout << "\n����� 4, ������� ������ - (10^7)" << endl;
	cout << "����� ����������� �� ���� - " << point4(counter_2, FREQ, 0) << " �����������." << endl;
	cout << "\n---------------------------------------------------------------------------------------------------------------\n";
	point5(counter_2, FREQ);

	return 0;
}
