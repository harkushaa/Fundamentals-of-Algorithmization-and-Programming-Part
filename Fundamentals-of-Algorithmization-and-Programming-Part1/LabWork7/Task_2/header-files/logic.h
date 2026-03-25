#pragma once
#include <string>

using std::string;

void ConvertToForwardModifiedCode(string& bit_sequence1, string& bit_sequence2);
void ConvertBothToEqualSizes(string& big_string, string& small_string, unsigned int sizes_difference);
void CallConvertBothToEqualSizes(string& bit_sequence1, unsigned int size1, string& bit_sequence2, unsigned int size2);
void ForwardModifiedToAdditionalModified(string& bit_sequence, unsigned int size);
void GenerateResult(bool& remainder, const string& bit_sequence1, const string& bit_sequence2, string& bit_sequence3, const int size);
string CalculateInAdditionalCode(string& bit_sequence1, string& bit_sequence2);
