#pragma once
#include <string>

using std::string;

void GenerateEncodingForChosenNumberSystem(const unsigned int base, string*& encoding);
string ConvertToChosenNumberSystem(const string& number, const unsigned int base, string*& encoding);
unsigned int TransformToInteger(char unit1, char unit2);
unsigned int ConvertFromEncodingToInteger(string& number, const unsigned int base);
string addNumbers(const string& num1, const string& num2, int base, string*& encoding);
string subtractNumbers(const string& num1, const string& num2, int base, string*& encoding);
string proccessOperation(string& num1, string& num2, string*& encoding, const unsigned int base, bool isAddition);