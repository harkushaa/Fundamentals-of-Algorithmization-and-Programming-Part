#include <iostream>

const int INF = 2000000000;

int readIntegerInLine(void) {
    int inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        return -INF;
    }
    return inputValue;
}

int getOrder(int val) {
    int res = 0;
    while (val) {
        res++;
        val = val / 10;
    }
    return res;
}

double pow(double x, int n) {
    if (n == 1) {
        return x;
    }
    if (n & 1) {
        return pow(x, n - 1) * x;
    }
    double h = pow(x, n / 2);
    return h * h;
}

bool isArmstrong(int x) {
    int order = getOrder(x);
    int temp = x, sum = 0;

    while (temp) {
        int r = temp % 10;
        sum += pow(r, order);
        temp /= 10;
    }
    return sum == x;
}

int main() {
    std::cout << "Задание 7. Программа, для нахождения чисел Армстронга меньше заданной границы\n";
    std::cout << "Выполнил: Гаркуша Игорь, группа 453502\n";

    while (true) {
        std::cout << "Введите 1 для запуска программы, 0 для завершения\n";
        int type = readIntegerInLine();
        if (type != 1 && type != 0) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        if (type == 0) {
            break;
        }
        std::cout << "Введите границу (до какого числа искать числа Армстронга):\n";
        int r;
        while (true) {
            r = readIntegerInLine();
            if (r <= 153) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        for (int i = 0; i < r; i++) {
            if (isArmstrong(i)) {
                std::cout << i << " является числом Армстронга" << '\n';
            }
        }
    }
    return 0;
}