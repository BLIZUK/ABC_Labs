#include <iostream>
#include <limits>
#include <string>
#include <cctype>


// ���������� ���� ���������� �� ������ ��������
#pragma warning(disable : 4996)


// �������� �������
#undef max


using namespace std;


// ���������
void Heading() {
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout << "|\t\t\t\t      ������������ ������ ����� 6   \t\t\t\t\t| " << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
}

// �������� ����� ���������
void delay() {
    char check;
    cout << "\n\n>> |x| ������� ����� ������ ��� ����������...\n\n$->: ";
    cin >> check;
}


// ������� 16 - 10
void hex(string hexStr) {
    int result = 0;
    int len = hexStr.length();
    char* cstr = new char[len + 1]; // ������� ����� ������
    strcpy(cstr, hexStr.c_str());

    __asm {
        mov ecx, len       // ���������� �������� (����� ������)
        mov esi, cstr      // ����� ������
        xor eax, eax        // �������� ������� eax (����� ������� ���������)
        xor ebx, ebx        // �������� ������� ebx (����� ������� ������� �������)

        loop_through_string :
        mov bl, [esi]       // ��������� ������� ������ � bl
            inc esi             // ������� � ���������� �������

            // ������������� ������ � ���������� ��������
            cmp bl, '9'
            jle digit_to_decimal
            sub bl, 55          // ��� ���� A-F (A=10, B=11,..., F=15)
            jmp multiply_and_add

            digit_to_decimal :
        sub bl, '0'         // ��� ���� 0-9

            multiply_and_add :
            imul eax, 16        // �������� ������� ��������� �� 16
            add eax, ebx        // �������� ���������� �������� ������� �����

            loop loop_through_string // ��������� ��� ��������� �����

            // ��������� ������ � eax
            mov[result], eax   // ��������� ��������� � ����������
    };

    delete[] cstr; // ����������� ������
    cout << "\n>> |���������� �������������| -> " << result << endl;
}


void oct(string num) {

}


void bin(string num) {

}


// ���� ��������� �������
void homework() {
    int flag = 1;
    string number;
    do {
        Heading();
        cout << "\n                                                 �������� ������" << endl;
        cout << "\n>> |��������� ��� ����������� ���� ������� ���������� � �������� �� � int.|" << endl;
        cout << ">> |x| ������� �����:\n    |\n    | 16 �� ������ - 0x01DE;\n    | 8 �� ������ - 0x0360;\n    | 2 ������ - 0b0110;\n    |\n    | 0 - ����� � ����;\n    |\n" << endl;
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
            cout << "\n\n>> |!| �� ����� �������� ��������!\n" << endl;
        }
    } while (flag != 0);
}


// ������� 16 - 10
uint32_t hex_to_int(std::string inp) {
    auto chinp = inp.c_str();
    int len = inp.length() - 2 > 8 ? 8 : inp.length() - 2;
    uint32_t res = 0;
    __asm {
        // ������������� ���������
        mov ecx, len
        mov ebx, chinp

        // ���� ��������� �����
        lp :
        // �������� ������� � ������� ��������
        xor edx, edx
            mov dl, [ebx + 2]
            // �������� � �������������� �������
            cmp edx, '9' //  ���������� ����������� ������ � '9'.
            jg alph // ���� ������ ������ '9', �� �� ��������� � ����� alph, ��� ����������� �������������� ���� A-F � ��������������� ���������� ��������.

            sub dl, '0' // ���� ������ ������ ��� ����� '9', �� �� ����������� ����� � �� ���������� ��������.
            jmp body // ��������� � ����� body ����� ��������������

            alph :
            sub dl, ('A' - 10)  // ����������� ����� A-F � ��������������� ���������� �������� (A=10, B=11,..., F=15)

            // ��������� � ���������� ����������
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


// ������� 2 - 10
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
        mov eax, format; ��������� ������(0 - ����������, 1 - ��������, 2 - ������������, 3 - �����������������)
        mov ebx, inp; ��������� �� ������

        cmp eax, 3; ���� ������ = 3, �� �����������������
        je hex_conversion

        cmp eax, 1; ���� ������ = 1, �� ��������
        je bin_conversion

        cmp eax, 2; ���� ������ = 2, �� ������������
        je octal_conversion

        ; ��� �����������
        jmp decimal_conversion

        hex_conversion :
        add ebx, 2; ���������� "0x" ��� ������������������ �����
            mov res, 0; ������������� ���������
            hex_loop :
        xor edx, edx
            movzx edx, byte ptr[ebx]; ��������� ������
            cmp edx, 0; ���� ����� ������, �������
            je end_conversion

            cmp edx, '0'
            jl invalid_char
            cmp edx, '9'
            jg check_alpha
            sub edx, '0'; ����������� �����
            jmp shift_left

            check_alpha :
        cmp edx, 'A'
            jl invalid_char
            cmp edx, 'F'
            jg invalid_char
            sub edx, 'A' - 10; ����������� ����� � �����
            jmp shift_left

            invalid_char :
        mov res, -1
            jmp end_conversion

            shift_left :
        shl res, 4; �������� ��������� �� 4 ����
            add res, edx; ��������� ����� � ����������
            inc ebx; ��������� � ���������� �������
            jmp hex_loop

            bin_conversion :
        add ebx, 2; ���������� "0b" ��� ��������� �����
            mov res, 0; ������������� ���������
            bin_loop :
        xor edx, edx
            movzx edx, byte ptr[ebx]; ��������� ������
            cmp edx, 0; ���� ����� ������, �������
            je end_conversion

            sub edx, '0'; ����������� ������ � 0 ��� 1
            shl res, 1; �������� ��������� �� 1 ���(�������� �� 2)
            add res, edx; ��������� ����� � ����������
            inc ebx; ��������� � ���������� �������
            jmp bin_loop

            octal_conversion :
        add ebx, 2; ���������� "0" ��� ������������� �����
            mov res, 0; ������������� ���������
            octal_loop :
        xor edx, edx
            movzx edx, byte ptr[ebx]; ��������� ������
            cmp edx, 0; ���� ����� ������, �������
            je end_conversion

            cmp edx, '0'
            jl invalid_char
            cmp edx, '7'
            jg invalid_char
            sub edx, '0'; ����������� ������ � �����
            shl res, 3; �������� ��������� �� 3 ����(�������� �� 8)
            add res, edx; ��������� ����� � ����������
            inc ebx; ��������� � ���������� �������
            jmp octal_loop

            decimal_conversion :
        mov res, 0; ������������� ��������� ��� �����������
            decimal_loop :
        xor edx, edx
            movzx edx, byte ptr[ebx]; ��������� ������
            cmp edx, 0; ���� ����� ������, �������
            je end_conversion

            cmp edx, '0'
            jl invalid_char
            cmp edx, '9'
            jg invalid_char
            sub edx, '0'; ����������� ������ � �����

            ; ��� ����������� �������� �� 10
            mov eax, res; ��������� ���������
            imul eax, eax, 10; �������� �� 10
            mov res, eax; ��������� ��������� ������� � res

            add res, edx; ��������� ����� � ����������
            inc ebx; ��������� � ���������� �������
            jmp decimal_loop

            end_conversion :
    }

    return res;
}


