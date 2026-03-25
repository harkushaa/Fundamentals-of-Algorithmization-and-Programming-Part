#include <iostream>
#include <cmath>

double func (double valueX) {
    double res, a, b, fi;
    std::cout << "Function: " << '\n';
    std::cout << "y(x) = 2/3 * a + sin^2(x) - 3b/4 * cos^2(fi * x)\n\n";
    std::cout << "Please enter a, b and fi values: " << '\n';
    std::cin >> a >> b >> fi;
    res = (double) 2 / (double) 3 * a * pow(sin(valueX), 2) - ( 3 * b / 4 * pow(cos(fi * valueX), 2));
    return res;
}

int main () {
    std::cout << "Please enter 1, 2 or 3 in order to declare how f(x) function will be calculated.";
    std::cout << "\n1 stands for: f(x) = 2 * x";
    std::cout << "\n2 stands for: f(x) = x ^ 3";
    std::cout << "\n3 stands for: f(x) = x / 3\n\n";
    std::cout << "Now please make a choice (1, 2 or 3): ";
    int choice; std::cin >> choice;

    double z;
    std::cout << "\nNow please enter z value: ";
    std::cin >> z;
    double x;
    if (z < 0) {x = z;}
    else if (z >= 0) {x = sin(z);}
    std::cout << "\nValue of x equals to: " << x << '\n';

    switch(choice) {
        case 1:
            std::cout << "Attention! Using f(x) = 2 * x function\n";
            x = 2 * x;
            break;
        case 2:
            std::cout << "Attention! Using f(x) = x ^ 3 function\n";
            x = pow(x, 3);
            break;
        case 3:
            std::cout << "Attention! Using f(x) = x / 3 function\n";
            x = x / 3;
            break;
    }

    std::cout << "Now x equals to: " << x << '\n' << '\n';

    double res = func(x);
    std::cout << "\nResult: " << res << '\n' << '\n';
    return 0;
}