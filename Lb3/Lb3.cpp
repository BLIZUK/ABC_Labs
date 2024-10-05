#include <iostream>
// Некий ужас


using namespace std;



void step4() {
    cout <<"Пункт 4\nРазработать программу на ассемблере, которая считывает адреса переменных С++ и отображает их на экране.\nПродумать вывод адресов и переменных в удобной системе счисления (dec, hex и пр.)\nРешение\n" << endl;
    char a, b, c;
    unsigned addr_a, addr_b, addr_c;

    __asm {
        lea eax, a;
        mov addr_a, eax;
        lea eax, b;
        mov addr_b, eax;
        lea eax, c;
        mov addr_c, eax;
    }
    cout << "Переменная типа char - a: " << dec << addr_a << endl;
    cout << "Переменная типа char - b: " << dec << addr_b << endl;
    cout << "Переменная типа char - c: " << dec << addr_c << endl;


    cout << "\n---------------------------------------------------------------------------------------------------------------\n";
}


void step5() {
    cout << "Пункт 5\nРазработать программу,которая считывает побайтно содержимое переменной в пределах выделенной под переменную память\nи производит последующий вывод этих значений на экран.\nРешение:\n " << endl;
    short a = 10;
    unsigned n[16], address;
    __asm {
        lea ebx, a         // загрузить адрес переменной 'a' в регистр ebx
        mov address, ebx   // сохранить адрес 'a' в переменную 'address'
        mov ecx, 16        // загрузить значение 16 в регистр ecx (счетчик цикла)

        L:                      // метка начала цикла
        mov eax, [ebx]     // загрузить значение по адресу ebx в регистр eax
            push eax           // сохранить значение eax в стеке
            dec ebx            // уменьшить ebx на 1 (переход к предыдущему элементу)
            loop L             // повторить цикл, пока ecx != 0

            mov ecx, 16        // загрузить значение 16 в регистр ecx (счетчик цикла)

            cycle:                 // метка начала цикла
        pop dword ptr[n + ecx - 1] // извлечь значение из стека и сохранить его по адресу n + ecx - 1
            loop cycle         // повторить цикл, пока ecx != 0
    }
    cout << "Переменная a" << endl;
    cout << "Переменная типа short" << endl;
    cout << "Адрес размещения: " << dec << address << endl;
    cout << hex;
    for (int i = 0; i < 16; ++i) {
        cout << dec << n[i] << endl;
    }

    cout << "\n---------------------------------------------------------------------------------------------------------------\n";
}


void step6() {
    cout << "Пункт 6\nРазработана программа, которая производит перестановку элементов в переменной типа char.\nПрограмма переставляет элементы четные на место нечетных элементов и наоборот.\nРешение: " << endl << "1. Четные на место нечетных\n2. Нечетные на место четных" << endl << "> ";
    int choice;
    char a[255];
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "Введите исходную последовательность: ";
        cin >> a;
        _asm {
            lea ebx, a;         // загружает адрес переменной a в регистр ebx
            mov edi, ebx;       // копирует значение из ebx в регистр edi
            mov ebx, 0;         // обнуляет регистр ebx

        M1:
            mov al, [ebx + edi]; // загружает байт из памяти по адресу ebx + edi в регистр al
            cmp al, 0;          // сравнивает значение в al с нулем
            jz L1;              // если значение равно нулю, перемещает к метке L1

            mov ah, [ebx + edi + 1]; // загружает следующий байт из памяти по адресу ebx + edi + 1 в регистр ah
            cmp ah, 0;          // сравнивает значение в ah с нулем
            jz L1;              // если значение равно нулю, перемещает к метке L1

            xchg al, ah;        // меняет местами значения в регистрах al и ah
            mov[ebx + edi], al; // записывает значение из al в память по адресу ebx + edi
            mov[ebx + edi + 1], ah; // записывает значение из ah в память по адресу ebx + edi + 1
            add ebx, 2;         // увеличивает значение в ebx на 2

        L1:
            jnz M1;             // если значение в al или ah не равно нулю, то цикл продолжается
        }
        cout << "Последовательность после перестановки: " << a << endl;
        break;
    case 2:
        cout << "Введите начальную последовательность: ";
        cin >> a;
        _asm {
            lea ebx, a;             // загрузить адрес переменной 'a' в регистр ebx
            mov edi, ebx;           // скопировать адрес из ebx в edi
            xor ecx, ecx;           // счётчик парных элементов

                L2:
            mov al, [edi + ecx];    // загрузить текущий элемент
            mov ah, [edi + ecx + 1]; // загрузить следующий элемент
            xchg al, ah;            // поменять местами
            mov[edi + ecx], al;    // сохранить текущий элемент
            mov[edi + ecx + 1], ah; // сохранить следующий элемент
            add ecx, 2;             // перейти к следующей паре
            cmp byte ptr[edi + ecx], 0; // проверить конец массива
            jnz L2;                 // если не конец, продолжить
        }
        cout << "Последовательность после перестановки: " << a << endl;
        break;
    }
}

