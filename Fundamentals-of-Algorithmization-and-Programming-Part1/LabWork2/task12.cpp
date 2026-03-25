#include <iostream>

const long double PI = 3.14159265358979383246;

long double Abs(long double x) {return(x >= 0 ? x : -x);}

double sqrt(double x) {
    double low, high;

    if (x >= 1) {low = 1, high = x;}
    else {low = x; high = 1;}

    double tolerance = 1e-9;
    while (high - low > tolerance) {
        double mid = (low + high) / 2;
        if (mid * mid  <= x) {
            low = mid;
        }
        else {
            high = mid;
        }
    }
    return high;
}

double cbrt(double x) {
    double low = -1e12, high = 1e12;

    double tolerance = 1e-9;
    while (high - low > tolerance) {
        double mid = (low + high) / 2;
        if (mid * mid * mid <= x) {
            low = mid;
        }
        else {
            high = mid;
        }
    }
    return low;
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
    } while (Abs(term) > tolerance);

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

int main() {
    double p, q;
    std::cout << "Введите значения коэффицентов p и q: ";
    std::cin >> p >> q;
    double Q = (p / 3) * (p / 3) * (p / 3) + (q / 2) * (q / 2);
    //одно действительное решение и два комплексных.
    if (Q > 0) {
        double a1 = -q / 2 + sqrt(Q);
        double b1 = -q / 2 - sqrt(Q);
        a1 = cbrt(a1);
        b1 = cbrt(b1);

        std::cout << "Действительный корень уравнения: " << a1 + b1 << " ";
    }
    //одно кратное действительное решение.
    else if (Q == 0) {
        double a1 = -q / 2;
        a1 = cbrt(a1);

        std::cout << "Действительные корни уравнения: " << 2 * a1 << " " << -a1;
    }
    //три действительных корня.
    else {
        double x1, x2, x3;
        x1 = 2 * sqrt(-p / 3) * cos(acos(-q / 2 * (3 / -p) * sqrt(3 / -p)) / 3);
        x2 = 2 * sqrt(-p / 3) * cos(acos(-q / 2 * (3 / -p) * sqrt(3 / -p)) / 3 + 2 * PI / 3);
        x3 = 2 * sqrt(-p / 3) * cos(acos(-q / 2 * (3 / -p) * sqrt(3 / -p)) / 3 - 2 * PI / 3);

        std::cout << "Действительные корни уравнения: " << x1 << " " << x2 << " " << x3;
    }
    return 0;
}