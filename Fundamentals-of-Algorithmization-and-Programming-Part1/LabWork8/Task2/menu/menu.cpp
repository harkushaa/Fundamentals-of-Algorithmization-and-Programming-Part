#include "../db/header-files/db.h"
#include "../constants/constants.h"
#include "../utils/header-files/utils.h"
#include "../elastic-search/header-files/elastic.h"

void menu(pqxx::connection& conn) {
    int choice;
    while (true) {
        std::cout << "\n===== Меню для управления абитуриентами =====\n";
        std::cout << "1. Просмотреть всех абитуриентов\n";
        std::cout << "2. Добавить нового абитуриента\n";
        std::cout << "3. Поиск\n";
        std::cout << "4. Вывести абитуриентов из Гомеля (средний балл >= 4.5)\n";
        std::cout << "5. Редактировать запись абитуриента\n";
        std::cout << "6. Удалить запись абитуриента\n";
        std::cout << "7. Удалить все записи\n";
        std::cout << "8. Выход\n";
        std::cout << "Введите ваш выбор: ";
        choice = ReadIntegerInLine();
        if (choice != AvailableOperations[0] && choice != AvailableOperations[1] && choice != AvailableOperations[2]
            && choice != AvailableOperations[3] && choice != AvailableOperations[4] && choice != AvailableOperations[5]
            && choice != AvailableOperations[6] && choice != AvailableOperations[7]) {
            std::cout << "Некорректный ввод. Попробуйте еще раз.\n";
            continue;
        }
        system("clear");
        if (choice == 1) {
            viewAllApplicants(conn);
            continue;
        } else if (choice == 2) {
            addMultipleApplicants(conn);
            continue;
        } else if (choice == 3) {
            searchViaElastic();
            continue;
        } else if (choice == 4) {
            searchEmployeeByCityAndGrade("Гомель", 4.5, 10.0);
            continue;
        } else if (choice == 5) {
            editApplicantField(conn);
            continue;
        } else if (choice == 6) {
            deleteApplicant(conn);
            continue;
        } else if (choice == 7) {
            deleteAllApplicants(conn);
            continue;
        } else if (choice == 8) {
            std::cout << "Завершение работы программы.\n";
            return;
        }
    }
}