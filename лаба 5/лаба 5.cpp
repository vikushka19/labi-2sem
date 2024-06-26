﻿#include <iostream>
#include <cmath>
using namespace std;

class D_Complex {
private:
    double real;
    double imag;

public:
    //конструкторы
    D_Complex() : real(0), imag(0) {//по умолчанию
        //cout << "Конструктор по умолчанию вызван" << endl;
    }

    D_Complex(double re, double im) : real(re), imag(im) {//полного заполнения
        //cout << "Конструктор полного заполнения вызван" << endl;
    }

    D_Complex(const D_Complex& other) : real(other.real), imag(other.imag) {
        //cout << "Конструктор копирования вызван" << endl;//копирования
    }

    D_Complex& operator=(const D_Complex& other) {//оператор присваивания копированием
        real = other.real;
        imag = other.imag;
        //cout << "Оператор присваивания вызван" << endl;
        return *this;//возвращает объект
    }

    ~D_Complex() {
        cout << "Деструктор вызван" << endl;//деструктор
    }

    D_Complex& operator++() {//префиксный
        real++;
        return *this;
    }

    D_Complex operator++(int) {//постфиксный
        D_Complex num = *this;
        real++;
        return num;
    }

    D_Complex operator+(const D_Complex& other) {//+
        return D_Complex(real + other.real, imag + other.imag);
    }

    D_Complex& operator+=(const D_Complex& other) {//+=
        real += other.real;
        imag += other.imag;
        return *this;
    }

    D_Complex operator*(const D_Complex& other) {//*
        return D_Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    D_Complex& operator*=(const D_Complex& other) {//*=
        double new_real = real * other.real - imag * other.imag;
        imag = real * other.imag + imag * other.real;
        real = new_real;
        return *this;
    }
    /* friend в объявлении указывает, что функция может иметь прямой доступ к закрытым членам класса,
    даже если она сама не является членом этого класса.*/
    friend ostream& operator<< (ostream& out, const D_Complex& c) {//вывод
        if (c.real == 0 and c.imag == 0) {
            out << 0;
        }
        else if (c.real == 0 and c.imag != 0) {
            out<< c.imag << "i";
        }
        else if (c.real != 0 and c.imag == 0) {
            out << c.real;                                          
        }
        else if (c.imag < 0) {
            out<< c.real << " - " << -c.imag << "i";
        }
        else {
            out << c.real << " + " << c.imag << "i";
        }
        return out;
    }

    friend istream& operator>> (istream& in, D_Complex& c) {//ввод
        in >> c.real >> c.imag;
        return in;
    }

    friend double scalarC(D_Complex a, D_Complex b);//скалярное произведение

    friend int qC(const D_Complex& c);

    double absC() {
        return sqrt(real * real + imag * imag);//модуль
    }
};
//ВНЕШНИЕ ФУНКЦИИ

//функция нахождения скалярного произведения двух радиус-векторов
double scalarC(D_Complex a,D_Complex b) {
    return (a.real * b.real + a.imag * b.imag);
}

//максимальный модуль
D_Complex MAX_absC(D_Complex a, D_Complex b) {
    cout << "Модуль числа num1: " << a.absC() << endl;
    cout << "Модуль числа num2: " << b.absC() << endl;

    cout << "Комплексное число с максимальным модулем: ";
    if (a.absC() > b.absC()) {
        cout << a << endl;
        return a;
    }
    else if (a.absC() < b.absC()) {
        cout << b << endl;
        return b;
    }
    else {
        cout << "Числа равны." << endl;
    }
}
//функция нахождения квадранта, в котором находится радиус-вектор
int qC(const D_Complex& c) {
    if (c.real == 0 && c.imag == 0)
        return 1;
    if (c.real == 0) {
        if (c.imag > 0)
            return 2;
        if (c.imag < 0)
            return 4;
    }
    if (c.imag == 0) {
        if (c.real >= 0)
            return 1;
        if (c.real < 0)
            return 3;
    }
    else if (c.real > 0 && c.imag > 0)
        return 1;
    else if (c.real < 0 && c.imag > 0)
        return 2;
    else if (c.real < 0 && c.imag < 0)
        return 3;
    else
        return 4;
}

int main() {
    setlocale(LC_ALL, "RU");
    D_Complex num1;
    D_Complex num2(3, 4);
    D_Complex num3 = num2; //конструктор копирования 
    D_Complex num4;
    num4 = num3; //оператор присваивания 

    cout << "Введите комплексное число (действительная и мнимая части через пробел): ";
    cin >> num1;

    cout << "Число 1: " << num1 << endl;
    cout << "Число 2: " << num2 << endl;
    cout << "Число 3: " << num3 << endl;
    cout << "Число 4: " << num4 << endl;

    //Операции с числами: *,*=,+,+=
    cout << "num1 * num2: " << num1 * num2 <<endl;
    num4 *= num1;
    cout << "num4 *= num1: " << num4 << endl;
    cout << "num1 + num3: " << num1 + num3 << endl;
    num3 += num1;
    cout << "num3 += num1: " << num3 << endl;

    //скалярное произведение двух комплексных чисел
    cout << "Скалярное произведение num1 и num2: " << scalarC(num1, num2) << endl;

    //число с максимальным модулем
    D_Complex maximum = MAX_absC(num1, num2);
    
    //определение квадранта, в котором находится радиус-вектор
    cout << "Квадрант числа 1: " << qC(num1) << endl;

    D_Complex pre_increment = ++num1; //префиксный инкремент
    cout << "Число 1 после префиксного инкремента: " << pre_increment << endl;

    D_Complex post_increment = num1++; //постфиксный инкремент
    cout << "Результат постфиксного инкремента: " << post_increment << endl;
    cout << "Число 1 после постфиксного инкремента: " << num1 << endl;

    //определение квадранта, в котором находится радиус-вектор
    cout << "Квадрант числа 1 после применения инкрементов: " << qC(num1) << endl;

    return 8;
}