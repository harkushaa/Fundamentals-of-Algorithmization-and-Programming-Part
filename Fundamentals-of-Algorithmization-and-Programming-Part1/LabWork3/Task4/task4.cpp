#include <iostream>
#include <cmath>

const int INF = 2000000000;

int readIntegerInLine() {
  int inputValue;
  if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
    std::cin.clear();
    while (std::cin.get() != '\n') {
    }
    return -INF;
  }
  return inputValue;
}

double readDoubleInLine() {
  double inputValue;
  if (!(std::cin >> inputValue) || (std::cin.peek() != '\n')) {
    std::cin.clear();
    while (std::cin.get() != '\n') {
    }
    return -INF;
  }
  return inputValue;
}

double pow(double x, int d) {
  if (d == 1) {
    return x;
  }
  if (d & 1) {
    return pow(x, d - 1) * x;
  }
  double h = pow(x, d / 2);
  return h * h;
}

double factorial(double x) {
  if (x == 0) {
    return 1;
  }
  return factorial(x - 1) * x;
}

double y(double x) {
  return (exp(x) - exp(-x)) / 2;
}

double taylor(double x, int n) {
  double res = 0;

  int i = 0;
  while (i <= n) {
    res += pow(x, 2 * i + 1) / factorial(2 * i + 1);
    i += 1;
  }

  return res;
}

int main() {
  std::cout << "Задание 4. Программа, сравнивающая значение функции (e^x-e^(-x))/2, вычисленное разложением в ряд и с помощью стандартных функций\n";
  std::cout << "Выполнил: Гаркуша Игорь, группа 453502\n";

  while (true) {
    std::cout << "Введите 1 для запуска программы, 0 для ее завершения:\n";
    int inputValue = readIntegerInLine();
    if (inputValue != 0 && inputValue != 1) {
      std::cout << "Некорректный ввод!\n";
      continue;
    }
    if (inputValue == 0) {
      break;
    }
    std::cout << "Введите кол-во членов ряда:\n";
    int n;
    while (true) {
      n = readIntegerInLine();
      if (n < 0) {
        std::cout << "Некорректный ввод\n";
        continue;
      }
      break;
    }
    std::cout << "Введите количество чисел, для которых нужно вычислить значение функции (целое неотрицательное число)\n";
    int m;
    while (true) {
      m = readIntegerInLine();
      if (m < 0) {
        std::cout << "Неверный формат ввода.\n";
        continue;
      }
      break;
    }
    for (int i = 1; i <= m; i++) {
      std::cout << "Введите число, для которого нужно вычислить значение функции(от 0.1 до 1.0):\n";
      double x;
      while (true) {
        x = readDoubleInLine();
        if (x < 0.1 || x > 1) {
          std::cout << "Некорретный ввод\n";
          continue;
        }
        break;
      }
      std::cout << "Значение функции, вычисленное разложением в ряд равно " << taylor(x, n) << '\n';
      std::cout << "Значение функции, вычисленное с использованием стандартной библиотеки: " << y(x) << '\n';
    }
  }
  return 0;
}