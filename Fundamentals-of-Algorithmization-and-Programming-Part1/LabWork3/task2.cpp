#include <iostream>

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

double pow(double x, int target) {
  double mult = x;
  double n = 1.0;

  while (n != target) {
    x *= mult;
    n++;
  }

  return x;
}

double rowSpread() {
  double result = 0.0;
  double term = 0.0;
  int n = 0;

  double tolerance = 1e-3;
  do {
    n++;
    term = 1 / pow(2, n) + 1 / pow(3, n);
    result += term;
  } while (term > tolerance);

  return result;
}

int main() {
  std::cout << "Задание 2. Найти сумму ряда с заданной точностью, равной 10e-3\n";
  std::cout << "Выполнил: Гаркуша Игорь, группа 453502\n";

  while (true) {
    std::cout << "Для начала работы программы введите 1, для завершения введите 0:\n";
    int inputValue = readIntegerInLine();

    if (inputValue != 1 && inputValue != 0) {
      std::cout << "Некорректный ввод! Попробуйте еще раз.\n";
      continue;
    }

    if (inputValue == 0) {
      break;
    }

    double res = rowSpread();
    std::cout << "Результат работы программы: " << res << '\n';
  }
  return 0;
}