// ��������� ���� ���������� �� ����������� ��������
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
        cout << "\t|\n\n\t|>> |Type|-> ����������";
        return 10;
    }
    else if (hex) {
        cout << "\t|\n\n|>> |Type|-> �����������������";
        return 16;
    }
    else if (bin) {
        cout << "\t|\n\n|>> |Type|-> ��������";
        return 2;
    }
    else {
        cout <<"\t|\n\n|>> |!| ������!";
        return 0;
    }
}


// ���� �������� �������
void classwork() {
    int flagChose, flagType;
    char num[100];
    do {
        Heading();
        cout << "\n                                             ������� �������:" << endl;
        cout << "\n>> |x| �������� �������:\n    |\n    | 1 - ����������� �������;\n    | 2 - �������� ����� � int;\n    | 0 - ����� � ����;\n    |" << endl;
        cout << "\n$->: ";
        // �������� �� ���� ����� � ��� ����������
        if (!(cin >> flagChose)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            flagChose = -1;
            system("cls");
            cout << "\n>> |!| �� ����� ������������ ��������!\n" << endl;
            continue;
        }
        switch (flagChose) {
        case 1:
            //system("cls");
            cout << "\n\t==����������� �������==";
            cout << "\n\t|\n\t|>> |x| ������� �����:\n\t|$->: ";
            cin >> num;
            get_type(num);
            delay();
            system("cls");
            break;
        case 2:
            cout << "\n\t==�������� ����� � int==";
            cout << "\n\t|\n\t|>> |x| ������� �����:\n\t|$->: ";
            cin >> num;
            if (strlen(num) > 10) {
                system("cls");
                cout << "\n>> |!| ������������\n" << endl;
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
                cout << "\n>> |!| �� ����� ������������ ��������!\n" << endl;
            }
        } while (flagChose != 0);
    }


// ������� ����
void mainMenu() {
    int flagChose;
    do {
        Heading();
        cout << "\n                                                 ����" << endl;
        cout << "\n>> |x| �������� ������:\n    |\n    | 1 - �������� ������;\n    | 2 - ������������ ������;\n    | 0 - �����;\n    |" << endl;
        cout << "\n$->: ";
        // �������� �� ���� ����� � ��� ����������
        if (!(cin >> flagChose)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            flagChose = -1;
            system("cls");
            cout << "\n>>|!| �� ����� ������������ ��������!\n" << endl;
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
            cout << "\n>> |!| �� ����� ������������ ��������!\n" << endl;
        }
    } while (flagChose != 0);
}


// ����� �����
int main() {
    system("chcp 1251 > nul");
    mainMenu();
    system("cls");
    cout << "\n\n>> |!| ���������� ���������!\n\n";
    return 0;
}