#define _CRT_SECURE_NO_WARNINGS
#include "Tree.h";

BinNode::BinNode(char k[30], int pos) : position(pos) {
    strcpy(key, k);
    this->left = this->right = nullptr;
}

void Tree::create() {
    ifstream read;
    Record record;
    read.open(fileName, ios::in | ios::binary);
    if (!read) cerr << "Can't open file" << endl;
    read.read((char*)&record, sizeof(Record));
    unsigned long index;
    int i = 0;

    while (!read.eof()) {
        tree = insert(tree, record.en, i);
        i++;
        read.read((char*)&record, sizeof(Record));
    }

    read.close();
}

void Tree::add(char en[30], char ru[30]) {
    File::add(fileName, en, ru);
    int pos = length() + 1;
    tree = insert(tree, en, pos);
}


void Tree::log(BinNode* root, int level) {
    if (root) {
        log(root->left, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << root->key << endl;
        log(root->right, level + 1);
    }
}

BinNode* Tree::insert(struct BinNode* root, char key[30], int position) {
    if (root == nullptr) return new BinNode(key, position);

    if (string(root->key).length() > string(key).length()) root->left = insert(root->left, key, position);
    else root->right = insert(root->right, key, position);

    return root;
}

BinNode* BinNode::search(char key[30]) {
    if (strcmp(this->key, key) == 0) return this;
    BinNode* ptr = nullptr;

    if (string(this->key).length() > string(key).length()) ptr = this->left->search(key);
    else ptr = this->right->search(key);

    return ptr;
}

void Tree::search(char key[30]) {
    BinNode* found = tree->search(key);
    if (!found) cout << "404" << endl;
    else File::search(fileName, found->position + 1);
}

int Tree::length() {
    int max = tree->position;
    BinNode* r = tree->right;
    BinNode* l = tree->left;

    if (!l) return max;
    while (l && l->left) {
        l = l->left;
        if (l->position > max) max = l->position;
    }

    if (!r) return max;
    while (r && r->right) {
        r = r->right;
        if (r->position > max) max = r->position;
    }

    return max;
}


BinNode* Tree::remove(BinNode* root, char key[30]) {
    BinNode* curr = root;
    BinNode* prev = nullptr;

    while (curr != nullptr && string(curr->key) != string(key)) {
        prev = curr;
        if (string(key).length() < string(curr->key).length()) curr = curr->left;
        else curr = curr->right;
    }

    if (curr == nullptr) {
        cout << "404" << endl;
        return root;
    }

    if (curr->left == nullptr || curr->right == nullptr) {
        BinNode* newCurr;

        if (curr->left == nullptr) newCurr = curr->right;
        else newCurr = curr->left;


        if (prev == nullptr) return newCurr;

        if (curr == prev->left)  prev->left = newCurr;
        else  prev->right = newCurr;

        free(curr);
    }
    else {
        BinNode* p = nullptr;
        BinNode* temp;

        temp = curr->right;
        while (temp->left != nullptr) {
            p = temp;
            temp = temp->left;
        }

        if (p != nullptr) p->left = temp->right;
        else curr->right = temp->right;

        strcpy(curr->key, temp->key);
        free(temp);
    }
    return root;
}