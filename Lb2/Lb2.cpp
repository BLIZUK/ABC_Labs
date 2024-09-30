#include <iostream>
#include <intrin.h>
#include <cmath>
#include <chrono>


using namespace std;


void point2() {
	unsigned __int32 tick32_1, tick32_2, tick32_3, tick32_4; // Создание переменных безнаковых 32 битных.
	unsigned __int64 tick64_1, tick64_2, tick64_3, tick64_4; // Создание переменных безнаковых 64 битных.
	cout << "Пункт 2" << endl;
	cout << "Количество тактов процессора с момента последнего сброса (Начальное количество тактов) - " << __rdtsc() << endl << endl;
	tick64_1 = __rdtsc(); // Функция __rdtsc() возвращает количество тактов сразу в 64 битном числе.
	tick64_2 = __rdtsc();

	__asm {
		rdtsc				// Инструкция rdtsc заполняет ->
		mov tick32_1, EAX	// -> регистр EAX младшеми 32 битами ->
		mov tick32_2, EDX	// -> регистр EDX старшеми 32 битами.

		rdtsc
		mov tick32_3, EAX
		mov tick32_4, EDX

		mov EBX, EAX
		mov ECX, EDX

		push EBX  // Сохранение регистров в стек.
		push ECX
	}

	tick64_3 = ((unsigned __int64)tick32_2 << 32) | tick32_1;  // Обьединение двух 32 битных чисел в ондно 64 битное число путем ->
	tick64_4 = ((unsigned __int64)tick32_4 << 32) | tick32_3;  // -> cдвига второго числа на 32 бита влево	и слиянием двух чисел битовой операцией или ("|").

	cout << "Вывод тактов процессора:\nКоличество тактов процессора сохраненные в переменных - " << "tick1 = | " << tick64_1 << " | tick2 = | " << tick64_2 << " |" << endl;
	cout << "Количество тактов процессора полученных из регистров -  " << "tick3 = | " << tick64_3 << " | tick4 = | " << tick64_4 << " | " << endl;
	cout << "Разница их составила - " << "| " << tick64_3 - tick64_1 << " | | " << tick64_4 - tick64_2 << " |" << endl << endl;

	__asm {
		pop EBX  // Извлечение регистров из стека.
		pop ECX

		mov tick32_3, EBX
		mov tick32_4, ECX
	}

	tick64_3 = tick64_4;
	tick64_4 = ((unsigned __int64)tick32_4 << 32) | tick32_3;

	cout << "Рассмотрим значение тактов процессора полученных из регистров до сохранения их в стек и после извлечения из него.\n";
	cout << "tick4 до = | " << tick64_3 << " |; после извлечения из стека = | " << tick64_4 << " |" << endl;
	cout << "Разница составила - " << tick64_3 - tick64_4 << endl;
	cout << "\n---------------------------------------------------------------------------------------------------------------";

}


void point3() {
	unsigned __int32 tick32_1, tick32_2, tick32_3, tick32_4; // Создание переменных безнаковых 32 битных.
	unsigned __int64 tick64_1, tick64_2; // Создание переменных безнаковых 64 битных.
	cout << "\n\nПункт 3" << endl;
	for (int i = 0; i < 2; i++) {
		__asm {
			rdtsc
			mov tick32_1, EAX
			mov tick32_2, EDX
			cmp i, 0            // Сравнение чисел i и 0 ->
			jg subprogramm		// -> jg - если (i > 0) -> "прыгаем" в метку subprogramm, иначе продолжаем выполнение ассемблерной вставки.

			empty_subprogramm :  // Пустая подпрограмма.
			jmp nextStep		// "Прыжок" в метку nextStep

				subprogramm :		// Подпрограмма с вычислениями.
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
		tick64_1 = ((unsigned __int64)tick32_2 << 32) | tick32_1;  // Обьединение двух 32 битных чисел в ондно 64 битное число путем ->
		tick64_2 = ((unsigned __int64)tick32_4 << 32) | tick32_3;  // -> cдвига второго числа на 32 бита влево	и слиянием двух чисел битовой операцией или ("|").
		if (i == 0) {
			cout << "Количество тактов процессора до выполнения пустой подпрограммы - | " << tick64_1 << " | " << endl;
			cout << "Количество тактов процессора после выполнения пустой подпрограммы - | " << tick64_2 << " | " << endl;
		}
		else {
			cout << "Количество тактов процессора до выполнения подпрограммы - | " << tick64_1 << " | " << endl;
			cout << "Количество тактов процессора после выполнения подпрограммы - | " << tick64_2 << " | " << endl;
		}

	}
	cout << "\n---------------------------------------------------------------------------------------------------------------";
}


long double point4(const int counter, const double FREQ, int flag) {
	unsigned __int32 tick32_1, tick32_2, tick32_3, tick32_4; // Создание переменных безнаковых 32 битных.
	unsigned __int64 tick64_1, tick64_2; // Создание переменных безнаковых 64 битных.
	long double time;
	int i = 0;

	__asm {
		rdtsc				// Инструкция rdtsc заполняет ->
		mov tick32_1, EAX	// -> регистр EAX младшеми 32 битами ->
		mov tick32_2, EDX	// -> регистр EDX старшеми 32 битами.
	};

	tick64_1 = ((unsigned __int64)tick32_2 << 32) | tick32_1;

	__asm {

		mov ecx, counter  // Загрузка значения переменной в регистр ECX
		xor eax, eax      // Обнуление регистра EAX
		cycle_start :
		inc eax           // Увеличение значения в регистре EAX на 1
			loop cycle_start  // Переход к метке, пока ECX не станет нулевым
			mov i, eax        // Сохранение значения EAX в переменную i
			rdtsc				// Инструкция rdtsc заполняет ->
			mov tick32_3, EAX	// -> регистр EAX младшеми 32 битами ->
			mov tick32_4, EDX	// -> регистр EDX старшеми 32 битами.
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
	cout << "\nПункт 5" << endl;
	auto start = chrono::high_resolution_clock::now();
	unsigned __int64 t = point4(counter, FREQ, 1);
	auto end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	cout << "Количество итераций = " << counter << endl;
	cout << "Время выполнения цикла: " << duration / pow(10, 6) << " миллисекунд" << endl;
	unsigned long long freq = point4(counter, FREQ, 1);
	cout << "i5 1155G7 FREQ ~ " << freq << endl;
}


int main() {
	double FREQ = 2.5e9;
	int counter_1 = pow(10, 2), counter_2 = pow(10, 5), counter_3 = pow(10, 7);
	system("chcp 1251 > nul");

	point2();
	point3();
	cout << "\n\nПункт 4, счетчик циклов - (10^2)" << endl;
	cout << "Время затраченное на цикл - " << point4(counter_1, FREQ, 0) << " миллисекунд.";
	cout << "\nПункт 4, счетчик циклов - (10^5)" << endl;
	cout << "Время затраченное на цикл - " << point4(counter_2, FREQ, 0) << " миллисекунд.";
	cout << "\nПункт 4, счетчик циклов - (10^7)" << endl;
	cout << "Время затраченное на цикл - " << point4(counter_2, FREQ, 0) << " миллисекунд." << endl;
	cout << "\n---------------------------------------------------------------------------------------------------------------\n";
	point5(counter_2, FREQ);

	return 0;
}
