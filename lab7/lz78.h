#ifndef LZ78
#define LZ78

#pragma once
#include "libs.h"

int indexOf(string* arr, int length, string str)
{
    int i;
    for (i = 0; i < length; i++)
        if (arr[i] == str)
            return i;
    return -1;
}

void addWord(string** arr, int* len, string word)
{
    string* n = new string[(*len) + 1];
    int i;
    for (i = 0; i < *len; i++)
        n[i] = (*arr)[i];
    n[i] = word;
    delete[](*arr);
    (*arr) = n;
    (*len)++;
}


string LZ78_ENCODE(const string& data)
{
    string* arr = NULL;
    string res = "";
    string temp = "";
    int i, len = 0, index, r;

    for (i = 0; i < data.length();)
    {
        temp = "";
        index = -1;
        r = -1;

        do
        {
            index = r;
            temp += data[i++];
            r = indexOf(arr, len, temp);
        } while (i < data.length() && r != -1);

        if (r == -1)
        {
            res += to_string(index + 1) + "" + temp[temp.length() - 1];
            addWord(&arr, &len, temp);
        }
        else
            res += to_string(r + 1) + "";
    }

    delete[] arr;
    return res;
}

string LZ78_DECODE(const string& data)
{
    string* arr = NULL;
    string res = "";
    int i, len = 0, is_last = 0, r = 0;
    addWord(&arr, &len, "");
    string index;

    for (i = 0; i < data.length(); i++)
        if (data[i] >= '0' && data[i] <= '9')
        {
            r = 1;
            break;
        }

    if (r == 0)
        return data;

    for (i = 0; i < data.length();)
    {
        index = "";
        is_last = 0;
        while (i < data.length() && data[i] >= '0' && data[i] <= '9')
            index += data[i++];
        if (i < data.length())
        {
            addWord(&arr, &len, arr[stoi(index)] + data[i]);
            is_last = 1;
        }
        i++;
    }

    for (i = 0; i < len; i++)
        res += arr[i];
    if (is_last == 0)
        res += arr[stoi(index)];
    return res;
}

void lz78(string test) {
    cout << "LZ78 =>" << endl;
    string lz78 = LZ78_ENCODE(test);
    cout << lz78 << endl;
    cout << LZ78_DECODE(lz78) << endl;
}

#endif