#include <iostream>
#include <cmath>

const int ERROR = 2000000000;
const double e = 2.71828182845904523536;
const double PI = 3.14159265358979323846;

int readIntegerInLine() {
  int inputValue;
  if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
    std::cin.clear();
    while (std::cin.get() != '\n') {
    }
    return -ERROR;
  }
  return inputValue;
}

double readDoubleInLine() {
  double inputValue;
  if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
    std::cin.clear();
    while (std::cin.get() != '\n') {
    }
    return -ERROR;
  }
  return inputValue;
}

double normalizeAngle(double a) {
    double curr = PI * 2;
    while (curr < std::abs(a)) {
        curr *= 2;
    }
    curr /= 2.0;
    if (a > 0) {
        while (curr > PI * 4) {
            if (a - curr > 0) {
                a -= curr;
            }
            curr /= 2.0;
        }
    } else {
        while (curr > PI * 4) {
            if (a + curr < 0) {
                a += curr;
            }
            curr /= 2.0;
        }
    }
    if (a > 0) {
        while (a > 2 * PI) {
            a -= 2 * PI;
        }
    } else {
        while (a < -2 * PI) {
            a += 2 * PI;
        }
    }
    return a;
}

double mySin(double x) {
    x = normalizeAngle(x);
    double term = x;
    double result = term;
    int n = 1;
    double precision = 1e-5;
    while (std::abs(term) > precision) {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        result += term;
        n++;
    }
    return result;
}

double myCos(double x) {
    x = normalizeAngle(x);
    double term = 1.0;
    double result = term;
    int n = 1;
    double precision = 1e-5;
    while (std::abs(term) > precision) {
      term *= -x * x / ((2 * n - 1) * (2 * n));
      result += term;
      n++;
    }
    return result;
}

long double ln(long double y) {
  long long k =0;
  while (y<1e-2){
      y *= e;
      k--;
  }
  while (y>1e5){
      y /= e;
      k++;
  }
  long double c = (y - 1) / (y + 1);
  long double term = c;
  long double sum = term;
  long double c_sqrt = c * c;

  long double precision = 1e6;
  for (long double n = 3.0 ; n < precision; n += 2){
      term *= c_sqrt;
      sum += term / n;
  }

  return 2 * sum + k;
}

double min(double a, double b, double c) {
  double min = a;
  if (b < min) {
    min = b;
  }
  if (c < min) {
    min = c;
  }
  return min;
}

int main() {
  std::cout << "Задание 6. Программа, для нахождения мин. значения среди функций sin(x), cos(x), ln(x) при заданном x\n";
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

    std::cout << "Задайте x для подсчета зн-ий функций:\n";
    int x;
    while (true) {
      x = readIntegerInLine();
      if (x == -ERROR || x == 0) {
        std::cout << "Некорректный ввод\n";
        continue;
      }
      break;
    }
    double sinx = mySin(x);
    double cosx = myCos(x);
    double lnx = ln(std::abs(x));
    std::cout << "ln(|" << x << "|) = " << lnx; std::cout << '\t'  << "CMATH: " << "ln(|" << x << "|) = " << log(std::abs(x)) << '\n' << '\n';
    std::cout << "sin(" << x << ") = " << sinx; std::cout << '\t' << "CMATH: "<< "sin(" << x << ") = " << sin(x) << '\n' << '\n';
    std::cout << "cos(" << x << ") = " << cosx; std::cout << '\t' << "CMATH: "<< "cos(" << x << ") = " << cos(x) << '\n' << '\n';
    std::cout << "Минимальное значение: " << min(sinx, cosx, lnx) << '\n';
  }
  return 0;
}