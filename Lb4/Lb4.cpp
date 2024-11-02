#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>


using namespace std;


// Функция перемножения переменных
void mulltiple() {
    cout << "Пункт 2.1:\nПеремножения переменных" << endl;
    float num1, num2, result;
    // Ввод чисел
    cout << "Введите два числа для умножения: ";
    cin >> num1 >> num2;

    // Использование встроенного ассемблера для умножения
    __asm {
        fld num1    // Загрузка перевого числа в стек FPU в st[0]
        fmul num2      // Умножение переменной st[0] с переменной num2
        fstp result // Сохранение результата в переменную result
    }

    // Вывод результата
    cout << "Результат умножения = " << result << "\n-----------------------------------------------------------------\n" << endl;
}


// Функция для расчета периметра окружности
void Perimtr() {
    cout << "Пункт 2.2:\nРасчет периметра окружности" << endl;
    float radius, result;
    cout << "Введите радиус: ";
    cin >> radius;

    __asm {
        fldpi     // Загрузить r в стек FPU в st[0]
        fld radius         // Загрузить pi в стек FPU в st[1]
        fmul st(0), st(1)  // Умножить pi на r
        fadd st(0), st(0)  // Удвоить результат (2 * pi * r)
        fstp result    // Сохранить результат
    }

    cout << "Периметр равен = " << result << "\n-----------------------------------------------------------------\n" << endl;
}


// Функция для расчета поверхности сферы
void Surface() {
    cout << "Пункт 2.3:\nРасчет поверхности сферы" << endl;
    float radius, result;
    cout << "Введите радиус: ";
    cin >> radius;

    __asm {
        fldpi              // Загрузить pi в стек FPU
        fld radius         // Загрузить r в стек FPU
        fmul st(1), st(0)  // r^2
        fmul st(0), st(1)  // pi * r^2
        fadd st(0), st(0)  // Удвоить
        fadd st(0), st(0)  // Еще раз удвоить (4 * pi * r^2)
        fstp result        // Сохранить результат
    }

    cout << "Площадь поверхности равна: " << result << "\n-----------------------------------------------------------------\n" << endl;
}

// Функция для перевода координат из декартовой системы в полярную и обратно
void convElem() {
    cout << "Пункт 2.4:\nПеревод координат из декартовой системы в полярную и обратно" << endl;
    float x, y, r, theta;
    cout << "Введите координаты (x, y): ";
    cin >> x >> y;

    // Перевод из декартовой в полярную
    __asm {
        fld x          // Загрузить x в стек
        fmul st(0), st(0)  // x^2
        fld y          // Загрузить y в стек
        fmul st(0), st(0)  // y^2
        faddp st(1), st(0) // x^2 + y^2
        fsqrt          // sqrt(x^2 + y^2)
        fstp r         // Сохранить результат в r

        fld y          // Загрузить y в стек
        fld x          // Загрузить x в стек
        fpatan         // Вычислить arctan(y/x)
        fstp theta     // Сохранить результат в theta
    }

    cout << "\nПолярные координаты: r = " << r << ", theta = " << theta << "\n        <------------------------------->" << endl;

    // Перевод из полярной в декартову
    float newX, newY;

    __asm {
        fld r          // Загрузить r
        fld theta      // Загрузить theta
        fsin           // Вычислить sin(theta)
        fmul st(0), st(1)  // r * sin(theta)
        fstp newY      // Сохранить результат в newY

        fld r          // Загрузить r
        fld theta      // Загрузить theta
        fcos           // Вычислить cos(theta)
        fmul st(0), st(1)  // r * cos(theta)
        fstp newX      // Сохранить результат в newX
    }

    cout << "Декартовые координаты: x = " << newX << ", y = " << newY << "\n-----------------------------------------------------------------\n" << endl;
}

// Функция для нахождения среднего значения последовательности
void averagResult() {
    cout << "Пункт 2.5:\nНахождения среднего значения последовательности" << endl;
    int n;
    cout << "Введите количество элементов: ";
    cin >> n;

    // Выделение памяти под n массив чисел
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    float sum = 0.0, avg;

    cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        sum += arr[i];
    }

    // Вычисление среднего значения
    __asm {
        fld sum          // Загрузить сумму в стек FPU
        fild n           // Загрузить количество элементов (целое число) в стек FPU
        fdiv             // Выполнить деление sum на n
        fstp avg         // Сохранить результат в avg
    }

    cout << "Среднее значение последовательности: " << avg << "\n-----------------------------------------------------------------\n" << endl;

    // Отчистка памяти
    delete[] arr;
}

// SSE

