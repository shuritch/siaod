#pragma once
#include "Tree.h"
#include <string>
#include <sstream>

struct Info {
    char key[30];
    int position;
};

class TreeNode {
public:
    vector<Info*> keys;
    vector<TreeNode*> children;
    int range;
    bool leaf;
    int length = 0;

    TreeNode(int temp, bool bool_leaf);

    void insertNonFull(char key[30], int position);
    void splitChild(int i, TreeNode* y);
    void traverse();
    TreeNode* search(char key[30]);

    // for delete
    int findKey(char key[30]);
    void remove(char key[30]);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    Info* getPredecessor(int idx);
    Info* getSuccessor(int idx);

    friend class BTree;
};

class BTree {
    int minRange;
    string fileName;
    int length = 0;

public:
    TreeNode* root;
    BTree(int temp, string fileName);

    void traverse() {
        if (root != NULL) root->traverse();
    }

    TreeNode* search(char key[30]) {
        return (root == NULL) ? NULL : root->search(key);
    }

    void insert(char key[30], int position);
    void remove(char key[30]);
    void create();
};

class BTreePrinter
{
    struct NodeInfo
    {
        std::string text;
        unsigned text_pos, text_end;  // half-open range
    };


    std::vector<vector<NodeInfo>> levels;

    string node_text(vector<Info*> const keys, unsigned key_count);

    void before_traversal()
    {
        levels.resize(0);
        levels.reserve(10);   // far beyond anything that could usefully be printed
    }

    void visit(TreeNode const* node, unsigned level = 0, unsigned child_index = 0);

    void after_traversal();

public:
    void print(BTree const& tree)
    {
        before_traversal();
        visit(tree.root);
        after_traversal();
    }
};
