#include "../utils/header-files/utils.h"
#include "../db/header-files/db.h"
#include "../scripts/header-files/random.h"
#include "../elastic-search/header-files/elastic.h"

void viewAllApplicants(pqxx::connection& conn) {
    pqxx::work txn(conn);

    pqxx::result result = txn.exec(
        "SELECT a.applicant_id, a.fullname, c.city_name, ad.street, ad.house, ad.apartment, "
        "       COALESCE(AVG(agrd.grade), 0) AS average_grade "
        "FROM public.applicants a "
        "JOIN public.address ad ON a.address_id = ad.address_id "
        "JOIN public.cities c ON ad.city_id = c.city_id "
        "LEFT JOIN public.applicant_grades agrd ON a.applicant_id = agrd.applicant_id "
        "GROUP BY a.applicant_id, a.fullname, c.city_name, ad.street, ad.house, ad.apartment "
        "ORDER BY a.applicant_id"
    );

    if (result.empty()) {
        std::cout << "Абитуриенты отсутствуют в базе данных." << '\n';
        return;
    }

    std::cout << "\nСписок всех абитуриентов:\n";
    std::cout << "ID | Полное имя | Город | Улица | Дом | Квартира | Средний балл\n";

    for (const auto& row : result) {
        std::cout << row["applicant_id"].as<int>() << " | "
                << row["fullname"].as<string>() << " | "
                << row["city_name"].as<string>() << " | "
                << row["street"].as<string>() << " | "
                << row["house"].as<string>() << " | "
                << row["apartment"].as<string>() << " | "
                << std::fixed << std::setprecision(1)
                << row["average_grade"].as<double>() << "\n";
    }
}

void addApplicant(pqxx::connection& conn) {
    Applicant applicant;
    std::cout << "Введите ФИО: ";
    std::getline(std::cin, applicant.fullname);

    std::cout << "Введите город проживания: ";
    std::getline(std::cin, applicant.city);

    int street_type;
    std::cout << "Введите тип ввода для улицы (2 - как строка, 1 - целое число, 0 - дробное число): ";
    while (true) {
        street_type = ReadIntegerInLine();
        if (street_type != 0 && street_type != 1 && street_type != 2) {
            std::cout << "Введите 0, 1 либо 2." << '\n';
            continue;
        }
        applicant.street_type = street_type;
        break;
    } 

    if (street_type == 2) {
        std::cout << "Введите название улицы: ";
        std::getline(std::cin, applicant.street_name);
    }
    else if (street_type == 1) {
        std::cout << "Введите номер улицы (целое число): ";
        int street_int;
        while (true) {
            street_int = ReadIntegerInLine();
            if (street_int == -INF) {
                std::cout << "Введите целое число." << '\n';
                continue;
            }
            applicant.street.street_int = street_int;
            break;
        } 
    } else if (street_type == 0) {
        std::cout << "Введите номер улицы (дробное число): ";
        double street_double;
        while (true) {
            street_double = ReadDoubleInLine();
            if (street_double == -INF) {
                std::cout << "Введите номер в формате числа с плавающей точкой." << '\n';
                continue;
            }
            applicant.street.street_double = street_double;
            break;
        } 
    }

    std::cout << "Введите номер дома: ";
    int house;
    while (true) {
        house = ReadIntegerInLine();
        if (house < 0) {
            std::cout << "Введите целое число\n";
            continue;
        }
        applicant.house = house;
        break;
    }

    std::cout << "Введите номер квартиры: ";
    int apartment;
    while (true) {
        apartment = ReadIntegerInLine();
        if (apartment < 0) {
            std::cout << "Введите целое число\n";
            continue;
        }
        applicant.apartment = apartment;
        break;
    }

    string grades_str;
    getGrades(grades_str);
    applicant.grades_str = grades_str;

    pqxx::work txn(conn);

    pqxx::result city_result = txn.exec("SELECT city_id FROM public.cities WHERE city_name = " + txn.quote(applicant.city) + " LIMIT 1");
    if (city_result.empty()) {
        city_result = txn.exec("INSERT INTO public.cities (city_name) VALUES (" + txn.quote(applicant.city) + ") RETURNING city_id");
    }
    int city_id = city_result[0][0].as<int>();

    pqxx::result address_result = txn.exec(
        "SELECT address_id FROM public.address WHERE city_id = " + txn.quote(city_id) +
        " AND street = " + txn.quote(applicant.street_name) +
        " AND house = " + txn.quote(applicant.house) +
        " AND apartment = " + txn.quote(applicant.apartment) + " LIMIT 1"
    );
    if (address_result.empty()) {
        address_result = txn.exec(
            "INSERT INTO public.address (city_id, street, house, apartment) VALUES (" +
            txn.quote(city_id) + ", " + txn.quote(applicant.street_name) + ", " +
            txn.quote(applicant.house) + ", " + txn.quote(applicant.apartment) +
            ") RETURNING address_id"
        );
    }
    int address_id = address_result[0][0].as<int>();

    pqxx::result person_result = txn.exec(
        "INSERT INTO public.applicants (fullname, address_id) VALUES (" +
        txn.quote(applicant.fullname) + ", " + txn.quote(address_id) +
        ") RETURNING applicant_id"
    );
    int applicant_id = person_result[0][0].as<int>();

    std::stringstream grades_stream(applicant.grades_str);
    std::string grade;
    while (grades_stream >> grade) {
        int grade_value = std::stoi(grade);
        txn.exec("INSERT INTO public.applicant_grades (applicant_id, grade) VALUES (" + txn.quote(applicant_id) + ", " + txn.quote(grade_value) + ")");
    }

    txn.commit();
    createApplicantInIndex(applicant, applicant_id);
}

