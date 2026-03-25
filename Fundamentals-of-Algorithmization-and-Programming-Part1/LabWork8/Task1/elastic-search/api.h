#pragma once
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "../employee.h"
#include "../employee_functions.h"
#include "../algorithms.h"

void AddDocumentToElastic(const employee&);
void DeleteDocumentFromElastic(const employee& e);
void DeleteAllEmployeesInIndex();
void AddAllEmployeesFromArray(employee*& arr, int& n);
void SearhViaElastic(employee*& arr, int& n);