void individ() {
    int count = 9;
   // std::cout << "": 
  //  std::cin >> count;
   // std::cout << std::endl;

    int* arr = new int[count];
    int* arr_new = new int[count];
    std::cout << "Введите элементы: ->" << std::endl;
    int a;

    for (int i = 0; i < count; i++) {
        std::cin >> a;
        arr[i] = a;
        arr_new[i] = a;
    }
    cout << endl;
    for (int i = 1; i <3; i++) {
        cout << arr[i] << endl;
    }
    cout << arr[4] << endl << arr[3] << endl;
    cout << arr[0] << endl;
    cout << arr[7] << endl << arr[8] << endl;
    cout << arr[5] << endl << arr[6] << endl;
    if (count == 10) {
        int a1 = arr[1], a2 = arr[2], a3 = arr[3], a4 = arr[4];
        if (count >= 9) {
            __asm {
                mov eax, arr

                mov ebx, [eax + 0 * 4] // arr[0] = 1
                mov ecx, [eax + 6 * 4] // arr[6] = 7
                mov edx, [eax + 8 * 4] // arr[8] = 9
                mov esi, [eax + 5 * 4] // arr[5] = 6
                mov edi, [eax + 7 * 4] // arr[7] = 8

                // Сохраняем переставленные элементы
                mov[eax + 0 * 4], ebx // arr[0] = 1
                mov[eax + 1 * 4], ecx // arr[1] = 7
                mov[eax + 2 * 4], edx // arr[2] = 9
                mov[eax + 3 * 4], esi // arr[3] = 6
                mov[eax + 4 * 4], edi // arr[4] = 8
            }

            arr[5] = a1;
            arr[6] = a2;
            arr[7] = a4;
            arr[8] = a3;

            std::cout << std::endl;
            for (int i = 0; i < count; i++) {
                std::cout << arr[i] << std::endl;
            }

        }
        if (count / 9 == 2) {
            a1 = arr[11];
            a2 = arr[12];
            a3 = arr[13];
            a4 = arr[14];
            __asm {
                mov eax, arr

                mov ebx, [eax + 10 * 4] // arr[0] = 1
                mov ecx, [eax + 16 * 4] // arr[6] = 7
                mov edx, [eax + 18 * 4] // arr[8] = 9
                mov esi, [eax + 15 * 4] // arr[5] = 6
                mov edi, [eax + 17 * 4] // arr[7] = 8

                // Сохраняем переставленные элементы
                mov[eax + 10 * 4], ebx // arr[0] = 1
                mov[eax + 11 * 4], ecx // arr[1] = 7
                mov[eax + 12 * 4], edx // arr[2] = 9
                mov[eax + 13 * 4], esi // arr[3] = 6
                mov[eax + 14 * 4], edi // arr[4] = 8
            }

            arr[15] = a1;
            arr[16] = a2;
            arr[17] = a4;
            arr[18] = a3;

            std::cout << std::endl;
            for (int i = 0; i < count; i++) {
                std::cout << arr[i] << std::endl;
            }
        }
    }
   
}


void choiceInt() {
    char a[255];
    std::cout << "Введите начальную последовательность: ";
    std::cin >> a;
         
    _asm {

        lea ebx, a;
        mov edi, ebx;

        mov ebx, 0;

    L1: mov ah, [ebx + edi];
        mov[ebx + edi], ah;
        inc ebx;
        cmp ah, 0;
        jnz L1

            mov ah, 0;
        mov al, [edi];
        mov ah, [edi + ebx - 2];
        xchg al, ah;
        mov[edi], al;
        mov[edi + ebx - 2], ah;

        mov al, 0;
        mov ah, 0;
        mov al, [edi + 1];
        mov ah, [edi + ebx - 3];
        xchg al, ah;
        mov[edi + 1], al;
        mov[edi + ebx - 3], ah;

        mov al, 0;
        mov ah, 0;
        mov al, [edi + 2];
        mov ah, [edi + ebx - 4];
        xchg al, ah;
        mov[edi + 2], al;
        mov[edi + ebx - 4], ah;

        mov al, 0;
        mov ah, 0;
        mov al, [edi + 4];
        mov ah, [edi + ebx - 5];
        xchg al, ah;
        mov[edi + 4], al;
        mov[edi + ebx - 5], ah;

        mov al, 0;
        mov ah, 0;
        mov al, [edi];
        mov ah, [edi + ebx - 5];
        xchg al, ah;
        mov[edi], al;
        mov[edi + ebx - 5], ah;

        mov al, 0;
        mov ah, 0;
        mov al, [edi];
        mov ah, [edi + ebx - 7];
        xchg al, ah;
        mov[edi], al;
        mov[edi + ebx - 7], ah;

        mov al, 0;
        mov ah, 0;
        mov al, [edi + 1];
        mov ah, [edi + 3];
        xchg al, ah;
        mov[edi + 1], al;
        mov[edi + 3], ah;
    }

    

    std::cout << "Последовательность после перестановки: " << a << std::endl;

}


void interFace() {
	int choiceType, flag = 1;
	cout << "Лабораторная работа номер 3\nПерестановка переменных" << endl;
	while (flag != 0){
		cout << "Выберите тип данных, для перестановки (int - 1; short - 2; float - 3; char - 4) - ";
		cin >> choiceType;
		if (choiceType > 0 && choiceType < 5) {
			flag = 0;
			switch (choiceType) {
			case 1:
				cout << "\n---------------------------------------------------------------------------------------------------------------\n";
				choiceInt();
				break;
			case 2:
				cout << "Недоступно" << endl;
				break;
			case 3:
				cout << "Недоступно" << endl;
				break;
				cout << "Недоступно" << endl;
			case 4:
				break;
			}
		}
		else {
			cout << "Вы ввели неправильное значение!" << endl;
			flag = 1;
		}
		
	}

}



int main() {
	system("chcp 1251 > nul");
    //step4();
   // step4();
   // step5();
    //step6(); 
    //choiceInt();
    individ();
	return 0;
}