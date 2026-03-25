#include <iostream>
#include <string>
#include <cmath>

#include "../../general/header-files/utils.h"
#include "../../general/header-files/constants.h"

#include "../header-files/constants.h"

using std::string;

string ConvertToTrinary(int number) {
    string res;
    while (number > 0) {  // O(n)
        res = std::to_string(number % 3) + res;
        number /= 3;
    }
    unsigned int bitsAmount = slaves;
    while (res.length() < bitsAmount) res = "0" + res;  // O(n)
    return res;
}

void EncodeAllBarrels(string*& barrels, const unsigned int total) {
    for (int indx = 0; indx < total; ++indx) {  // O(n)
        barrels[indx] = ConvertToTrinary(indx + 1);
    }
}

unsigned int ConvertFromTrinaryToDecimal(string& str) {
    unsigned int res = 0; 

    for (int i = slaves - 1; i >= 0; --i) {  // O(n)
        res += (str[i] - '0') * pow(base, slaves - 1 - i);
    }

    return res;
}

void ShowBarrelsList(const unsigned int pos, char unit, string*& barrels) {
    unsigned int cnt = 0;
    for (unsigned int i = 0; i < barrelsAmount; ++i) {  // O(n)
        if (barrels[i][pos] == unit) {
            if (cnt % 10 == 0) std::cout << '\n';
            std::cout << ConvertFromTrinaryToDecimal(barrels[i]) << ' ';
            cnt++;
        }
    }
}

void ShowAliveSlaves(bool (&alive)[5]) {
    for (unsigned int i = 0; i < slaves; ++i) {  // O(n)
        if (alive[i]) 
            std::cout << alive[i] << ' ';
    }
}

void ExecuteTask() {
    string* barrels = new string[barrelsAmount];
    EncodeAllBarrels(barrels, barrelsAmount);   
    
    unsigned int indx = 0;
    string res = "-----";
    bool slavesAlive[slaves] = {true, true, true, true, true};
    std::cout << "Первые 24 часа подошли к концу. Давайте узнаем, кто из слуг умер.\n";
    for (unsigned int i = 0; i < slaves; ++i) {  // O(n)
        std::cout << "Слуга номер " << (i + 1) << " пил из бочек под номерами: ";
        ShowBarrelsList(i, base_units[indx], barrels);
        std::cout << '\n';
        std::cout << "Умер ли он? Введите 1 если да, 0 если нет: ";
        int type;
        while (true) {  // O(m), где m - потенциальное количество итераций, которые могут понадобиться для ввода
            type = readIntegerInLine();
            if (type == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        if (type == 0) {
            continue;
        }
        //меняем результат
        slavesAlive[i] = false;
        res[i] = base_units[indx];
    }
    indx += 1;
    std::cout << "Прошло 48 часов, из живых остались слуги под номерами: ";
    ShowAliveSlaves(slavesAlive);
    std::cout << "кто из оставшихся слуг умер?\n";
    for (unsigned int i = 0; i < slaves; ++i) {  // O(n)
        if (slavesAlive[i] == false) continue;
        std::cout << "Слуга номер " << (i + 1) << " пил из бочек под номерами:";
        ShowBarrelsList(i, base_units[indx], barrels);
        std::cout << '\n';
        std::cout << "Умер ли он? Введите 1 если да, 0 если нет: ";
        std::cout << '\n';
        int type;
        while (true) {  // O(m), где m - потенциальное количество итераций, которые могут понадобиться для ввода
            type = readIntegerInLine();
            if (type == -INF) {
                std::cout << "Некорректный ввод\n";
                continue;
            }
            break;
        }
        if (type == 0) {
            continue;
        }
        //меняем результат
        slavesAlive[i] = false;
        res[i] = base_units[indx];
    }   
    indx += 1;
    for (unsigned int i = 0; i < slaves; ++i) {  // O(n)
        if (slavesAlive[i] == false) continue;
        res[i] = base_units[indx]; 
    }
    std::cout << "Бочка, которую вы отравили была под номером: " << ConvertFromTrinaryToDecimal(res) << '\n';
};