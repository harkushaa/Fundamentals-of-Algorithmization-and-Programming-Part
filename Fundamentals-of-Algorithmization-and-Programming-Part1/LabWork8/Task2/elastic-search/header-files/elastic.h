#pragma once

#include <iostream>
#include <string>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iomanip> 

#include "../../db/header-files/db.h"

using std::string;

void elasticCreateIndex();
void createApplicantInIndex(Applicant& applicant, const int& applicant_id);
void deleteApplicantInIndex(const int& applicant_id);
void deleteAllApplicantsInIndex(); 
void updateApplicantInIndex(const int& applicant_id, const string& field, const string& new_value);
void SearchGetResponse(const cpr::Response& response);
void searchEmployeeByCityAndGrade(const std::string& city, double minGrade, double maxGrade);
void SearchWithWildcard(const std::string& searchQuery);
void SearchWithRange(const std::string& input);
void SearchWithFuzziness(const std::string& query);
void searchViaElastic();