void addMultipleApplicants(pqxx::connection& conn) {
    std::cout << "Как вы хотите добавить абитуриента?\n";
    std::cout << "1 - Ручной ввод\n";
    std::cout << "2 - Автоматически (случайные данные)\n";
    int choice;
    while (true) {
        choice = ReadIntegerInLine();
        if (choice != 1 && choice != 2) {
            std::cout << "Введите 1 или 2." << '\n';
            continue;
        }
        break;
    } 

    std::cout << "Сколько абутуриентов вы хотите добавить?: ";
    int applicantCount;
    while (true) {
        applicantCount = ReadIntegerInLine();
        if (applicantCount == -INF) {
            std::cout << "Введите целое число." << '\n';
            continue;
        }
        break;
    } 

    if (choice == 1) {
        for (int i = 0; i < applicantCount; ++i) {
            std::cout << "\nДобавление абитуриента " << (i + 1) << " вручную:" << '\n';
            addApplicant(conn);  
        }
    } else if (choice == 2) {
        AddRandomApplicants(applicantCount);
    }
    std::cout << "Абитуриент(-ы) успешно добавлен(-ы)." << '\n';
}

void deleteApplicant(pqxx::connection& conn) {
    viewAllApplicants(conn);
    int applicant_id;

    pqxx::work txn(conn);

    std::cout << "Введите id абитуриента для удаления: ";
    while (true) {
        applicant_id = ReadIntegerInLine();
        if (applicant_id == -INF) {
            std::cout << "Введите целое число" << '\n';
            continue;
        }
        if (!CheckValidID(txn, applicant_id)) {
            std::cout << "Введите существующий id." << '\n';
            continue;
        }
        break;
    }
    
    txn.exec("DELETE FROM public.applicants WHERE applicant_id = " + txn.quote(applicant_id));
    
    txn.commit();
    std::cout << "Абитуриент успешно удален." << '\n';
    deleteApplicantInIndex(applicant_id);
}

void deleteAllApplicants(pqxx::connection& conn) {
    pqxx::work txn(conn);

    txn.exec("DELETE FROM public.applicants;");
    txn.commit();

    std::cout << "Все абитуриенты успешно удалены." << '\n';
    deleteAllApplicantsInIndex(); 
}

