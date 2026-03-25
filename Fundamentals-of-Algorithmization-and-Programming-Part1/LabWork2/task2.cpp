#include <iostream>

int main () {
    long double x, y, z;
    std::cout << "Enter x y z values: ";
    std::cin >> x >> y >> z;
    if (x + y > z && x + z > y && y + z > x) { std::cout << "Exists"; }
    else { std::cout << "Doesn't exists"; }
    return 0;
}