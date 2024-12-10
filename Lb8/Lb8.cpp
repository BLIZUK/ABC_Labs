#include <iostream>
#include <iomanip>
#include <string>


// ���������� ������� CPUID
void execute_cpuid(unsigned int eax_in, unsigned int& eax_out, unsigned int& ebx_out, unsigned int& ecx_out, unsigned int& edx_out) {
    unsigned int bufer[4];
    __asm {
        mov eax, eax_in       // �������� ������� �������� EAX
        cpuid                 // ��������� ���������� CPUID
        mov bufer[0], eax      // ��������� �������� ���������
        mov bufer[4], ebx
        mov bufer[8], ecx
        mov bufer[12], edx
    }

    eax_out = bufer[0];
    ebx_out = bufer[1];
    ecx_out = bufer[2];
    edx_out = bufer[3];
}

// ����� ������ �� ��������� (��������, 48 ASCII ��������)
std::string get_ascii_string(unsigned int eax, unsigned int ebx, unsigned int ecx, unsigned int edx) {
    char buffer[17] = { 0 }; // ������ ��� ������ (16 �������� + null-����������)
    memcpy(buffer, &eax, 4); // �������� 4 ����� �� EAX
    memcpy(buffer + 4, &ebx, 4); // �������� 4 ����� �� EBX
    memcpy(buffer + 8, &ecx, 4); // �������� 4 ����� �� ECX
    memcpy(buffer + 12, &edx, 4); // �������� 4 ����� �� EDX
    return std::string(buffer);
}


// �������� ����������� CPUID
bool check_cpuid_support() {
    bool supported = false;
    __asm {
        pushfd                // ��������� EFLAGS
        pop eax               // �������� EFLAGS � EAX
        mov ebx, eax          // ��������� ������������ �������� � EBX
        xor eax, 0x200000     // �������� 21-� ���
        push eax              // ���������� ����� �������� � ����
        popfd                 // ��������� � EFLAGS
        pushfd                // ���������, ��������� �� ���
        pop eax
        xor eax, ebx          // ���������� � ����������
        je not_supported      // ���� �� ���������, CPUID �� ��������������
        mov supported, 1      // ������������� ���� ���������
        not_supported:
    }
    return supported;
}


void process()
{
    unsigned int eax, ebx, ecx, edx;

    // ��������� ������� ���������� (EAX = 0)
    execute_cpuid(0x0, eax, ebx, ecx, edx);
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t������� ����������:" << std::endl;
    std::cout << "  EAX: " << std::hex << eax << std::endl;
    std::cout << "  EBX: " << std::hex << ebx << std::endl;
    std::cout << "  ECX: " << std::hex << ecx << std::endl;
    std::cout << "  EDX: " << std::hex << edx << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t\n----------------------------------------------------------------" << std::endl;
    std::cout << "������������� ����������:\n  " << get_ascii_string(ebx, edx, ecx, 0) << std::endl;

    std::cout << "----------------------------------------------------------------" << std::endl;

    // ��������� ���������� � ������ (EAX = 1)
    execute_cpuid(0x1, eax, ebx, ecx, edx);
    std::cout << "\n----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t���������� � ����������:" << std::endl;
    std::cout << "  EAX: " << std::hex << eax << std::endl;
    std::cout << "  EBX: " << std::hex << ebx << std::endl;
    std::cout << "  ECX: " << std::hex << ecx << std::endl;
    std::cout << "  EDX: " << std::hex << edx << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    // ��������� ����������� ���������� (EAX = 80000000h)
    execute_cpuid(0x80000000, eax, ebx, ecx, edx);
    std::cout << "\n----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t����������� ����������� ����������:" << std::endl;
    std::cout << "  ������������ �������� EAX: " << std::hex << eax << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

    // ���������� ������ ���������� (EAX = 80000002h, 80000003h, 80000004h)
    std::string processor_name;
    for (unsigned int i = 0x80000002; i <= 0x80000004; ++i) {
        execute_cpuid(i, eax, ebx, ecx, edx);
        processor_name += get_ascii_string(eax, ebx, ecx, edx);
    }
    std::cout << "\n----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t��� ����������:\n  " << processor_name << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;
    // ��������� ���������� � ���� (EAX = 80000006h)
    execute_cpuid(0x80000006, eax, ebx, ecx, edx);
    std::cout << "\n----------------------------------------------------------------" << std::endl;
    std::cout << "\t\t\t���������� � ���� ����������:  " << std::endl;
    std::cout << "  EAX: " << std::hex << eax << std::endl;
    std::cout << "  EBX: " << std::hex << ebx << std::endl;
    std::cout << "  ECX: " << std::hex << ecx << std::endl;
    std::cout << "  EDX: " << std::hex << edx << std::endl;
    std::cout << "----------------------------------------------------------------" << std::endl;

}


// ����� �����
int main() {
    system("chcp 1251 > nul");
    if (!check_cpuid_support()) {
        std::cout << "CPUID �� �������������� �����������." << std::endl;
        return 1;
    }
    process();
    return 0;
}
