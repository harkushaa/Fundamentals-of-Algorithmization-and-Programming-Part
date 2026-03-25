#include <iostream>
#include <iomanip>

int main() {
    double X, Y;

    std::cout << "Введите два вещественных числа: ";
    std::cin >> X >> Y;

    double max = (X > Y) ? X : Y;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Максимальное число: " << max << std::endl;

    return 0;
}