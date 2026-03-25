#include <iostream>

int main () {
    int x, y;
    std::cout << "Please enter x and y values: ";
    std::cin >> x >> y;
    if (x > y) {y = 0;} else if (x < y) {x = 0;} else {x = y = 0;};
    double a, b, c;
    std::cout << "Please enter a b c values: ";
    std::cin >> a >> b >> c;
    double k;
    std::cout << "Please enter k value: ";
    std::cin >> k;
    if (a > b && a > c) {a = a - k;}
    else if (b > a && b > c) {b = b - k;}
    else if (c > a && c > b) {c = c - k;}
    std::cout << "Value of x: " << x << '\n';
    std::cout << "Value of y: " << y << '\n';
    std::cout << "Value of a: " << a << '\n';
    std::cout << "Value of b: " << b << '\n';
    std::cout << "Value of c: " << c;
    return 0;
}