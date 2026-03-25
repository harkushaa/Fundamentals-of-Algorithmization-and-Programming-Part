#include <iostream>
// #include <cmath>
// #include <gtest/gtest.h>

using namespace std;


int main () {
    int arr[2] = {2, 4};

    cout << arr[6];
}


/*
int add (int a, int b) {

    return a + b; fsfl;ks
}

TEST (add, positive) {

    ASSERT_EQ(10, add(5, 5));
}

TEST (add, negative) {

    ASSERT_EQ(-10, add(-5, -5));
}

int main (int  argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}
*/


/*
int main() {
    int a[2] = {1, 4};
    cout << a[5];
    double start, end, step;
    cout << "Введите начальное значение x: ";
    cin >> start; // Задаем исходное значение переменной
    cout << "Введите конечное значение x: ";
    cin >> end; // Задаем конечно значение переменной
    cout << "Введите шаг: ";
    cin >> step; // Задаем шаг, с которым с которым будет изменяться аргумент
    for (double x = start; x <= end; x += step) {
    double y = sin(x); // функция y = sin(x)
    std::cout << x << " | " << y << std::endl; // Выводим значения функции для каждого аргумента (x | y)
    }
    return 0;
}
*/