void editApplicantField(pqxx::connection& conn) {
    viewAllApplicants(conn); 
    int applicant_id;

    pqxx::work txn(conn);

    std::cout << "Введите ID абитуриента, которого хотите изменить: ";
    while (true) {
        applicant_id = ReadIntegerInLine();
        if (applicant_id == -INF) {
            std::cout << "Введите целое число." << '\n';
            continue;
        }
        if (!CheckValidID(txn, applicant_id)) {
            std::cout << "Введите существующий id." << '\n';
            continue;
        }
        break;
    } 

    std::cout << "Введите цифру для изменения:\n"
          << "1 - ФИО   \n"
          << "2 - Город\n"
          << "3 - Улица\n"
          << "4 - Дом\n"
          << "5 - Квартира\n"
          << "Ваш выбор: ";

    int choice;
    while (true) {
        choice = ReadIntegerInLine();
        if (choice == -INF) {
            std::cout << "Введите целое число." << '\n';
            continue;
        }
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
            std::cout << "Введите цифру от 1 до 5!" << '\n';
            continue;
        }
        break;
    } 

    string column_name;

    switch (choice) {
        case 1: column_name = "fullname"; break;
        case 2: column_name = "city"; break;
        case 3: column_name = "street"; break;
        case 4: column_name = "house"; break;
        case 5: column_name = "apartment"; break;
    }

    std::cout << "Введите новое значение: "; 
    string new_value;
    if (choice == 1 || choice == 2 || choice == 3) {
        std::getline(std::cin, new_value);
    }
    else if (choice == 5 || choice == 4) {
        while (true) {
            std::getline(std::cin, new_value); 
            if (!ValidIntegerString(new_value)) {
                std::cout << "Некорректный ввод. Введите целое число.\n";
                continue;
            }
            break; 
        }
    } 

    if (column_name == "fullname") {
        txn.exec(
            "UPDATE public.applicants SET fullname = " + txn.quote(new_value) + 
            " WHERE applicant_id = " + txn.quote(applicant_id)
        );
    }
    else if (column_name == "city") {
        pqxx::result city_result = txn.exec("SELECT city_id FROM public.cities WHERE city_name = " + txn.quote(new_value));
        int city_id;
        if (city_result.empty()) {
            txn.exec("INSERT INTO public.cities (city_name) VALUES (" + txn.quote(new_value) + ")");
            pqxx::result new_city_result = txn.exec("SELECT city_id FROM public.cities WHERE city_name = " + txn.quote(new_value));
            city_id = new_city_result[0][0].as<int>();
        } else {
            city_id = city_result[0][0].as<int>();
        }

        txn.exec(
            "UPDATE public.address SET city_id = " + txn.quote(city_id) + 
            " WHERE address_id = (SELECT address_id FROM public.applicants WHERE applicant_id = " + txn.quote(applicant_id) + ")"
        );
    }
    else if (column_name == "street") {
        txn.exec(
            "UPDATE public.address SET street = " + txn.quote(new_value) + 
            " WHERE address_id = (SELECT address_id FROM public.applicants WHERE applicant_id = " + txn.quote(applicant_id) + ")"
        );
    }
    else if (column_name == "house") {
        txn.exec(
            "UPDATE public.address SET house = " + txn.quote(new_value) + 
            " WHERE address_id = (SELECT address_id FROM public.applicants WHERE applicant_id = " + txn.quote(applicant_id) + ")"
        );
    }
    else if (column_name == "apartment") {
        txn.exec(
            "UPDATE public.address SET apartment = " + txn.quote(new_value) + 
            " WHERE address_id = (SELECT address_id FROM public.applicants WHERE applicant_id = " + txn.quote(applicant_id) + ")"
        );
    }

    txn.commit();
    std::cout << "Данные об абитуриенте изменены успешно!\n";
    updateApplicantInIndex(applicant_id, column_name, new_value);      
}