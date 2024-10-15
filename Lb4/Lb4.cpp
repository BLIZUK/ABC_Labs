#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


using namespace std;


// ������� ������������ ����������
void mulltiple() {
    cout << "����� 2.1:\n������������ ����������" << endl;
    float num1, num2, result;
    // ���� �����
    cout << "������� ��� ����� ��� ���������: ";
    cin >> num1 >> num2;

    // ������������� ����������� ���������� ��� ���������
    __asm {
        fld num1    // �������� �������� ����� � ���� FPU � st[0]
        fmul num2      // ��������� ���������� st[0] � ���������� num2
        fstp result // ���������� ���������� � ���������� result
    }

    // ����� ����������
    cout << "��������� ��������� = " << result << "\n-----------------------------------------------------------------\n" << endl;
}


// ������� ��� ������� ��������� ����������
void Perimtr() {
    cout << "����� 2.2:\n������ ��������� ����������" << endl;
    float radius, result;
    cout << "������� ������: ";
    cin >> radius;

    __asm {
        fldpi     // ��������� r � ���� FPU � st[0]
        fld radius         // ��������� pi � ���� FPU � st[1]
        fmul st(0), st(1)  // �������� pi �� r
        fadd st(0), st(0)  // ������� ��������� (2 * pi * r)
        fstp result    // ��������� ���������
    }

    cout << "�������� ����� = " << result << "\n-----------------------------------------------------------------\n" << endl;
}


// ������� ��� ������� ����������� �����
void Surface() {
    cout << "����� 2.3:\n������ ����������� �����" << endl;
    float radius, result;
    cout << "������� ������: ";
    cin >> radius;

    __asm {
        fldpi              // ��������� pi � ���� FPU
        fld radius         // ��������� r � ���� FPU
        fmul st(1), st(0)  // r^2
        fmul st(0), st(1)  // pi * r^2
        fadd st(0), st(0)  // �������
        fadd st(0), st(0)  // ��� ��� ������� (4 * pi * r^2)
        fstp result        // ��������� ���������
    }

    cout << "������� ����������� �����: " << result << "\n-----------------------------------------------------------------\n" << endl;
}

// ������� ��� �������� ��������� �� ���������� ������� � �������� � �������
void convElem() {
    cout << "����� 2.4:\n������� ��������� �� ���������� ������� � �������� � �������" << endl;
    float x, y, r, theta;
    cout << "������� ���������� (x, y): ";
    cin >> x >> y;

    // ������� �� ���������� � ��������
    __asm {
        fld x          // ��������� x � ����
        fmul st(0), st(0)  // x^2
        fld y          // ��������� y � ����
        fmul st(0), st(0)  // y^2
        faddp st(1), st(0) // x^2 + y^2
        fsqrt          // sqrt(x^2 + y^2)
        fstp r         // ��������� ��������� � r

        fld y          // ��������� y � ����
        fld x          // ��������� x � ����
        fpatan         // ��������� arctan(y/x)
        fstp theta     // ��������� ��������� � theta
    }

    cout << "\n�������� ����������: r = " << r << ", theta = " << theta << "\n        <------------------------------->" << endl;

    // ������� �� �������� � ���������
    float newX, newY;

    __asm {
        fld r          // ��������� r
        fld theta      // ��������� theta
        fsin           // ��������� sin(theta)
        fmul st(0), st(1)  // r * sin(theta)
        fstp newY      // ��������� ��������� � newY

        fld r          // ��������� r
        fld theta      // ��������� theta
        fcos           // ��������� cos(theta)
        fmul st(0), st(1)  // r * cos(theta)
        fstp newX      // ��������� ��������� � newX
    }

    cout << "���������� ����������: x = " << newX << ", y = " << newY << "\n-----------------------------------------------------------------\n" << endl;
}

// ������� ��� ���������� �������� �������� ������������������
void averagResult() {
    cout << "����� 2.5:\n���������� �������� �������� ������������������" << endl;
    int n;
    cout << "������� ���������� ���������: ";
    cin >> n;

    // ��������� ������ ��� n ������ �����
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    float sum = 0.0, avg;

    cout << "������� " << n << " ����� �����: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sum += arr[i];
    }

    // ���������� �������� ��������
    __asm {
        fld sum          // ��������� ����� � ���� FPU
        fild n           // ��������� ���������� ��������� (����� �����) � ���� FPU
        fdiv             // ��������� ������� sum �� n
        fstp avg         // ��������� ��������� � avg
    }

    cout << "������� �������� ������������������: " << avg << "\n-----------------------------------------------------------------\n" << endl;

    // �������� ������
    delete[] arr;
}

// SSE

