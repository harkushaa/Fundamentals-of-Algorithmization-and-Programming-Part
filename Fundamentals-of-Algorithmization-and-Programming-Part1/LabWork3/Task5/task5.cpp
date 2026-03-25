#include <iostream>

const int INF = 2000000000;
const long double PI = 3.14159265358979383246;

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

long double fAbs(long double x) {
    return (x >= 0 ? x : -x);
}

double normalizeAngle(double x) {
    while (x > 2 * PI) x -= 2 * PI;
    while (x < -2 * PI) x += 2 * PI;
    return x;
}

double cos(double x) {
    x = normalizeAngle(x);
    double result = 1.0;
    double term = 1.0;
    int n = 0;

    double tolerance = 1e-10;
    do {
        n++;
        term *= -x * x / (2 * n * (2 * n - 1));
        result += term;
    } while (fAbs(term) > tolerance);

    return result;
}

long double acos(long double x) {
    long double left = 0.0;
    long double right = PI;
    long double mid;

    double tolerance = 1e-10;
    while (right - left > tolerance) {
        mid = (left + right) / 2.0;
        if (cos(mid) < x) {
            right = mid;
        }
        else {
            left = mid;
        }
    }

    return (left + right) / 2.0;
}

double sin(double x) {
    x = normalizeAngle(x);
    double result = x;
    double term = x;
    int n = 0;

    double tolerance = 1e-10;
    do {
        n++;
        term *= -x * x / ((2 * n) * (2 * n + 1));  //следующий член ряда: (-1)^n * x^(2n+1) / (2n+1)!
        result += term;
    } while (fAbs(term) > tolerance);

    return result;
}

double exp(double x) {
    double result = 1.0;
    double term = 1.0;
    int n = 1;

    double tolerance = 1e-10;
    do {
        term *= x / n;  //член ряда: (x^n / n!)
        result += term;
        n++;
    } while (fAbs(term) > tolerance);

    return result;
}

int main() {
    std::cout << "Задание 5. Программа, для нахождения приближенного корня уравнения arccos(e^(-x)) - 2sin(x) = 0 на пром. [1, 3]\n";
    std::cout << "Выполнил: Гаркуша Игорь, группа 453502\n";

    while (true) {
        std::cout << "Введите 1 для начала работы программы, 0 для завершения:\n";
        int type = readIntegerInLine();
        if (type != 1 && type != 0) {
            std::cout << "Некорректный ввод\n";
            continue;
        }
        if (type == 0) {
            break;
        }
        std::cout << "Введите кол-во частей, на которые разбить промежуток (целое число > 0):\n";
        int n;
        while (true) {
            n = readIntegerInLine();
            if (n <= 0) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }

        long double step = (double)(3.0 - 1.0) / (double) n;

        long double best = 1.0e18;
        long double root = 0;

        long double tolerance = 1e-10;

        for (long double x = 1; x - tolerance <= 3; x += step) {
            long double value = acos(exp(-x)) - 2 * sin(x);

            std::cout << x << " " << value << '\n';

            if (fAbs(value) < best) {
                best = fAbs(value);
                root = x;
            }
        }
        std::cout << "Приближенный корень найден и равен " << root << "\n";
    }
}