#pragma once
#include <iostream>
#include <iomanip>
#include <pqxx/pqxx>
#include <string>

#include "../header-files/Applicant.h"

void viewAllApplicants(pqxx::connection& conn);
void addApplicant(pqxx::connection& conn);
void addMultipleApplicants(pqxx::connection& conn);
void deleteApplicant(pqxx::connection& conn);
void deleteAllApplicants(pqxx::connection& conn);
void editApplicantField(pqxx::connection& conn);