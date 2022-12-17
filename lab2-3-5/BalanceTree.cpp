#define _CRT_SECURE_NO_WARNINGS
#include "BalanceTree.h";
#include <string>

BTree::BTree(int temp, string fileName) {
    this->fileName = fileName;
    root = NULL;
    minRange = temp;
    BTreePrinter printer;
    create();
    Menu menu({ "Return", "Search", "Remove", "Log", "Add" });
    int command = menu.prompt();
    while (command != 0) {
        if (command == 1) {
            char key[30]; cout << "Key: "; cin >> key;
            TreeNode* result = search(key);
            if (result != nullptr) {
                for (int i = 0; i < result->length; i++) {
                    if (strcmp(result->keys[i]->key, key) != 0) continue;
                    File::search(fileName, result->keys[i]->position + 1);
                }
            } else cout << "404" << endl;
        }
        else if (command == 2) {
            char key[30]; cout << "Key: "; cin >> key;
            length--;
            remove(key);
            File::remove(fileName, key);
        }
        else if (command == 3) {
           // traverse();
            printer.print(*this);
            cout << endl;
        }
        else if (command == 4) {
            char en[30]; cout << "En: "; cin >> en;
            char ru[30]; cout << "Ru: "; cin >> ru;
            insert(en, length);
            File::add(fileName, en, ru);
            length++;
        }
        command = menu.prompt();
    }
}

void BTree::create() {
    ifstream read;
    Record record;
    read.open(fileName, ios::in | ios::binary);
    if (!read) cerr << "Can't open file" << endl;
    read.read((char*)&record, sizeof(Record));

    while (!read.eof()) {
        insert(record.en, length);
        length++;
        read.read((char*)&record, sizeof(Record));
    }

    read.close();
}

void BTree::remove(char key[30]) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(key);

    if (root->length == 0) {
        TreeNode* tmp = root;
        if (root->leaf) root = NULL;
        else root = root->children[0];

        delete tmp;
    }
}

TreeNode::TreeNode(int _range, bool _leaf) {
    range = _range;
    leaf = _leaf;
    keys.resize(2 * range - 1);
    children.resize(2 * range);
    length = 0;
}

void TreeNode::traverse() {
    int i;
    for (i = 0; i < length; i++) {
        if (leaf == false) children[i]->traverse();
        cout << " " << keys[i]->key;
    }

    if (leaf == false) children[i]->traverse();
}

TreeNode* TreeNode::search(char key[30]) {
    int i = 0;
    while (i < length && string(key).length() > string(keys[i]->key).length()) i++;

    if (strcmp(keys[i]->key, key) == 0) return this;
    if (leaf == true) return NULL;

    return children[i]->search(key);
}

void BTree::insert(char key[30], int position) {
    if (root == NULL) {
        root = new TreeNode(minRange, true);
        root->keys[0] = new Info;
        strcpy(root->keys[0]->key, key);
        root->keys[0]->position = position;
        root->length = 1;
    } else {
        if (root->length == 2 * minRange - 1) {
            TreeNode* s = new TreeNode(minRange, false);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (string(s->keys[0]->key).length() < string(key).length()) i++;
            s->children[i]->insertNonFull(key, position);
            root = s;
        } else root->insertNonFull(key, position);
    }
}

void TreeNode::insertNonFull(char key[30], int position) {
    int i = length - 1;

    if (leaf == true) {
        while (i >= 0 && string(keys[i]->key).length() > string(key).length()) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = new Info;
        strcpy(keys[i + 1]->key, key);
        keys[i + 1]->position = position;
        length = length + 1;
    } else {
        while (i >= 0 && string(keys[i]->key).length() > string(key).length())  i--;

        if (children[i + 1]->length == 2 * range - 1) {
            splitChild(i + 1, children[i + 1]);
            if (string(keys[i + 1]->key).length() < string(key).length())  i++;
        }

        children[i + 1]->insertNonFull(key, position);
    }
}

void TreeNode::splitChild(int i, TreeNode* y) {
    TreeNode* z = new TreeNode(y->range, y->leaf);
    z->length = range - 1;

    for (int j = 0; j < range - 1; j++) z->keys[j] = y->keys[j + range];

    if (y->leaf == false) {
        for (int j = 0; j < range; j++)
            z->children[j] = y->children[j + range];
    }

    y->length = range - 1;
    for (int j = length; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = length - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[range - 1];
    length = length + 1;
}

int TreeNode::findKey(char key[30]) {
    int idx = 0;
    while (idx < length && string(keys[idx]->key).length() < string(key).length()) ++idx;
    return idx;
}

void TreeNode::remove(char key[30]) {
    int idx = findKey(key);

    if (idx < length && strcmp(keys[idx]->key, key) == 0) {
        if (leaf) removeFromLeaf(idx);
        else removeFromNonLeaf(idx);
    } else {
        if (leaf) {
            cout << "404" << endl;
            return;
        }

        bool flag = ((idx == length) ? true : false);

        if (children[idx]->length < range) fill(idx);
        if (flag && idx > length) children[idx - 1]->remove(key);
        else children[idx]->remove(key);
    }

}


void TreeNode::removeFromNonLeaf(int idx) {
    char* key = keys[idx]->key;

    if (children[idx]->length >= range) {
        Info* pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred->key);
    } else if (children[idx + 1]->length >= range) {
        Info* succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ->key);
    } else {
        merge(idx);
        children[idx]->remove(key);
    }
}

