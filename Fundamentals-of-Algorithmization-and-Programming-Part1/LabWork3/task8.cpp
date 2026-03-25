#include <iostream>
#include <limits.h>

const int INF = 2000000000;

int stipulateOverflow(int a, int b) {
  if (((b > 0) && (a > (INT_MAX - b))) ||
      ((b < 0) && (a < (INT_MIN - b)))) {
    return -INF;
  } else {
    return a + b;
  }
}

int readIntegerInLine() {
    int inputValue;
    if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
        std::cin.clear();
        while (std::cin.get() != '\n') {
        }
        return -INF;
    }
    return inputValue;
}

int main() {
    std::cout << "Задание 8. Программа, для нахождения суммы без использования вещественной арифметики\n";
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
        std::cout << "Введите кол-во членов для подсчета:\n";
        int n;
        while (true) {
            n = readIntegerInLine();
            if (n < 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }

        int res = 0, p1 = 1, p2 = 1;
        bool flag = true;
        for (int i = 0; i < n; i++) {
            std::cout << "Введите a" << "[" << i << "]" << " член последовательности:\n";
            int a;
            while (true) {
                a = readIntegerInLine();
                if (a == -INF) {
                    std::cout << "Некорректный ввод\n";
                    continue;
                }
                break;
            }
            int curr = a * p1 * p2;
            res = stipulateOverflow(res, curr);
            if (res == -INF) {
                flag = false;
                std::cout << "Переполнение\n";
                break;
            }
            p1 *= 2;
            p2 *= -1;
        }
        if (flag) {
            std::cout << "Результат работы программы: " << res << '\n';
        }
    }
    return 0;
}