#include <iostream>

const int INF = 2000000000;

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
    std::cout << "Задание 1. Программа, вычисляющая с помощью цикла while сумму (ai-bi)^2 для i от 1 до 30\n";
    std::cout << "Выполнил: Гаркуша Игорь, группа 453502\n";

    while (true) {
        std::cout << "Пожалуйста, введите 1 для запуска программы, либо 0 для ее окончания:\n";
        int inputValue = readIntegerInLine();

        if (inputValue != 1 && inputValue != 0) {
            std::cout << "Некорректный ввод! Попробуйте еще раз.\n";
            continue;
        }

        if (inputValue == 0) {
            break;
        }

        int res = 0;
        int i = 1;
        while (i <= 30) {
            if (!(i % 2)) {
                res += (i / 2 - i * i * i) * (i / 2 - i * i * i);
            } else {
                res += (i - i * i) * (i - i * i);
            }
            i++;
        }
        std::cout << "Результат работы программы: " << res << '\n';

    }
    return 0;
}