Info* TreeNode::getPredecessor(int idx) {
    TreeNode* cur = children[idx];
    while (!cur->leaf) cur = cur->children[cur->length];
    return cur->keys[cur->length - 1];
}

Info* TreeNode::getSuccessor(int idx) {
    TreeNode* cur = children[idx + 1];
    while (!cur->leaf) cur = cur->children[0];
    return cur->keys[0];
}

void TreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->length >= range) borrowFromPrev(idx);
    else if (idx != length && children[idx + 1]->length >= range) borrowFromNext(idx);
    else {
        if (idx != length)  merge(idx);
        else merge(idx - 1);
    }
}

void TreeNode::borrowFromPrev(int idx) {
    TreeNode* child = children[idx];
    TreeNode* sibling = children[idx - 1];

    for (int i = child->length - 1; i >= 0; --i) child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->length; i >= 0; --i) child->children[i + 1] = child->children[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf) child->children[0] = sibling->children[sibling->length];

    keys[idx - 1] = sibling->keys[sibling->length - 1];

    child->length += 1;
    sibling->length -= 1;
}

void TreeNode::borrowFromNext(int idx) {
    TreeNode* child = children[idx];
    TreeNode* sibling = children[idx + 1];

    child->keys[(child->length)] = keys[idx];

    if (!(child->leaf)) child->children[(child->length) + 1] = sibling->children[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->length; ++i) sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->length; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->length += 1;
    sibling->length -= 1;
}

void TreeNode::merge(int idx) {
    TreeNode* child = children[idx];
    TreeNode* sibling = children[idx + 1];

    child->keys[range - 1] = keys[idx];

    for (int i = 0; i < sibling->length; ++i)
        child->keys[i + range] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->length; ++i)
            child->children[i + range] = sibling->children[i];
    }

    for (int i = idx + 1; i < length; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= length; ++i)
        children[i - 1] = children[i];

    child->length += sibling->length + 1;
    length--;

    delete (sibling);
}

void TreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < length; ++i) keys[i - 1] = keys[i];
    length--;
}

// ----------- PRINT -----------------

void BTreePrinter::visit(TreeNode const* node, unsigned level, unsigned child_index) {
    if (level >= levels.size()) levels.resize(level + 1);

    vector<NodeInfo>& level_info = levels[level];
    NodeInfo info;

    info.text_pos = 0;
    if (!level_info.empty())  // one blank between nodes, one extra blank if left-most child
        info.text_pos = level_info.back().text_end + (child_index == 0 ? 2 : 1);

    info.text = node_text(node->keys, unsigned(node->length));

    if (node->leaf) {
        info.text_end = info.text_pos + unsigned(info.text.length());
    }
    else // non-leaf -> do all children so that .text_end for the right-most child becomes known
    {
        for (unsigned i = 0, e = unsigned(node->length); i <= e; ++i)  // one more pointer than there are keys
            visit(node->children[i], level + 1, i);

        info.text_end = levels[level + 1].back().text_end;
    }

    levels[level].push_back(info);
}

void print_blanks(unsigned n) {
    while (n--) std::cout << ' ';
}

string BTreePrinter::node_text(vector<Info*> const keys, unsigned key_count) {
    std::ostringstream os;
    char const* sep = "";

    os << "[";
    for (unsigned i = 0; i < key_count; ++i, sep = ", ") {
        os << sep << keys[i]->key;
    }
    os << "]";

    return os.str();
}

void BTreePrinter::after_traversal() {
    for (std::size_t l = 0, level_count = levels.size(); ; )
    {
        auto const& level = levels[l];
        unsigned prev_end = 0;

        for (auto const& node : level)
        {
            unsigned total = node.text_end - node.text_pos;
            unsigned slack = total - unsigned(node.text.length());
            unsigned blanks_before = node.text_pos - prev_end;

            print_blanks(blanks_before + slack / 2);
            std::cout << node.text;

            if (&node == &level.back())
                break;

            print_blanks(slack - slack / 2);

            prev_end += blanks_before + total;
        }

        if (++l == level_count)
            break;

        std::cout << "\n\n";
    }

    std::cout << "\n";
}