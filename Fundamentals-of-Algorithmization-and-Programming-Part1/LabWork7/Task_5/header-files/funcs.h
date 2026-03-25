#pragma once
#include <string>

using std::string;

string ConvertToTrinary(int number);
void EncodeAllBarrels(string*& barrels, const unsigned int total);
unsigned int ConvertFromTrinaryToDecimal(string& str);
void ShowBarrelsList(const unsigned int pos, char unit, string*& barrels);
void ShowAliveSlaves(bool (&alive)[5]);
void ExecuteTask();