#include "../utils/header-files/utils.h"
#include "../db/header-files/db.h"
#include "./header-files/elastic.h"

void elasticCreateIndex() {
    nlohmann::json doc = {
        {"mappings", {
            {"properties", {
                {"fullname", {
                    {"type", "text"},
                    {"analyzer", "russian"}
                }},
                {"city", {
                    {"type", "text"}
                }},
                {"street", {
                    {"type", "text"}
                }},
                {"house", {
                    {"type", "integer"}
                }},
                {"apartment", {
                    {"type", "integer"}
                }},
                {"house_aparment_average_grade", {
                    {"type", "text"}
                }},
                {"average_grade", {
                    {"type", "float"}
                }}
            }}
        }}
    };

    string json_string = doc.dump();
    string endPoint = "api_url/applicants";
    auto response = cpr::Put(
        cpr::Url{endPoint},
        cpr::Body{json_string},
        cpr::Header{{"Content-Type", "application/json"}}
    );
}

void createApplicantInIndex(Applicant& applicant, const int& applicant_id) {
    nlohmann::json doc;

    doc["fullname"] = applicant.fullname;
    doc["city"] = applicant.city;
    if (applicant.street_type == 2) {
        doc["street"] = applicant.street_name;
    }
    else if (applicant.street_type == 1) {
        doc["street"] = applicant.street.street_int;
    } else if (applicant.street_type == 0) {
        doc["street"] = applicant.street.street_double;
    }
    doc["house"] = applicant.house;
    doc["apartment"] = applicant.apartment;

    double average_grade = 0.0;
    int grade_count = 0;
    std::istringstream grades_stream(applicant.grades_str);
    string grade;
    while (grades_stream >> grade) {
        average_grade += std::stod(grade);
        ++grade_count;
    }

    if (grade_count > 0) {
        average_grade /= grade_count;
    } else {
        average_grade = 0.0;
    }

    doc["average_grade"] = average_grade;

    doc["house_aparment_average_grade"] =
        std::to_string(applicant.house) + " " +
        std::to_string(applicant.apartment) + " " +
        std::to_string(average_grade);

    string json_string = doc.dump();

    string endPoint = "api_url/applicants/_doc/" + std::to_string(applicant_id) + "/_create";
    auto response = cpr::Put(
        cpr::Url{endPoint},
        cpr::Body{json_string},
        cpr::Header{{"Content-Type", "application/json"}}
    );
}

void deleteApplicantInIndex(const int& applicant_id) {
    auto response = cpr::Delete(
        cpr::Url{"api_url/applicants/_doc/" + std::to_string(applicant_id)},
        cpr::Header{{"Content-Type", "application/json"}}
    );
    std::cout << "Документ успешно удален из индекса ElasticSearch.";
}

void deleteAllApplicantsInIndex() {
    auto response = cpr::Delete(
        cpr::Url{"api_url/applicants"},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200 || response.status_code == 201) {
        std::cout << "Все документы успешно удалены из индекса ElasticSearch." << '\n';
    } else {
        std::cerr << "Ошибка при удалении документов из индекса ElasticSearch: " << response.text << '\n';
    }
}

