#include <iostream>

const double pi = 3.14159265358979323846;

long double abs(long double a) {
    return a >= 0 ? a : -a;
}

double sqrt(double x) {
    double low, high;
    if (x >= 1) {
        low = 1, high = x;
    } else {
        low = x; high = 1;
    }

    while (high - low > 1e-9) {
        double mid = (low + high) / 2;
        if (mid * mid <= x) {
            low = mid;
        }
        else {
            high = mid;
        }
    }
    return low;
}

long double arcsin(double x) {
    long double res = 0.0;
    long double term = x;
    int n = 1;
    while (abs(term) > 1e-12) {
        res += term;
        term *= x * x * (2 * n - 1) * (2 * n - 1) / ((long double)2 * n * (2 * n + 1));
        n++;
    }
    return res;
}

int main() {
    double x1, y1;
    double x2, y2;
    double x3, y3;
    std::cout << "Введите значения x1 и y1 для вершины A: ";
    std::cin >> x1 >> y1;
    std::cout << '\n' << "Введите значения x2 и y2 для вершины B: ";
    std::cin >> x2 >> y2;
    std::cout << '\n' << "Введите значения x3 и y3 для вершины C: ";
    std::cin >> x3 >> y3;
    double a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    double b = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    double c = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
    std::cout << "Длины сторон треугольника ABC: ";
    std::cout << a << " " << b << " " << c << '\n' << '\n';
    double p = (a + b + c) / 2;
    double heron = sqrt(p * (p - a) * (p - b) * (p - c));
    double h1 = heron * 2 / a;
    double h2 = heron * 2 / b;
    double h3 = heron * 2 / c;
    std::cout << "Высоты треугольника равны: ";
    std::cout << h1 << " " << h2 << " " << h3 << '\n' << '\n';
    double med_a = 0.5 * sqrt(2 * c * c + 2 * b * b - a * a);
    double med_b = 0.5 * sqrt(2 * c * c + 2 * a * a - b * b);
    double med_c = 0.5 * sqrt(2 * a * a + 2 * b * b - c * c);
    std::cout << "Медианы треугольника равны: ";
    std::cout << med_a << " " << med_b << " " << med_c << '\n' << '\n';
    double bis_a = sqrt(b * c * (a + b + c) * (b + c - a)) / (b + c);
    double bis_b = sqrt(a * c * (a + b + c) * (a + c - b)) / (a + c);
    double bis_c = sqrt(a * b * (a + b + c) * (a + b - c)) / (a + b);
    std::cout << "Биссектрисы треугольника равны: ";
    std::cout << bis_a << " " << bis_b << " " << bis_c << '\n' << '\n';
    long double radians_a = arcsin(heron * 2 / b / c);
    long double radians_b = arcsin(heron * 2 / a / c);
    long double radians_c = arcsin(heron * 2 / a / b);
    std::cout << "Углы в радианах: " << radians_a << ' ' << radians_b << ' ' << radians_c << '\n';
    std::cout << "Значения углов в градусах: " << radians_a / pi * 180 << ' ' << radians_b / pi * 180 << ' ' << radians_c / pi * 180 << '\n';
    double R = a * b * c / 4 / heron;
    double r = heron / p;
    std::cout << '\n' << "Значение радуиса, вписанной в треугольник окружности: " << r << '\n';
    std::cout << "Значение радиуса, описанной около треугольника окружности: " << R << '\n' << '\n';
    long double sr = pi * r * r;
    long double sR = pi * R * R;
    std::cout << "Площади вписанной и описанной окружностей равны: " << sr << " и " << sR << '\n';
    long double Cr = 2 * pi * r;
    long double CR = 2 * pi * R;
    std::cout << "Значение длин дуг этих окружностей: " << Cr << " и " << CR << '\n';

    std::cout << '\n' << "Площадь треугольника равна: " << heron << '\n';
    std::cout << "Периметр треугольника равен: " << p * 2 << '\n' << '\n';
}