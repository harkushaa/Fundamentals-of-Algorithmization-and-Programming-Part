#include <iostream>

int main () {
    double a = -13.8, b = 8.9, c = 25.0;
    int N;
    std::cout << "Please enter N value (int values can be taken): ";
    std::cin >> N;
    double y;
    switch (N) {
        case 2:
            y = b * c - a * a;
            std::cout << "Result of calculating this (b * c - a * a = ) equals to " << y;
            break;
        case 56:
            y = b * c;
            std::cout << "Result of calculating this (b * c = ) equals to " << y;
            break;
        case 7:
            y = a * a * a * a * a * a * a + c;
            std::cout << "Result of calculating this (a^7 + c = ) equals to " << y;
            break;
        case 3:
            y = a - b * c;
            std::cout << "Result of calculating this (a - b * c = ) equals to " << y;
            break;
        default:
            y = (a + b) * (a + b) * (a + b);
            std::cout << "Result of calculating this ((a + b)^3 = ) equals to " << y;
    }
    return 0;
}