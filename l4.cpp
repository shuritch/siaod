#include <string>
#include <iostream>
#include <stack>
using namespace std;

// Tree Structure
typedef struct node {
    char data;
    struct node* left, * right;
} *nptr;

nptr newNode(char c) {
    nptr n = new node;
    n->data = c;
    n->left = n->right = nullptr;
    return n;
}

int canSimplify(string s, int i) {
    bool condition1 = s[i] == '1' && (s[i + 1] == '*');
    bool condition2 = s[i] == '0' && s[i + 1] == '+';

    if (condition1 || condition2) {
        return 12;
    }

    bool condition3 = s[i + 2] == '0' && (s[i + 1] == '+' || s[i + 1] == '-');
    bool condition4 = s[i + 2] == '1' && (s[i + 1] == '*' || s[i + 1] == '^' || s[i + 1] == '/');
    bool condition6 = s[i + 2] == '1' && s[i + 1] == '^';

    if (condition3 || condition4 || condition6) {
        return 346;
    }

    bool condition5 = ((s[i] == '0' || s[i + 2] == '0') && s[i + 1] == '*') || (s[i] == '0' && s[i + 1] == '^') || (s[i] == '0' && s[i + 1] == '/');
    if (condition5) {
        return 5;
    }

    bool condition7 = s[i + 2] == '0' && s[i + 1] == '^';
    bool condition8 = s[i + 2] == s[i];
    if (condition7 || condition8) {
        return 78;
    }

    return 0;
}

char helpSimplify(string* str, int* index, int offset, int rule) {
    string s = *str;
    cout << "String: " << s << endl;
    int i = *index;
    i -= offset;
    cout << "Letter: " << s[i] << endl;

    if (rule == 12) {
        cout << "Op: " << 12 << endl;
        s.replace(i, 2, "");
        *str = s;
        *index -= 2;
        return s[i + 2];
    }
    else if (rule == 346) {
        cout << "Op: " << 346 << endl;
        s.replace(i + 1, 2, "");
        *str = s;
        *index -= 2;
        return s[i];
    }
    else if (rule == 5) {
        cout << "Op: " << 5 << endl;
        s.replace(i, 3, "0");
        *str = s;
        *index -= 2;
        return 0;
    }
    else if (rule == 78) {
        cout << "Op: " << 78 << endl;
        s.replace(i, 3, "1");
        *str = s;
        *index -= 2;
        return 1;
    }


    return s[i];
}

char simplify(string* str, int* index) {
    string s = *str;
    int i = *index;
    if (s.length() > i + 1) return helpSimplify(str, index, 0, canSimplify(s, i));
    // else if (s.length() - 1 == i) return helpSimplify(str, index, -2, canSimplify(s, i));
    return s[i];
}

nptr build(string& s) {
    stack<nptr> stN; // Nodes stack
    stack<char> stC; // Chars stack
    nptr t, t1, t2;

    // Priority
    int operations[123] = { 0 };
    operations['+'] = operations['-'] = 1, operations['/'] = operations['*'] = 2, operations['^'] = 3, operations[')'] = 0;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') stC.push(s[i]); // Push '(' in char stack

        // Operand
        else if (isdigit(s[i]) || isalpha(s[i])) {
            bool condition1 = s[i] == '1' && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '^');
            bool condition2 = s[i] == '0' && s[i + 1] == '+';
            t = newNode(simplify(&s, &i));
            stN.push(t);
        }

        // Operation
        else if (operations[s[i]] > 0) {
            // If an operator with lower or
            // same associativity appears
            while (!stC.empty() && stC.top() != '(' && ((s[i] != '^' && operations[stC.top()] >= operations[s[i]]) || (s[i] == '^' && operations[stC.top()] > operations[s[i]]))) {

                t = newNode(stC.top());
                stC.pop();

                t1 = stN.top();
                stN.pop();

                t2 = stN.top();
                stN.pop();

                t->left = t2;
                t->right = t1;

                stN.push(t);
            }

            stC.push(s[i]);
        }

        else if (s[i] == ')') {
            while (!stC.empty() && stC.top() != '(') {
                t = newNode(stC.top());
                stC.pop();
                t1 = stN.top();
                stN.pop();
                t2 = stN.top();
                stN.pop();
                t->left = t2;
                t->right = t1;
                stN.push(t);
            }

            stC.pop();
        }
    }
    t = stN.top();
    return t;
}

void postorder(nptr root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data;
    }
}

int main() {
    string s = "2*0+2+3*4-5";
    s = "(" + s + ')';
    nptr root = build(s);
    postorder(root);
    return 0;
}