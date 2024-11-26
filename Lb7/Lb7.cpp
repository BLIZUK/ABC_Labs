#include <iostream>
#include <iomanip>
#include <cstring>
#include <string.h>

// Функция для вывода содержимого программного кода
int step4(unsigned char* txt) {
    const int codeSize = 1024; // Размер области программного кода
    unsigned char* code = txt; // Указатель на программный код
    int offset = 0; // Смещение

    while (offset < codeSize) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << offset << " "; // Вывод смещения

        for (int i = 0; i < 16; ++i) {
            if (offset + i < codeSize) {
                unsigned char bytemy = code[offset + i];
                // Ассемблерная вставка для вывода байта в шестнадцатеричном формате
                unsigned char hexByte;
                __asm {
                    mov al, bytemy // Загрузка байта в регистр al
                    mov bl, '0' // Загрузка '0' в регистр bl
                    cmp al, 10 // Сравнение al с 10
                    jl digit // Переход к метке digit, если al < 10
                    add al, 'a' - 10 // Преобразование al в шестнадцатеричную букву (A-F)
                    digit: // Метка для продолжения выполнения
                    add al, '0' // Преобразование al в шестнадцатеричную цифру (0-9)
                        mov hexByte, al // Сохранение результата обратно в память
                }
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hexByte << " ";
            }
            else {
                std::cout << "   "; // Вывод пробелов для выравнивания
            }
        }

        for (int i = 0; i < 16; ++i) {
            if (offset + i < codeSize) {
                unsigned char bytemy = code[offset + i];
                if (bytemy >= 32 && bytemy <= 126) { // Проверка ASCII диапазона
                    std::cout << (char)bytemy; // Вывод ASCII символа
                }
                else {
                    std::cout << "."; // Вывод точки для не-ASCII символов
                }
            }
        }

        std::cout << "\n"; // Переход на новую строку
        offset += 16; // Инкремент смещения на 16 байт

        // Ожидание нажатия клавиши для перехода к следующей строке
        std::cout << "Нажмите Enter для продолжения...";
        std::cin.get();
    }

    return 0;
}

// Функция для вывода содержимого области данных
int step2() {
    const int bufferSize = 1024; // Размер области данных
    unsigned char buffer[bufferSize]; // Массив для хранения данных
    int index; // Индекс для адресации памяти

    // Инициализация буфера для демонстрации
    for (int i = 0; i < bufferSize; ++i) {
        buffer[i] = i % 256; // Инициализация байтов значениями от 0 до 255
    }

    int offset = 0; // Смещение для вывода данных
    while (offset < bufferSize) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << offset << " "; // Вывод смещения
        for (int i = 0; i < 16; ++i) {
            if (offset + i < bufferSize) {
                index = int(buffer) + offset + i; // Расчет адреса байта
                // Ассемблерная вставка для вывода байта в шестнадцатеричном формате
                __asm {
                    //mov al, byte ptr[buffer + offset + i]
                    mov al, byte ptr[index] // Загрузка байта в регистр al
                    mov bl, '0' // Загрузка '0' в регистр bl
                    cmp al, 10 // Сравнение al с 10
                    jl digit // Переход к метке digit, если al < 10
                    add al, 'a' - 10 // Преобразование al в шестнадцатеричную букву (A-F)
                    digit: // Метка для продолжения выполнения
                    add al, '0' // Преобразование al в шестнадцатеричную цифру (0-9)
                        mov byte ptr[index], al // Сохранение результата обратно в память (не рекомендуется)
                }
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[offset + i] << " "; // Вывод байта в шестнадцатеричном формате
            }
            else {
                std::cout << "   "; // Вывод пробелов для выравнивания
            }
        }
        for (int i = 0; i < 16; ++i) {
            if (offset + i < bufferSize) {
                if (buffer[offset + i] >= 32 && buffer[offset + i] <= 126) { // Проверка ASCII диапазона
                    std::cout << (char)buffer[offset + i]; // Вывод ASCII символа
                }
                else {
                    std::cout << "."; // Вывод точки для не-ASCII символов
                }
            }
        }
        std::cout << "\n"; // Переход на новую строку
        offset += 16; // Инкремент смещения на 16 байт

        // Ожидание нажатия клавиши для перехода к следующей строке
        std::cout << "Нажмите Enter для продолжения...";
        std::cin.get();
    }

    return 0;
}

// Функция для чтения и вывода заданного количества байтов из памяти
int step1() {
    unsigned int bytesRead; // Количество байтов для чтения
    std::cout << "Введите количество байтов для чтения: ";
    std::cin >> bytesRead;

    unsigned char* memory = new unsigned char[bytesRead]; // Выделение памяти для хранения байтов
    std::cout << "Введите байты (по одному в строке):\n";

    for (unsigned int i = 0; i < bytesRead; ++i) {
        std::cin >> std::hex >> memory[i]; // Чтение байтов из стандартного ввода
    }

    std::cout << "Введенные байты в ASCII и шестнадцатеричном формате:\n";
    for (unsigned int i = 0; i < bytesRead; ++i) {
        unsigned char temp = memory[i]; // Копируем значение в временную переменную

        // Ассемблерная вставка для преобразования байта в шестнадцатеричный формат
        __asm {
            mov al, temp // Загрузка байта в регистр al
            mov bl, '0' // Загрузка '0' в регистр bl
            cmp al, 10 // Сравнение al с 10
            jl digit // Переход к метке digit, если al < 10
            add al, 'a' - 10 // Преобразование al в шестнадцатеричную букву (A-F)
            digit: // Метка для продолжения выполнения
            add al, '0' // Преобразование al в шестнадцатеричную цифру (0-9)
        }

        // Вывод шестнадцатеричного значения
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)memory[i] << " ";

        // Вывод ASCII значения
        if (memory[i] >= 32 && memory[i] <= 126) { // Проверка ASCII диапазона
            std::cout << (char)memory[i] << " "; // Вывод ASCII символа
        }
        else {
            std::cout << "." << " "; // Вывод точки для не-ASCII символов
        }

        // Переход на новую строку после каждых 16 байт
        if ((i + 1) % 16 == 0) {
            std::cout << "\n";
        }
    }
    std::cout << "\n\n";

    delete[] memory; // Освобождение памяти
    return 0;
}

int main() {
    int flag;
    unsigned char* code = (unsigned char*)main; // Указатель на программный код
    system("chcp 1251 > nul"); // Установка кодовой страницы для корректного вывода кириллицы
    do
    {
        std::cout << "Выберите задание :\n 1 - Первый шаг; \n 2 - второй шаг;\n 3 - Четвертый шаг;\n 0 - Выход.\n";
        std::cin >> flag;
        switch (flag) 
        {
        case 1:
            step1(); // Вызов функции для чтения и вывода заданного количества байтов
            break;
        case 2:
            step2(); // Вызов функции для вывода содержимого области данных
            break;
        case 3:
            step4(code); // Вызов функции для вывода содержимого программного кода
            break;
        }
    } while (flag != 0);

    return 0;
}