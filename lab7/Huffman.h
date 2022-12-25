#ifndef HUFF
#define HUFF
#define MAX_TREE_HT 256 
#include <map>
#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct MinHeapNode
{
    char data;
    int freq;
    MinHeapNode* left, * right;

    MinHeapNode(char data, int freq) {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

struct compare
{
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

map<char, string> codes;
map<char, int> freq;
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;


void storeCodes(struct MinHeapNode* root, string str)
{
    if (root == NULL)
        return;
    if (root->data != '$')
        codes[root->data] = str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

void HuffmanCodes(int size)
{
    struct MinHeapNode* left, * right, * top;
    for (map<char, int>::iterator v = freq.begin(); v != freq.end(); v++)
        minHeap.push(new MinHeapNode(v->first, v->second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}
void calcFreq(string str, int n)
{
    for (int i = 0; i < str.size(); i++)
        freq[str[i]]++;
}
string decode_file(struct MinHeapNode* root, string s)
{
    string ans = "";
    struct MinHeapNode* curr = root;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->left == NULL and curr->right == NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }
    return ans + '\0';
}

void huffman(string test) {
    float avLength = 0, disp = 0;
    string encodedString, decodedString;
    calcFreq(test, test.length());
    HuffmanCodes(test.length());

    for (auto i : test) encodedString += codes[i];
    decodedString = decode_file(minHeap.top(), encodedString);

    cout << "HUFFMAN Character With codes:\n";
    cout << "Letter\tCode\tCount\tposibility" << endl;
    
    for (auto v = codes.begin(); v != codes.end(); v++) {
        float pos = (float)freq[v->first] / (float)test.size();
        cout << v->first << "\t" << v->second << "\t" << freq[v->first] << "\t" << pos * 100 << endl;
        avLength += v->second.length() * pos;
    }

    for (auto v = codes.begin(); v != codes.end(); v++) {
        float pos = (float)freq[v->first] / (float)codes.size();
        disp += pos * (v->second.length() - avLength) * (v->second.length() - avLength);
    }

    cout << "Average code length: " << avLength << endl;
    cout << "Dispersion: " << disp << endl;
    cout << "%: " << (float)test.length() * 8 / (float)encodedString.length()  << endl;
    cout << "\nEncoded Huffman data:\n" << encodedString << endl;
    cout << "\nDecoded Huffman Data:\n" << decodedString << endl;
}

#endif