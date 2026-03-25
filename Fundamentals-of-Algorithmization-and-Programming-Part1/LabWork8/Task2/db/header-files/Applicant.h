#pragma once
#include <string>
#include "Street.h"

using std::string;

typedef struct Applicant {
    Street street;
    int street_type;
    string street_name;
    string fullname;
    string city;
    int house;
    int apartment;
    string grades_str;
} Applicant;