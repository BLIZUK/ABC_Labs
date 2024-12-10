#include <iostream>
#include <iomanip>
#include <string>


// Выполнение команды CPUID
void execute_cpuid(unsigned int eax_in, unsigned int& eax_out, unsigned int& ebx_out, unsigned int& ecx_out, unsigned int& edx_out) {
    unsigned int bufer[4];
    __asm {
        mov eax, eax_in       // Передаем входное значение EAX
        cpuid                 // Выполняем инструкцию CPUID
        mov bufer[0], eax      // Сохраняем значения регистров
        mov bufer[4], ebx
        mov bufer[8], ecx
        mov bufer[12], edx
    }

    eax_out = bufer[0];
    ebx_out = bufer[1];
    ecx_out = bufer[2];
    edx_out = bufer[3];
}

// Вывод строки из регистров (например, 48 ASCII символов)
std::string get_ascii_string(unsigned int eax, unsigned int ebx, unsigned int ecx, unsigned int edx) {
    char buffer[17] = { 0 }; // Массив для строки (16 символов + null-терминатор)
    memcpy(buffer, &eax, 4); // Копируем 4 байта из EAX
    memcpy(buffer + 4, &ebx, 4); // Копируем 4 байта из EBX
    memcpy(buffer + 8, &ecx, 4); // Копируем 4 байта из ECX
    memcpy(buffer + 12, &edx, 4); // Копируем 4 байта из EDX
    return std::string(buffer);
}


// Проверка доступности CPUID
bool check_cpuid_support() {
    bool supported = false;
    __asm {
        pushfd                // Сохраняем EFLAGS
        pop eax               // Копируем EFLAGS в EAX
        mov ebx, eax          // Сохраняем оригинальное значение в EBX
        xor eax, 0x200000     // Изменяем 21-й бит
        push eax              // Записываем новое значение в стек
        popfd                 // Сохраняем в EFLAGS
        pushfd                // Проверяем, изменился ли бит
        pop eax
        xor eax, ebx          // Сравниваем с оригиналом
        je not_supported      // Если не изменился, CPUID не поддерживается
        mov supported, 1      // Устанавливаем флаг поддержки
        not_supported:
    }
    return supported;
}


void process()
{
    unsigned int eax, ebx, ecx, edx;

    // Получение базовой информации (EAX = 0)
    execute_cpuid(0x0, eax, ebx, ecx, edx);
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\tБазовая информация:" << std::endl;
    std::cout << "  EAX: " << std::hex << eax << std::endl;
    std::cout << "  EBX: " << std::hex << ebx << std::endl;
    std::cout << "  ECX: " << std::hex << ecx << std::endl;
    std::cout << "  EDX: " << std::hex << edx << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t\n----------------------------------------------------------------" << std::endl;
    std::cout << "Производитель процессора:\n  " << get_ascii_string(ebx, edx, ecx, 0) << std::endl;

    std::cout << "----------------------------------------------------------------" << std::endl;

    // Получение информации о модели (EAX = 1)
    execute_cpuid(0x1, eax, ebx, ecx, edx);
    std::cout << "\n----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\tИнформация о процессоре:" << std::endl;
    std::cout << "  EAX: " << std::hex << eax << std::endl;
    std::cout << "  EBX: " << std::hex << ebx << std::endl;
    std::cout << "  ECX: " << std::hex << ecx << std::endl;
    std::cout << "  EDX: " << std::hex << edx << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    // Получение расширенной информации (EAX = 80000000h)
    execute_cpuid(0x80000000, eax, ebx, ecx, edx);
    std::cout << "\n----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\tРасширенные возможности процессора:" << std::endl;
    std::cout << "  Максимальное значение EAX: " << std::hex << eax << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    // Считывание строки процессора (EAX = 80000002h, 80000003h, 80000004h)
    std::string processor_name;
    for (unsigned int i = 0x80000002; i <= 0x80000004; ++i) {
        execute_cpuid(i, eax, ebx, ecx, edx);
        processor_name += get_ascii_string(eax, ebx, ecx, edx);
    }
    std::cout << "\n----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\tИмя процессора:\n  " << processor_name << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;
    // Получение информации о кэше (EAX = 80000006h)
    execute_cpuid(0x80000006, eax, ebx, ecx, edx);
    std::cout << "\n----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\tИнформация о кэше процессора:  " << std::endl;
    std::cout << "  EAX: " << std::hex << eax << std::endl;
    std::cout << "  EBX: " << std::hex << ebx << std::endl;
    std::cout << "  ECX: " << std::hex << ecx << std::endl;
    std::cout << "  EDX: " << std::hex << edx << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

}


// Точка входа
int main() {
    system("chcp 1251 > nul");
    if (!check_cpuid_support()) {
        std::cout << "CPUID не поддерживается процессором." << std::endl;
        return 1;
    }
    process();
    return 0;
}