// Функция умножения упакованных чисел
void multiplyPackedNumbers() {
    cout << "Пункт 3.1:\nУмножения упакованных чисел" << endl;
    float result[4], ar1[4] = { 1.0, 2.0, 3.0, 4.0 }, ar2[4] = { 5.0, 6.0, 7.0, 8.0 };

    /*
    for (int i = 0; i < 4; i++) {
        ar1[i] = arr1[i];
        ar2[i] = arr2[i];
    }
    */
    __asm {
        movups xmm0, ar1      // Загружаем массив ar1 в xmm0
        movups xmm1, ar2       // Загружаем массив ar2 в xmm1
        mulps xmm0, xmm1     // Умножаем xmm0 (A) на xmm1 (B)
        movups result, xmm0   // Сохраняем результат в массив result
    }

    cout << "Результат умножения упакованных чисел: ";
    for (int i = 0; i < 4; i++) {
        cout << result[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------\n" << endl;
}

// Функция преобразования последовательности целых int чисел в последовательность float
void int_to_float() {
    cout << "Пункт 3.2:\nПреобразования последовательности целых int чисел в последовательность float" << endl;
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
        movups xmm0, intArray  // Загружаем массив целых чисел в xmm0
        cvtdq2ps xmm0, xmm0    // Преобразуем целые числа в float
        movups floatArray, xmm0 // Сохраняем результат в массив floatArray
    }

    cout << "Преобразование int в float: ";
    for (int i = 0; i < 4; i++) {
        cout << floatArray[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------\n" << endl;
}

// Функция вычисления последовательности обратных значений чисел
void reciprocals() {
    cout << "Пункт 3.3:\nВычисления последовательности обратных значений чисел" << endl;
    float result[4], values[4] = { 1.0, 2.0, 4.0, 8.0 };
    /*
    for (int i = 0; i < 4; i++) {
        values[i] = arr[i];
    }
    */

    __asm {
        movups xmm0, values        // Загружаем массив значений в xmm0
        rsqrtps xmm0, xmm0        // Вычисляем приближенные обратные значения
        mulps xmm0, xmm0          // Умножаем на значения для получения истинных обратных значений
        movups result, xmm0       // Сохраняем результат
    }

    cout << "Обратные значения чисел: ";
    for (int i = 0; i < 4; i++) {
        cout << result[i] << " ";
    }
    cout << "\n-----------------------------------------------------------------\n" << endl;
}


void new_func() {

    // Задание: y = (sinx + cosx)/(sinx - cosx)
    cout << "Доп задание." << endl;
    float y, x;
    // cout << "Введите X: ";
     //cin >> x;
    float pi = M_PI;
    float xArr[8] = { pi / 4, pi / 2, 3 * pi / 2, pi, -3 * pi / 4, -pi / 2, -pi / 4, 2 * pi };

    for (int i = 0; i < 8; i++) {
        x = xArr[i];
        cout << "x = " << x << endl;
        __asm {
            fld  x                // Загружаем x в стек
            fsin                  // Вычисляем sin(x)
            fld  x                // Загружаем x сверху
            fcos                  // Вычисляем cos(x)
            fadd                  // Суммируем послдение два элемента в стеке - sin(x) и cos(x)
            fld x                 // Загружаем x свпреху
            fsin                  // Вычисляем sin(x) 
            fld x                 // Загружаем x свреху
            fcos                  // Вычисляем cos(x)
            fsub                  // Вычитаем послдение два элемента в стеке - cos(x) из sin(x)

            fdiv;                 // Делим последние два элемента стека (sin(x) + cos(x)) на (sin(x) - cos(x))
            fstp y                // Сохраняем результат

        }

        cout << "Ответ: " << y << endl;
    }

    /*
    __asm {
        fld  x                // Загружаем x в стек
        fsin                  // Вычисляем sin(x)
        fld  x                // Загружаем x сверху
        fcos                  // Вычисляем cos(x)
        fadd                  // Суммируем послдение два элемента в стеке - sin(x) и cos(x)

        fld x                 // Загружаем x свпреху
        fsin                  // Вычисляем sin(x)
        fld x                 // Загружаем x свреху
        fcos                  // Вычисляем cos(x)
        fsub                  // Вычитаем послдение два элемента в стеке - cos(x) из sin(x)

        fdiv;                 // Делим последние два элемента стека (sin(x) + cos(x)) на (sin(x) - cos(x))
        fstp y                // Сохраняем результат

    }

    cout << "Ответ: " << y << endl;
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
    mulltiple(); // запуск функции с перемножением переменных
    Perimtr();   // функция вычисления периметра
    Surface();   // запуск функции расчета поверхности сферы
    convElem();  // запуск функции перевода декартовой системы в обычную и обратно
    averagResult();    // запуск функции среднего значения
    multiplyPackedNumbers();
    int_to_float();
    reciprocals();
    */
    new_func();
    return 0;
}
