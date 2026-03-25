#include "binary.h"
#include "elastic-search/api.h"
#include "employee_functions.h"
#include "algorithms.h"

FILE *databaseFile = fopen("employees.bin", "rb+");

employee* getEmployees(int& n) {
    fseek(databaseFile, 0L, SEEK_END);
    if (ftell(databaseFile) == SEEK_SET) {
        fwrite(&n, sizeof(int), 1, databaseFile);
    }
    fseek(databaseFile, 0L, SEEK_SET);
    fread(&n, sizeof(int), 1, databaseFile);
    employee* arr = new employee[n];
    fread(arr, sizeof(employee), n, databaseFile);
    return arr;
}

bool emptyDb() {
    int n = 0;
    fseek(databaseFile, 0L, SEEK_END);
    if (ftell(databaseFile) == SEEK_SET) {
        fwrite(&n, sizeof(int), 1, databaseFile);
    }
    fseek(databaseFile, 0L, SEEK_SET);
    fread(&n, sizeof(int), 1, databaseFile);
    return n == 0;
}

void truncateFile(int n) {
    fseek(databaseFile, 0L, SEEK_SET);
    char* ch = (char*)malloc(4 + n * sizeof(employee));
    fread(ch, sizeof(char), 4 + n * sizeof(employee), databaseFile);
    FILE *db = fopen("employees.bin", "wb");
    fwrite(ch, sizeof(char), 4 + n * sizeof(employee), db);
    fclose(db);
    free(ch);
}

void displayDatabase() {
    std::cout << "Сотрудники, записи о которых хранятся в базе данных:\n";
    int n = 0;
    employee* arr = getEmployees(n); 
    for (int i = 0; i < n; i++) {
        std::cout << "Сотрудник " << i << ": ";
        display(arr[i]);
    }
    delete[] arr;
}

void clearDatabase(employee*& arr, int& n) {
    FILE* databaseFile = fopen("employees.bin", "wb");
    if (databaseFile == nullptr) {
        std::cout << "Не удалось открыть файл базы данных для очистки.\n";
        return;
    }

    int zero = 0;
    fwrite(&zero, sizeof(int), 1, databaseFile);

    fclose(databaseFile);
    std::cout << "Бинарный файл очищен.\n";

    if (arr != nullptr) {
        free(arr);  
        arr = nullptr; 
        n = 0;        
        std::cout << "Массив сотрудников очищен.\n";
    } else {
        std::cout << "Массив уже был пуст.\n";
    }       

    DeleteAllEmployeesInIndex();
}

void addToDatabase(employee*& arr, int& n) {
    char choice;
    do {
        int fileEmployeeCount = 0;
        fseek(databaseFile, 0L, SEEK_END);
        if (ftell(databaseFile) == SEEK_SET) {
            fwrite(&fileEmployeeCount, sizeof(int), 1, databaseFile);
        }
        
        std::cout << "Введите данные о сотруднике, которого хотите добавить в файл.\n";
        employee e;
        read(arr, n, e);
        
        fseek(databaseFile, 0L, SEEK_SET);
        fread(&fileEmployeeCount, sizeof(int), 1, databaseFile);
        
        fileEmployeeCount++;
        fseek(databaseFile, 0L, SEEK_SET);
        fwrite(&fileEmployeeCount, sizeof(int), 1, databaseFile);
        
        fseek(databaseFile, 4L + (fileEmployeeCount - 1) * (long)sizeof(employee), SEEK_SET);
        fwrite(&e, sizeof(employee), 1, databaseFile);
        
        std::cout << "Сотрудник добавлен в файл.\n";
        
        n++;
        arr = (employee*)realloc(arr, n * sizeof(employee));
        arr[n - 1] = e;
        std::cout << "Сотрудник добавлен в массив.\n";

        AddDocumentToElastic(e);

        std::cout << "Хотите добавить еще одного сотрудника? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');
}

void deleteFromDatabase(employee*& arr, int& n) {
    if (emptyDb()) {
        std::cout << "База данных пустая, невозможно ничего удалить.\n";
        return;
    }
    displayDatabase();
    std::cout << "Введите номер сотрудника, которого хотите удалить из файла: ";
    int ndel;
    ndel = ReadIntegerInLine();

    //удаление из файла
    int fileEmployeeCount = 0;
    fseek(databaseFile, 0L, SEEK_SET);
    fread(&fileEmployeeCount, sizeof(int), 1, databaseFile);

    if (ndel < 0 || ndel >= fileEmployeeCount) {
        std::cout << "Неверный номер сотрудника.\n";
        return;
    }

    fileEmployeeCount--;
    fseek(databaseFile, 0L, SEEK_SET);
    fwrite(&fileEmployeeCount, sizeof(int), 1, databaseFile);

    fseek(databaseFile, 4L + ndel * (long)sizeof(employee), SEEK_SET);
    while (ftell(databaseFile) < 4L + fileEmployeeCount * (long)sizeof(employee)) {
        fseek(databaseFile, (long)sizeof(employee), SEEK_CUR);
        employee e;
        fread(&e, sizeof(employee), 1, databaseFile);
        fseek(databaseFile, -(long)sizeof(employee) * 2, SEEK_CUR);
        fwrite(&e, sizeof(employee), 1, databaseFile);
    }
    truncateFile(fileEmployeeCount);
    std::cout << "Сотрудник удален из базы данных.\n";

    employee removedEmployee = arr[ndel];
    for (int i = ndel; i < n - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    n--;
    arr = (employee*)realloc(arr, n * sizeof(employee));
    std::cout << "Сотрудник удален из массива.\n";

    DeleteDocumentFromElastic(removedEmployee);
}

void editDatabase(employee* arr, int n) {
    if (emptyDb()) {
        std::cout << "База данных пустая, нет сотрудников для редактирования.\n";
        return;
    }
    displayDatabase();
    std::cout << "Введите номер сотрудника, информацию о котором хотите изменить: ";
    int ndel;
    ndel = ReadIntegerInLine();
    int fileEmployeeCount = 0;
    fseek(databaseFile, 0L, SEEK_SET);
    fread(&fileEmployeeCount, sizeof(int), 1, databaseFile);
    if (ndel < 0 || ndel >= fileEmployeeCount) {
        std::cout << "Неверный номер сотрудника.\n";
        return;
    }
    fseek(databaseFile, 4L + ndel * (long)sizeof(employee), SEEK_SET);
    employee e;
    fread(&e, sizeof(employee), 1, databaseFile);
    changeField(arr, n, e);
    fseek(databaseFile, -(long)sizeof(employee), SEEK_CUR);
    fwrite(&e, sizeof(employee), 1, databaseFile);
    std::cout << "Информация о сотруднике изменена.\n";

    arr[ndel] = e;
    std::cout << "Информация о сотруднике обновлена в массиве.\n";

    AddDocumentToElastic(e);
}

void loadDatabase(employee*& arr, int& n) {
    FILE* databaseFile = fopen("employees.bin", "rb");
    if (!databaseFile) {
        std::cout << "Не удалось открыть файл базы данных для чтения.\n";
        return;
    }

    fread(&n, sizeof(int), 1, databaseFile);

    if (n > 0) {
        arr = (employee*)malloc(n * sizeof(employee));
        if (arr == nullptr) {
            std::cout << "Не удалось выделить память для массива сотрудников.\n";
            fclose(databaseFile);
            return;
        }

        fread(arr, sizeof(employee), n, databaseFile);
    }

    fclose(databaseFile);
    std::cout << "База данных загружена из файла.\n";
}