// ������� ��������� ����������� �����
void multiplyPackedNumbers() {
    cout << "����� 3.1:\n��������� ����������� �����" << endl;
    float result[4], ar1[4] = { 1.0, 2.0, 3.0, 4.0 }, ar2[4] = { 5.0, 6.0, 7.0, 8.0 };

    /*
    for (int i = 0; i < 4; i++) {
        ar1[i] = arr1[i];
        ar2[i] = arr2[i];
    }
    */
    __asm {
        movups xmm0, ar1      // ��������� ������ ar1 � xmm0
        movups xmm1, ar2       // ��������� ������ ar2 � xmm1
        mulps xmm0, xmm1     // �������� xmm0 (A) �� xmm1 (B)
        movups result, xmm0   // ��������� ��������� � ������ result
    }

    cout << "��������� ��������� ����������� �����: ";
    for (int i = 0; i < 4; i++) {
        cout << result[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------\n" << endl;
}

// ������� �������������� ������������������ ����� int ����� � ������������������ float
void int_to_float() {
    cout << "����� 3.2:\n�������������� ������������������ ����� int ����� � ������������������ float" << endl;
    int intArray[4] = { 1, 2, 3, 4 };
    float floatArray[4];

    /*
    int intArray[4];
    float floatArray[4];
    for (int i = 0; i < 4; i++) {
        intArray[i] = intar[i];
    }
    */

    __asm {
        movups xmm0, intArray  // ��������� ������ ����� ����� � xmm0
        cvtdq2ps xmm0, xmm0    // ����������� ����� ����� � float
        movups floatArray, xmm0 // ��������� ��������� � ������ floatArray
    }

    cout << "�������������� int � float: ";
    for (int i = 0; i < 4; i++) {
        cout << floatArray[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------\n" << endl;
}

// ������� ���������� ������������������ �������� �������� �����
void reciprocals() {
    cout << "����� 3.3:\n���������� ������������������ �������� �������� �����" << endl;
    float result[4], values[4] = { 1.0, 2.0, 4.0, 8.0 };
    /*
    for (int i = 0; i < 4; i++) {
        values[i] = arr[i];
    }
    */

    __asm {
        movups xmm0, values        // ��������� ������ �������� � xmm0
        rsqrtps xmm0, xmm0        // ��������� ������������ �������� ��������
        mulps xmm0, xmm0          // �������� �� �������� ��� ��������� �������� �������� ��������
        movups result, xmm0       // ��������� ���������
    }

    cout << "�������� �������� �����: ";
    for (int i = 0; i < 4; i++) {
        cout << result[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------\n" << endl;
}


void new_func() {

    // �������: y = (sinx + cosx)/(sinx - cosx)
    cout << "��� �������." << endl;
    float y, x;
    // cout << "������� X: ";
     //cin >> x;
    float pi = M_PI;
    float xArr[8] = { pi / 4, pi / 2, 3 * pi / 2, pi, -3 * pi / 4, -pi / 2, -pi / 4, 2 * pi };

    for (int i = 0; i < 8; i++) {
        x = xArr[i];
        cout << "x = " << x << endl;
        __asm {
            fld  x                // ��������� x � ����
            fsin                  // ��������� sin(x)
            fld  x                // ��������� x ������
            fcos                  // ��������� cos(x)
            fadd                  // ��������� ��������� ��� �������� � ����� - sin(x) � cos(x)
            fld x                 // ��������� x �������
            fsin                  // ��������� sin(x) 
            fld x                 // ��������� x ������
            fcos                  // ��������� cos(x)
            fsub                  // �������� ��������� ��� �������� � ����� - cos(x) �� sin(x)

            fdiv;                 // ����� ��������� ��� �������� ����� (sin(x) + cos(x)) �� (sin(x) - cos(x))
            fstp y                // ��������� ���������

        }

        cout << "�����: " << y << endl;
    }

    /*
    __asm {
        fld  x                // ��������� x � ����
        fsin                  // ��������� sin(x)
        fld  x                // ��������� x ������
        fcos                  // ��������� cos(x)
        fadd                  // ��������� ��������� ��� �������� � ����� - sin(x) � cos(x)

        fld x                 // ��������� x �������
        fsin                  // ��������� sin(x)
        fld x                 // ��������� x ������
        fcos                  // ��������� cos(x)
        fsub                  // �������� ��������� ��� �������� � ����� - cos(x) �� sin(x)

        fdiv;                 // ����� ��������� ��� �������� ����� (sin(x) + cos(x)) �� (sin(x) - cos(x))
        fstp y                // ��������� ���������

    }

    cout << "�����: " << y << endl;
    */
}


int  main() {
    system("chcp 1251 > nul");
    /*
    int intArr[4];
    float floatArr1[4], floatArr2[4], result[4];
    for (int i = 0; i < 4; i++) {
        intArr[i] = 0 + i + 1;
        float fi = i;
        floatArr1[i] = 0.0 + fi + 1.0;
        floatArr2[i] = 4.0 + fi + 1.0;
    }
    for (int i = 0; i < 4; i++) {
        cout << floatArr1[i] << " ";

    }
    */
    /*
    mulltiple(); // ������ ������� � ������������� ����������
    Perimtr();   // ������� ���������� ���������
    Surface();   // ������ ������� ������� ����������� �����
    convElem();  // ������ ������� �������� ���������� ������� � ������� � �������
    averagResult();    // ������ ������� �������� ��������
    multiplyPackedNumbers();
    int_to_float();
    reciprocals();
    */
    new_func();
    return 0;
}
