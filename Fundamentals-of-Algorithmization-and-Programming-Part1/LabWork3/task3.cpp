#include <iostream>

const long double PI = 3.14159265358979323846;
const double TOLERANCE = 1e-10;
const int INF = 2000000000;

double abs(double x) {
  return (x >= 0 ? x : -x);
}

double normalizeAngle(double x) {
  while (x > 2 * PI) x -= 2 * PI;
  while (x < -2 * PI) x += 2 * PI;
  return x;
}

double cos(double x) {
  x = normalizeAngle(x);
  double result = 1.0;
  double term = 1.0;
  int n = 0;

  do {
    n++;
    term *= -x * x / (2 * n * (2 * n - 1));
    result += term;
  } while (abs(term) > TOLERANCE);

  return result;
}

double sin(double x) {
  x = normalizeAngle(x);
  double result = x;
  double term = x;
  int n = 0;

  do {
    n++;
    term *= -x * x / (2 * n * (2 * n + 1));
    result += term;
  } while (abs(term) > TOLERANCE);

  return result;
}

void solveFunc() {
  const double kM = 20;
  const double kA = 0;
  const double kB = PI / 2;
  const double h = (kB - kA) / kM;

  for (int i = 0; i <= kM; ++i) {
    double xi = kA + i * h;
    double y = sin(xi) - cos(xi);
    std::cout << "При A = " << i << " значение функции равно " << y << '\n';
  }
}

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

int main() {
  std::cout << "Задание 3. Программа, использующая цикл for для вычисления значений функ-ии y = sin(x) - cos(x)\n";
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

    solveFunc();
  }
  return 0;
}