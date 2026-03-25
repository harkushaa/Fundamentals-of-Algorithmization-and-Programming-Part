#include <iostream>

int main() {
    std::cout << "Введите часы и минуты для первого момента времени: ";
    int h1, min1; std::cin >> h1 >> min1;

    std::cout << '\n' << "Введите часы и минуты для второго момента времени: ";
    int h2, min2; std::cin >> h2 >> min2;

    int h = h2 - h1;
    int min = min2 - min1;

    if (min < 0) {min += 60;}
    if (h < 0) {h += 24;}

    if (min2 < min1) {h -= 1;}

    std::cout << '\n' << "Прошел(-ло) " << h << " часа(-ов)" << '\n';
    std::cout << "Прошло(-а) " << min << " минут(-а)";

    return 0;
}