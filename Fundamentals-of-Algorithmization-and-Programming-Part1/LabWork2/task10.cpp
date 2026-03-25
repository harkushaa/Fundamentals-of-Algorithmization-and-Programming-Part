#include <iostream>

double sqrt(double x) {
    if (x < 0) {return -1;}
    if (x == 0) {return 0;}

    double low = 0, high = x;
    double tolerance = 1e-10;

    if (x < 1) {high = 1;}

    while (high - low > tolerance) {
        double mid = (high + low) / 2.0;
        if (mid * mid < x) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return (high + low) / 2.0;
}

double calculateDistance(int x1, int y1, int x2, int y2) {
    double res;
    res = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    return res;
}

double calculateAbs(double x) {return (x >= 0) ? x : -x;}

void solveCircles(double dist, int r1, int r2) {
    if (dist + r1 <= r2) {
        std::cout << "Да" << std::endl;
    } else if (dist + r2 <= r1) {
        std::cout << "Да, но справделиво обратное для двух" << std::endl;
    } else if (dist < r1 + r2 && dist > calculateAbs(r1 - r2)) {
        std::cout << "Фигуры пересекаются" << std::endl;
    } else {
        std::cout << "Ни одно условие не выполнено" << std::endl;
    }
}

int main() {
    int x1, y1, r;
    std::cout << "Введите пожалуйста координаты и радиус для первого круга: ";
    std::cin >> x1 >> y1 >> r;
    int x2, y2, R;
    std::cout << "Введите пожалуйста координаты и радиус для второго круга: ";
    std::cin >> x2 >> y2 >> R;

    double d = calculateDistance(x1, y1, x2, y2);

    solveCircles(d, r, R);

    return 0;
}
