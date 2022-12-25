#ifndef FANO
#define FANO
#include <iostream>
#include <map>
#include <string>
#include <cassert>
using namespace std;

struct pnode {
    char ch;
    float p;
};

static int pnode_compare(const void* elem1, const void* elem2);

class Coder {
private:
    int tsize;
    pnode* ptable; 
    map<char, string> codes; 

public:

    void Encode(const char* inputFilename, const char* outputFilename);

    void Decode(const char* inputFilename, const char* outputFilename);

private:
    void EncShannon(int li, int ri);
};


int fano(const char* decoded);

#endif