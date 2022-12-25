#ifndef LZ77
#define LZ77

#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct Node
{
    int offset;
    int length;
    char next;

    Node(int of, int le, char ne) :  offset(of), length(le), next(ne){}
};

vector<Node*> LZ77_ENCODE(string s);

string LZ77_DECODE(const vector<Node*> encoded);

void lz77(string test);

#endif