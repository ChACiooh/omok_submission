#ifndef PARSE_RADIX_H_INCLUDED
#define PARSE_RADIX_H_INCLUDED

#include <string>
#include <vector>
#include <cstdlib>
#include <ctype.h>

using namespace std;

bool IsError(const string& str);
int ParseRadix(const string& number);
string ConvertRadix(int number, int radix);
void split(vector<string> *sv, const string str, const string pivot);

#endif // PARSE_RADIX_H_INCLUDED
