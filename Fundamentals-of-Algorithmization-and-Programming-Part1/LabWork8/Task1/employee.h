#pragma once

typedef struct employee_s {
    bool currency;
    char fullname[60];
    int service_number;
    int hours_worked;

    union salary {
        int dollars;
        int euros;
    } salary_per_hour;
} employee;