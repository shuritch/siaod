#pragma once
#include "Menu.h"
#include "File.h"
#include <iostream>
using namespace std;

class BinNode {
public:
    char key[30];
    int position;
    struct BinNode* left = nullptr, * right = nullptr;

    BinNode(char k[30], int pos);
    BinNode* search(char key[30]);
};

class Tree {
protected:
    int length();
    string fileName;
    BinNode* remove(BinNode* root, char key[30]);
    void search(char key[30]);
    void add(char key[30], char ru[30]);
    void create();
    void log(BinNode* root, int level);
    BinNode* insert(struct BinNode* root, char key[30], int position);
    BinNode* tree;
};