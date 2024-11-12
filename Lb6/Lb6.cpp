#include <iostream>
#include <limits>
#include <string>
#include <cctype>


// Отключение окна оповещения об старых функциях
#pragma warning(disable : 4996)


// Удаление макроса
#undef max


using namespace std;


// Заголовок
void Heading() {
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "|\t\t\t\t      Лабораторная работа номер 6   \t\t\t\t\t| " << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
}

// Задержка перед переходом
void delay() {
    char check;
    cout << "\n\n>> |x| Введите любой символ для продожения...\n\n$->: ";
    cin >> check;
}


// Перевод 16 - 10
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


// Меню домашнего задания
void homework() {
    int flag = 1;
    string number;
    do {
        Heading();
        cout << "\n                                                 Домашняя работа" << endl;
        cout << "\n>> |Программа для определения типа формата переменной и перевода ее в int.|" << endl;
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


// Перевод 16 - 10
uint32_t hex_to_int(std::string inp) {
    auto chinp = inp.c_str();
    int len = inp.length() - 2 > 8 ? 8 : inp.length() - 2;
    uint32_t res = 0;
    __asm {
        // Инициализация регистров
        mov ecx, len
        mov ebx, chinp

        // Цикл обработки строк
        lp :
        // Загрузка символа и очистка регистра
        xor edx, edx
            mov dl, [ebx + 2]
            // Проверка и преобразование символа
            cmp edx, '9' //  сравнивает загруженный символ с '9'.
            jg alph // если символ больше '9', то он переходит к метке alph, где выполняется преобразование букв A-F в соответствующие десятичные значения.

            sub dl, '0' // если символ меньше или равен '9', то он преобразует цифру в ее десятичное значение.
            jmp body // переходит к метке body после преобразования

            alph :
            sub dl, ('A' - 10)  // преобразует букву A-F в соответствующее десятичное значение (A=10, B=11,..., F=15)

            // Умножение и накопление результата
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


// Перевод 2 - 10
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


uint32_t stringToInt(const char* inp) {
    int format = 0;
    //int len = strlen(str);
    uint32_t res = 0;

    __asm {
        mov eax, format; Загружаем формат(0 - десятичный, 1 - двоичный, 2 - восьмеричный, 3 - шестнадцатеричный)
        mov ebx, inp; Указатель на строку

        cmp eax, 3; Если формат = 3, то шестнадцатеричный
        je hex_conversion

        cmp eax, 1; Если формат = 1, то двоичный
        je bin_conversion

        cmp eax, 2; Если формат = 2, то восьмеричный
        je octal_conversion

        ; Для десятичного
        jmp decimal_conversion

        hex_conversion :
        add ebx, 2; Пропускаем "0x" для шестнадцатеричного числа
            mov res, 0; Устанавливаем результат
            hex_loop :
        xor edx, edx
            movzx edx, byte ptr[ebx]; Загружаем символ
            cmp edx, 0; Если конец строки, выходим
            je end_conversion

            cmp edx, '0'
            jl invalid_char
            cmp edx, '9'
            jg check_alpha
            sub edx, '0'; Преобразуем цифру
            jmp shift_left

            check_alpha :
        cmp edx, 'A'
            jl invalid_char
            cmp edx, 'F'
            jg invalid_char
            sub edx, 'A' - 10; Преобразуем букву в число
            jmp shift_left

            invalid_char :
        mov res, -1
            jmp end_conversion

            shift_left :
        shl res, 4; Сдвигаем результат на 4 бита
            add res, edx; Добавляем цифру к результату
            inc ebx; Переходим к следующему символу
            jmp hex_loop

            bin_conversion :
        add ebx, 2; Пропускаем "0b" для двоичного числа
            mov res, 0; Устанавливаем результат
            bin_loop :
        xor edx, edx
            movzx edx, byte ptr[ebx]; Загружаем символ
            cmp edx, 0; Если конец строки, выходим
            je end_conversion

            sub edx, '0'; Преобразуем символ в 0 или 1
            shl res, 1; Сдвигаем результат на 1 бит(умножаем на 2)
            add res, edx; Добавляем число к результату
            inc ebx; Переходим к следующему символу
            jmp bin_loop

            octal_conversion :
        add ebx, 2; Пропускаем "0" для восьмеричного числа
            mov res, 0; Устанавливаем результат
            octal_loop :
        xor edx, edx
            movzx edx, byte ptr[ebx]; Загружаем символ
            cmp edx, 0; Если конец строки, выходим
            je end_conversion

            cmp edx, '0'
            jl invalid_char
            cmp edx, '7'
            jg invalid_char
            sub edx, '0'; Преобразуем символ в число
            shl res, 3; Сдвигаем результат на 3 бита(умножаем на 8)
            add res, edx; Добавляем число к результату
            inc ebx; Переходим к следующему символу
            jmp octal_loop

            decimal_conversion :
        mov res, 0; Устанавливаем результат для десятичного
            decimal_loop :
        xor edx, edx
            movzx edx, byte ptr[ebx]; Загружаем символ
            cmp edx, 0; Если конец строки, выходим
            je end_conversion

            cmp edx, '0'
            jl invalid_char
            cmp edx, '9'
            jg invalid_char
            sub edx, '0'; Преобразуем символ в цифру

            ; Для десятичного умножаем на 10
            mov eax, res; Загружаем результат
            imul eax, eax, 10; Умножаем на 10
            mov res, eax; Сохраняем результат обратно в res

            add res, edx; Добавляем цифру к результату
            inc ebx; Переходим к следующему символу
            jmp decimal_loop

            end_conversion :
    }

    return res;
}


// Получения типа переменной по специальным символам
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
        cout << "\t|\n\n\t|>> |Type|-> Десятичное";
        return 10;
    }
    else if (hex) {
        cout << "\t|\n\n|>> |Type|-> Шестнадцетеричное";
        return 16;
    }
    else if (bin) {
        cout << "\t|\n\n|>> |Type|-> Двоичное";
        return 2;
    }
    else {
        cout <<"\t|\n\n|>> |!| Ошибка!";
        return 0;
    }
}


// Меню рабочего задания
void classwork() {
    int flagChose, flagType;
    char num[100];
    do {
        Heading();
        cout << "\n                                             Рабочее задание:" << endl;
        cout << "\n>> |x| Выберите задания:\n    |\n    | 1 - Определения формата;\n    | 2 - Перевода чисел в int;\n    | 0 - Выход в меню;\n    |" << endl;
        cout << "\n$->: ";
        // Проверка на ввод чарок в инт переменную
        if (!(cin >> flagChose)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            flagChose = -1;
            system("cls");
            cout << "\n>> |!| Вы ввели неправильное значение!\n" << endl;
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
            if (strlen(num) > 10) {
                system("cls");
                cout << "\n>> |!| Переполнение\n" << endl;
                continue;
            }
            flagType = get_type(num);
            if (flagType == 10)
            {
                cout << "\n|>> " << stringToInt(num);
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


// Главное меню
void mainMenu() {
    int flagChose;
    do {
        Heading();
        cout << "\n                                                 Меню" << endl;
        cout << "\n>> |x| Выберите работу:\n    |\n    | 1 - Домашняя работа;\n    | 2 - Практическая работа;\n    | 0 - Выход;\n    |" << endl;
        cout << "\n$->: ";
        // Проверка на ввод чарок в инт переменную
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


// Точка входа
int main() {
    system("chcp 1251 > nul");
    mainMenu();
    system("cls");
    cout << "\n\n>> |!| Завершение программы!\n\n";
    return 0;
}