void updateApplicantInIndex(const int& applicant_id, const string& field, const string& new_value) {
    nlohmann::json doc = {
        {"doc", { //данные, которые нужно обновить
            {field, new_value}  //field и его новое значение
        }},
        {"doc_as_upsert", true}  //специальный флаг (если документ отсутствует, он будет создан)
    };

    string endPoint = "api_url
    /applicants/_update/" + std::to_string(applicant_id);
    auto response = cpr::Post(
        cpr::Url{endPoint},
        cpr::Body{doc.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200) {
        std::cout << "Данные об абитуриенте упешно обновлены в ElasticSearch.\n";
    } else {
        std::cout << "Ошибка при обновлении документа ElasticSearch.\n";
    }
}

void SearchGetResponse(const cpr::Response& response) {
    if (response.status_code == 200) {
        nlohmann::json json_response = nlohmann::json::parse(response.text);

        if (json_response.contains("hits") && json_response["hits"].contains("hits")) {
            auto hits = json_response["hits"]["hits"];

            if (!hits.empty()) {
                std::sort(hits.begin(), hits.end(), CompareByFullname);
                std::cout << "Результаты поиска:\n";
                for (const auto& hit : hits) {
                    auto source = hit["_source"];

                    std::cout << "ID: " << hit["_id"] << "\n";
                    std::cout << "ФИО: " << source["fullname"] << "\n";
                    std::cout << "Город: " << source["city"] << "\n";
                    std::cout << "Улица: " << source["street"] << "\n";
                    std::cout << "Дом: " << source["house"] << "\n";
                    std::cout << "Квартира: " << source["apartment"] << "\n";
                    double average_grade = source["average_grade"];
                    std::cout << "Средний балл: " << std::fixed << std::setprecision(1) << average_grade << "\n";
                    std::cout << "------------------------\n";
                }
            } else {
                std::cout << "Нет абитуриентов, соответствующих запросу.\n";
            }
        } else {
            std::cout << "Ошибка запроса.\n";
        }
    } else {
        // std::cout << "Ошибка запроса: Код ошибки " << response.status_code << "\n";
        std::cout << "Таких абитуриентов нет.\n";
    }
}

void searchEmployeeByCityAndGrade(const std::string& city, double minGrade, double maxGrade) {
    nlohmann::json query = {
        {"query", {
            {"bool", {
                {"must", nlohmann::json::array({
                    {{"range", {
                        {"average_grade", {
                            {"gte", minGrade},
                            {"lte", maxGrade}
                        }}
                    }}},
                    {{"match", {
                        {"city", city}
                    }}}
                })}
            }}
        }}
    };

    std::string jsonString = query.dump();

    auto response = cpr::Post(
        cpr::Url{"api_url/applicants/_search"},
        cpr::Body{jsonString},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    SearchGetResponse(response);
}

void SearchWithWildcard(const std::string& searchQuery) {
    nlohmann::json requestBody = {
        {
            "query", {
                {"bool", {
                    {"should", {
                        {
                            {"wildcard", {
                                {"house_aparment_average_grade", "*" + searchQuery + "*"}
                            }}
                        },
                        {
                            {"wildcard", {
                                {"street", "*" + searchQuery + "*"}
                            }}
                        }
                    }},
                    {"minimum_should_match", 1}
                }}
            }
        }
    };

    std::string url = "api_url/applicants/_search/";

    cpr::Response response = cpr::Post(
        cpr::Url{url},
        cpr::Body{requestBody.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200) {
        SearchGetResponse(response);
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
                    {{"range", {{"house", {{"gte", left}, {"lte", right}}}}}},
                    {{"range", {{"apartment", {{"gte", left}, {"lte", right}}}}}},
                    {{"range", {{"average_grade", {{"gte", left}, {"lte", right}}}}}}
                }}
            }}
        }}
    };

    std::string url = "api_url/applicants/_search/";

    cpr::Response response = cpr::Post(
        cpr::Url{url},
        cpr::Body{query.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200) {
        SearchGetResponse(response);
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
                {"should", nlohmann::json::array({
                    {{"match", {
                        {"fullname", {
                            {"fuzziness", "AUTO"},
                            {"query", query}
                        }}}
                    }},
                    {{"match", {
                        {"city", {
                            {"fuzziness", "AUTO"},
                            {"query", query}
                        }}}
                    }},
                    {{"match", {
                        {"street", {
                            {"fuzziness", "AUTO"},
                            {"query", query}
                        }}}
                    }},
                    {{"match", {
                        {"house_aparment_average_grade", {
                            {"fuzziness", "AUTO"},
                            {"query", query}
                        }}}
                    }}
                })},
                {"minimum_should_match", "1"}  //как минимум одно условие должно совпасть
            }}
        }}
    };

    std::string url = "api_url/applicants/_search/";

    cpr::Response response = cpr::Post(
        cpr::Url{url},
        cpr::Body{requestBody.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );

    if (response.status_code == 200) {
        SearchGetResponse(response);
    } else {
        std::cout << "Ошибка при отправке запроса:\n"
                  << "HTTP статус: " << response.status_code << "\n"
                  << "Ответ: " << response.text << "\n";
    }
}

void searchViaElastic() {
    std::string input;
    // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите поисковой запрос: ";

    std::getline(std::cin, input);

    if (IsValidNumber(input)) {
        //ищем шаблонно сразу по трем полям
        SearchWithWildcard(input);
    } else if (IsRange(input)) {
        //диапазон, ищем по полям house, apartment, average_grade с использованием range
        SearchWithRange(input);
    } else {
        //строка, ищем по ФИО с помощью match && fuzziness
        SearchWithFuzziness(input);
    }
}
