#define _CRT_SECURE_NO_WARNINGS
#include "BinTree.h";

BinTree::BinTree(string name) {
    this->fileName = name;
    create();
    Menu menu({ "Return", "Search", "Remove", "Log", "Add" });
    int command = menu.prompt();
    while (command != 0) {
        if (command == 1) {
            char key[30]; cout << "Key: "; cin >> key;
            search(key);
        }
        else if (command == 2) {
            char key[30]; cout << "Key: "; cin >> key;
            File::remove(fileName, key);
            tree = remove(tree, key);
        }
        else if (command == 3) {
            log(tree, 0);
        }
        else if (command == 4) {
            char en[30]; cout << "En: "; cin >> en;
            char ru[30]; cout << "Ru: "; cin >> ru;
            add(en, ru);
        }
        command = menu.prompt();
    }
}