#ifndef LZ78
#define LZ78

#include <string>
#include <iostream>
using namespace std;

int indexOf(string* arr, int length, string str);

void addWord(string** arr, int* len, string word);

string LZ78_ENCODE(const string& data);

string LZ78_DECODE(const string& data);

void lz78(string test);
#endif