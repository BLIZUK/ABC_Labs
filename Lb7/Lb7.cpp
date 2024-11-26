#include <iostream>
#include <iomanip>
#include <cstring>
#include <string.h>

// ������� ��� ������ ����������� ������������ ����
int step4(unsigned char* txt) {
    const int codeSize = 1024; // ������ ������� ������������ ����
    unsigned char* code = txt; // ��������� �� ����������� ���
    int offset = 0; // ��������

    while (offset < codeSize) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << offset << " "; // ����� ��������

        for (int i = 0; i < 16; ++i) {
            if (offset + i < codeSize) {
                unsigned char bytemy = code[offset + i];
                // ������������ ������� ��� ������ ����� � ����������������� �������
                unsigned char hexByte;
                __asm {
                    mov al, bytemy // �������� ����� � ������� al
                    mov bl, '0' // �������� '0' � ������� bl
                    cmp al, 10 // ��������� al � 10
                    jl digit // ������� � ����� digit, ���� al < 10
                    add al, 'a' - 10 // �������������� al � ����������������� ����� (A-F)
                    digit: // ����� ��� ����������� ����������
                    add al, '0' // �������������� al � ����������������� ����� (0-9)
                        mov hexByte, al // ���������� ���������� ������� � ������
                }
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)hexByte << " ";
            }
            else {
                std::cout << "   "; // ����� �������� ��� ������������
            }
        }

        for (int i = 0; i < 16; ++i) {
            if (offset + i < codeSize) {
                unsigned char bytemy = code[offset + i];
                if (bytemy >= 32 && bytemy <= 126) { // �������� ASCII ���������
                    std::cout << (char)bytemy; // ����� ASCII �������
                }
                else {
                    std::cout << "."; // ����� ����� ��� ��-ASCII ��������
                }
            }
        }

        std::cout << "\n"; // ������� �� ����� ������
        offset += 16; // ��������� �������� �� 16 ����

        // �������� ������� ������� ��� �������� � ��������� ������
        std::cout << "������� Enter ��� �����������...";
        std::cin.get();
    }

    return 0;
}

// ������� ��� ������ ����������� ������� ������
int step2() {
    const int bufferSize = 1024; // ������ ������� ������
    unsigned char buffer[bufferSize]; // ������ ��� �������� ������
    int index; // ������ ��� ��������� ������

    // ������������� ������ ��� ������������
    for (int i = 0; i < bufferSize; ++i) {
        buffer[i] = i % 256; // ������������� ������ ���������� �� 0 �� 255
    }

    int offset = 0; // �������� ��� ������ ������
    while (offset < bufferSize) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << offset << " "; // ����� ��������
        for (int i = 0; i < 16; ++i) {
            if (offset + i < bufferSize) {
                index = int(buffer) + offset + i; // ������ ������ �����
                // ������������ ������� ��� ������ ����� � ����������������� �������
                __asm {
                    //mov al, byte ptr[buffer + offset + i]
                    mov al, byte ptr[index] // �������� ����� � ������� al
                    mov bl, '0' // �������� '0' � ������� bl
                    cmp al, 10 // ��������� al � 10
                    jl digit // ������� � ����� digit, ���� al < 10
                    add al, 'a' - 10 // �������������� al � ����������������� ����� (A-F)
                    digit: // ����� ��� ����������� ����������
                    add al, '0' // �������������� al � ����������������� ����� (0-9)
                        mov byte ptr[index], al // ���������� ���������� ������� � ������ (�� �������������)
                }
                std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[offset + i] << " "; // ����� ����� � ����������������� �������
            }
            else {
                std::cout << "   "; // ����� �������� ��� ������������
            }
        }
        for (int i = 0; i < 16; ++i) {
            if (offset + i < bufferSize) {
                if (buffer[offset + i] >= 32 && buffer[offset + i] <= 126) { // �������� ASCII ���������
                    std::cout << (char)buffer[offset + i]; // ����� ASCII �������
                }
                else {
                    std::cout << "."; // ����� ����� ��� ��-ASCII ��������
                }
            }
        }
        std::cout << "\n"; // ������� �� ����� ������
        offset += 16; // ��������� �������� �� 16 ����

        // �������� ������� ������� ��� �������� � ��������� ������
        std::cout << "������� Enter ��� �����������...";
        std::cin.get();
    }

    return 0;
}

// ������� ��� ������ � ������ ��������� ���������� ������ �� ������
int step1() {
    unsigned int bytesRead; // ���������� ������ ��� ������
    std::cout << "������� ���������� ������ ��� ������: ";
    std::cin >> bytesRead;

    unsigned char* memory = new unsigned char[bytesRead]; // ��������� ������ ��� �������� ������
    std::cout << "������� ����� (�� ������ � ������):\n";

    for (unsigned int i = 0; i < bytesRead; ++i) {
        std::cin >> std::hex >> memory[i]; // ������ ������ �� ������������ �����
    }

    std::cout << "��������� ����� � ASCII � ����������������� �������:\n";
    for (unsigned int i = 0; i < bytesRead; ++i) {
        unsigned char temp = memory[i]; // �������� �������� � ��������� ����������

        // ������������ ������� ��� �������������� ����� � ����������������� ������
        __asm {
            mov al, temp // �������� ����� � ������� al
            mov bl, '0' // �������� '0' � ������� bl
            cmp al, 10 // ��������� al � 10
            jl digit // ������� � ����� digit, ���� al < 10
            add al, 'a' - 10 // �������������� al � ����������������� ����� (A-F)
            digit: // ����� ��� ����������� ����������
            add al, '0' // �������������� al � ����������������� ����� (0-9)
        }

        // ����� ������������������ ��������
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)memory[i] << " ";

        // ����� ASCII ��������
        if (memory[i] >= 32 && memory[i] <= 126) { // �������� ASCII ���������
            std::cout << (char)memory[i] << " "; // ����� ASCII �������
        }
        else {
            std::cout << "." << " "; // ����� ����� ��� ��-ASCII ��������
        }

        // ������� �� ����� ������ ����� ������ 16 ����
        if ((i + 1) % 16 == 0) {
            std::cout << "\n";
        }
    }
    std::cout << "\n\n";

    delete[] memory; // ������������ ������
    return 0;
}

int main() {
    int flag;
    unsigned char* code = (unsigned char*)main; // ��������� �� ����������� ���
    system("chcp 1251 > nul"); // ��������� ������� �������� ��� ����������� ������ ���������
    do
    {
        std::cout << "�������� ������� :\n 1 - ������ ���; \n 2 - ������ ���;\n 3 - ��������� ���;\n 0 - �����.\n";
        std::cin >> flag;
        switch (flag) 
        {
        case 1:
            step1(); // ����� ������� ��� ������ � ������ ��������� ���������� ������
            break;
        case 2:
            step2(); // ����� ������� ��� ������ ����������� ������� ������
            break;
        case 3:
            step4(code); // ����� ������� ��� ������ ����������� ������������ ����
            break;
        }
    } while (flag != 0);

    return 0;
}