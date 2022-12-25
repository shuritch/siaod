#include "RLE.h"

string RLE_ENCODE(const string& str)
{
    string encodedLetters;

    for (int i = 0; i < str.length(); i++)
    {
        int count = 1;
        while (str[i] == str[i + 1])
        {
            count++;
            i++;
        }
        (count > 1) ? encodedLetters += str[i] + to_string(count) : encodedLetters += str[i];
    }
    return encodedLetters;
}

string RLE_DECODE(const string& str) {
    string decodedLetters = "";
    int j = 0;
    for (int i = 0; i < str.length(); i++) {
        string counter = "";
        int letterCoefficient = 0;
        if (!isalpha(str[0])) {
            if (!isalpha(str[i])) continue;
            counter = str.substr(j, i - j);
            j = i + 1;
            istringstream(counter) >> letterCoefficient;
            for (int k = 0; k < letterCoefficient; k++) decodedLetters += str[i];
            if (isalpha(str[i + 1]))  decodedLetters += str[i + 1];
        } else {
            if (isalpha(str[i]))  decodedLetters += str[i];
            else {
                counter = str.substr(i, i - j);
                j = i - 1;
                istringstream(counter) >> letterCoefficient;
                for (int k = 1; k < letterCoefficient; k++)
                    decodedLetters += str[j];
            }
        }
    }
    return decodedLetters;
}

void rle(string test) {
    string encoded = RLE_ENCODE(test);
    string decoded = RLE_DECODE(encoded);

    cout << "RLE => " << endl;
    cout << "Encoded: " << encoded << endl;
    cout << "Decoded: " << decoded << endl;
    cout << "%: " << (float)test.length() / (float)encoded.length() << endl << endl;
}