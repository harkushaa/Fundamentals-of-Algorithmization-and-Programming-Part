#include "api.h"

void AddDocumentToElastic(const employee& e) {
    std::string number_salary_hours = std::to_string(e.service_number) + " " +
                                      std::to_string(e.currency ? e.salary_per_hour.dollars : e.salary_per_hour.euros) + " " +
                                      std::to_string(e.hours_worked);

    nlohmann::json jsonDocument = {
        {"service_number", e.service_number},
        {"name", e.fullname},
        {"salary", e.currency ? e.salary_per_hour.dollars : e.salary_per_hour.euros},
        {"hours_worked", e.hours_worked},
        {"number_salary_hours", number_salary_hours}
    };

    std::string url = "api_url/employees/_doc/" + std::to_string(e.service_number);

    cpr::Response response = cpr::Put(
        cpr::Url{url},
        cpr::Body{jsonDocument.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 201 || response.status_code == 200) {
        std::cout << "Документ успешно добавлен в Elasticsearch с service_number: " << e.service_number << "\n";
    } else {
        std::cerr << "Ошибка при добавлении документа в Elasticsearch:\n"
                  << "HTTP статус: " << response.status_code << "\n"
                  << "Ответ: " << response.text << "\n";
    }
}

void DeleteDocumentFromElastic(const employee& e) {
    std::string url = "api_url/employees/_doc/" + std::to_string(e.service_number);

    cpr::Response response = cpr::Delete(
        cpr::Url{url},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200 || response.status_code == 404) {
        std::cout << "Документ с service_number: " << e.service_number << " успешно удален из Elasticsearch.\n";
    } else {
        std::cerr << "Ошибка при удалении документа из Elasticsearch:\n"
                  << "HTTP статус: " << response.status_code << "\n"
                  << "Ответ: " << response.text << "\n";
    }
}

void DeleteAllEmployeesInIndex() {
    auto response = cpr::Delete(
        cpr::Url{"api_url/employees"},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200 || response.status_code == 201) {
        std::cout << "Все документы успешно удалены из индекса ElasticSearch." << '\n';
    }
}

void AddAllEmployeesFromArray(employee*& arr, int& n) {
    for (int i = 0; i < n; ++i) {
        AddDocumentToElastic(arr[i]);
    }
}

void ParseElasticSearchResponse(const std::string& response) {
    nlohmann::json parsedResponse = nlohmann::json::parse(response);
    auto hits = parsedResponse["hits"]["hits"];

    for (const auto& hit : hits) {
        std::string docId = hit["_id"];
        auto source = hit["_source"];

        employee e;
        e.service_number = source["service_number"];
        e.hours_worked = source["hours_worked"];

        std::string name = source["name"];
        std::strncpy(e.fullname, name.c_str(), sizeof(e.fullname) - 1);
        e.fullname[sizeof(e.fullname) - 1] = '\0';

        if (source["currency"] == true) {
            e.salary_per_hour.dollars = source["salary"];
        } else {
            e.salary_per_hour.euros = source["salary"];
        }

        std::cout << "Имя: " << e.fullname << "\n";
        std::cout << "Номер сотрудника: " << e.service_number << "\n";
        std::cout << "Часы работы: " << e.hours_worked << "\n";
        std::cout << "Зарплата за час: " << (e.currency ? e.salary_per_hour.dollars : e.salary_per_hour.euros) << "\n";
        std::cout << "--------------------------\n";
    }
}

void SearchWithWildcard(const std::string& searchQuery) {
    nlohmann::json requestBody = {
        {
            "query", {
                {"wildcard", {
                    {"number_salary_hours", "*" + searchQuery + "*"}
                }}
            }
        }
    };

    std::string url = "api_url/employees/_search/";

    cpr::Response response = cpr::Post(
        cpr::Url{url},
        cpr::Body{requestBody.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200) {
        ParseElasticSearchResponse(response.text);
    } else {
        std::cout << "Ошибка при отправке запроса:\n"
                  << "HTTP статус: " << response.status_code << "\n"
                  << "Ответ: " << response.text << "\n";
    }
}

void SearchWithRange(const std::string& input) {
    unsigned long dashPos = input.find('-');
    int left = std::stoi(input.substr(0, dashPos));
    int right = std::stoi(input.substr(dashPos + 1));

    nlohmann::json query = {
        {"query", {
            {"bool", {
                {"should", {
                    {{"range", {{"hours_worked", {{"gte", left}, {"lte", right}}}}}},
                    {{"range", {{"salary", {{"gte", left}, {"lte", right}}}}}},
                    {{"range", {{"service_number", {{"gte", left}, {"lte", right}}}}}}
                }}
            }}
        }}
    };

    std::string url = "api_url/employees/_search/";

    cpr::Response response = cpr::Post(
        cpr::Url{url},
        cpr::Body{query.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200) {
        ParseElasticSearchResponse(response.text);
    } else {
        std::cout << "Ошибка при отправке запроса:\n"
                  << "HTTP статус: " << response.status_code << "\n"
                  << "Ответ: " << response.text << "\n";
    }
}

void SearchWithFuzziness(const std::string& query) {
    nlohmann::json requestBody = {
        {"query", {
            {"bool", {
                {"should", {
                    {{"match", {
                        {"name", {
                            {"fuzziness", "AUTO"},
                            {"query", query}
                        }}
                    }}}
                }}
            }}
        }}
    };

    std::string url = "api_url/employees/_search/";

    cpr::Response response = cpr::Post(
        cpr::Url{url},
        cpr::Body{requestBody.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200) {
        ParseElasticSearchResponse(response.text);
    } else {
        std::cout << "Ошибка при отправке запроса:\n"
                  << "HTTP статус: " << response.status_code << "\n"
                  << "Ответ: " << response.text << "\n";
    }
}

void SearhViaElastic(employee*& arr, int& n) {
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите поисковой запрос: ";

    std::getline(std::cin, input);

    if (IsValidNumber(input)) {
        //ищем шаблонно сразу по трем полям
        SearchWithWildcard(input);
    } else if (IsRange(input)) {
        //диапазон, ищем по полям salary, hours_worked, service_number с использованием range
        SearchWithRange(input);
    } else {
        //строка, ищем по ФИО с помощью match && fuzziness
        SearchWithFuzziness(input);
    }
}
