#include <iostream>
#include "employee.h"

employee* getEmployees(int&);
bool emptyDb();
void truncateFile(int);
void displayDatabase();
void clearDatabase(employee*&, int&);
void addToDatabase(employee*&, int&);
void deleteFromDatabase(employee*&, int&);
void editDatabase(employee*, int);
void loadDatabase(employee*&, int&);