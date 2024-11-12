#include <iostream>
#include <limits>
#include <string>
#include <cctype>
//#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)


// Удаление макроса
#undef max


using namespace std;


void Heading() {
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "|\t\t\t\t     Лабораторная работа номер 6    \t\t\t\t\t| " << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
}

// Задержка перед переходом
void delay() {
    char check;
    cout << "\n\n>> |x| Введите любой символ для продожения...\n\n$->: ";
    cin >> check;
}

void hex(string hexStr) {
    int result = 0;
    int len = hexStr.length();
    char* cstr = new char[len + 1]; // Создаем копию строки
    strcpy(cstr, hexStr.c_str());

    __asm {
        mov ecx, len       // Количество итераций (длина строки)
        mov esi, cstr      // Адрес строки
        xor eax, eax        // Очистить регистр eax (будет хранить результат)
        xor ebx, ebx        // Очистить регистр ebx (будет хранить текущую позицию)

        loop_through_string :
        mov bl, [esi]       // Загрузить текущий символ в bl
            inc esi             // Перейти к следующему символу

            // Преобразовать символ в десятичное значение
            cmp bl, '9'
            jle digit_to_decimal
            sub bl, 55          // Для букв A-F (A=10, B=11,..., F=15)
            jmp multiply_and_add

            digit_to_decimal :
        sub bl, '0'         // Для цифр 0-9

            multiply_and_add :
            imul eax, 16        // Умножить текущий результат на 16
            add eax, ebx        // Добавить десятичное значение текущей цифры

            loop loop_through_string // Повторить для следующей цифры

            // Результат теперь в eax
            mov[result], eax   // Сохранить результат в переменную
    };

    delete[] cstr; // Освобождаем память
    cout << "\n>> |Десятичное представление| -> " << result << endl;
}

void oct(string num) {

}

void bin(string num) {

}

void homework() {
    int flag = 1;
    string number;
    do {
        Heading();
        cout << "\n                                                 Домашняя работа" << endl;
        cout << ">> |Программа для определения типа формата переменной и перевода ее в int.|" << endl;
        cout << ">> |x| Введите число:\n    |\n    | 16 СС пример - 0x01DE;\n    | 8 СС пример - 0x0360;\n    | 2 пример - 0b0110;\n    |\n    | 0 - Выход в меню;\n    |\n" << endl;
        cout << "$->: ";
        cin >> number;
        if (number == "0") {
            flag = 0;
        }
        else if (number.size() > 2 && number.substr(0, 2) == "0x") {
            hex(number.substr(2));
            flag = 1;
            delay();
            system("cls");
        }
        else if (number.size() > 2 && number.substr(0, 2) == "Ox") {
            flag = 1;
        }
        else if (number.size() > 2 && number.substr(0, 2) == "0d") {
            flag = 1;
        }
        else {
            system("cls");
            cout << "\n\n>> |!| Вы ввели неверное значение!\n" << endl;
        }
    } while (flag != 0);
}

uint32_t hex_to_int(std::string inp) {
    auto chinp = inp.c_str();
    int len = inp.length() - 2 > 8 ? 8 : inp.length() - 2;
    uint32_t res = 0;
    __asm {
        mov ecx, len
        mov ebx, chinp

        lp :
        xor edx, edx
            mov dl, [ebx + 2]
            cmp edx, '9'
            jg alph

            sub dl, '0'
            jmp body

            alph :
        sub dl, ('A' - 10)

            body :
            mov eax, 4
            xchg dl, ch
            mul ecx
            xchg ch, dl
            xchg ecx, eax

            ror edx, 4
            rol edx, cl
            add res, edx
            xchg ecx, eax
            inc ebx
            loop lp
    }
    return res;
}


uint32_t bin_to_int(std::string inp) {
    auto chinp = inp.c_str();
    int len = inp.length() - 2 > 32 ? 32 : inp.length() - 2;
    uint32_t res = 0;
    __asm {
        mov ecx, len
        mov ebx, chinp

        lp :
        xor edx, edx
            mov dl, [ebx + 2]
            sub dl, '0'
            ror edx, 1
            rol edx, cl
            add res, edx
            inc ebx
            loop lp
    }
    return res;
}


int get_type(char* input) {
    bool dec = false;
    bool hex = false;
    bool bin = false;
    __asm {
        mov ebx, input

        cmp[ebx], '0'
        jne decim

        cmp[ebx + 1], 'x'
        je hexim
        cmp[ebx + 1], 'X'
        je hexim

        cmp[ebx + 1], 'b'
        je binar
        cmp[ebx + 1], 'B'
        je binar

        decim :
        mov dec, 1
            jmp done

            hexim :
        mov hex, 1
            jmp done

            binar :
        mov bin, 1

            done :
    }
    if (dec) {
        cout << "\t|\n\n\t|>> Десятичное";
        return 10;
    }
    else if (hex) {
        cout << "\t|\n\n|>>Шестнадцетеричное";
        return 16;
    }
    else if (bin) {
        cout << "\t|\n\n|>> Двоичное";
        return 2;
    }
    else {
        cout <<"\t|\n\n|>> |!| Ошибка!";
        return 0;
    }
}


void classwork() {
    int flagChose, flagType;
    char num[100];
    do {
        Heading();
        cout << "\n                                             Рабочее задание:" << endl;
        cout << ">> |x| Выберите задания:\n    |\n    | 1 - Определения формата;\n    | 2 - Перевода чисел в int;\n    | 0 - Выход в меню;\n    |" << endl;
        cout << "\n$->: ";
        if (!(cin >> flagChose)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            flagChose = -1;
            system("cls");
            cout << "\n>>|!| Вы ввели неправильное значение!\n" << endl;
            continue;
        }
        switch (flagChose) {
        case 1:
            //system("cls");
            cout << "\n\t==Определение формата==";
            cout << "\n\t|\n\t|>> |x| Введите число:\n\t|$->: ";
            cin >> num;
            get_type(num);
            delay();
            system("cls");
            break;
        case 2:
            cout << "\n\t==Перевода чисел в int==";
            cout << "\n\t|\n\t|>> |x| Введите число:\n\t|$->: ";
            cin >> num;
            flagType = get_type(num);
            if (flagType == 10)
            {
                cout << "\n|>> " << num;
            }
            if (flagType == 16)
            {
                cout << "\n|>> " << hex_to_int(num);
            }
            if (flagType == 2)
            {
                cout << "\n|>> " << bin_to_int(num);
            }
            delay();
            system("cls");
            break;
        }
            if (flagChose < 0 || flagChose > 2)
            {
                system("cls");
                cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
            }
        } while (flagChose != 0);
    }


void mainMenu() {
    int flagChose;
    do {
        Heading();
        cout << "\n                                                 Меню" << endl;
        cout << ">> |x| Выберите работу:\n    |\n    | 1 - Домашняя работа;\n    | 2 - Практическая работа;\n    | 0 - Выход;\n    |" << endl;
        cout << "\n$->: ";
        if (!(cin >> flagChose)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            flagChose = -1;
            system("cls");
            cout << "\n>>|!| Вы ввели неправильное значение!\n" << endl;
            continue;
        }
        switch (flagChose) {
        case 1:
            system("cls");
            homework();
            system("cls");
            break;
        case 2:
            system("cls");
            classwork();
            system("cls");
            break;
        }
        if (flagChose < 0 || flagChose > 2)
        {
            system("cls");
            cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
        }
    } while (flagChose != 0);
}

int main() {
    system("chcp 1251 > nul");
    mainMenu();
    return 0;
}