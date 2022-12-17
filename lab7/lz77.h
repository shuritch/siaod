#ifndef LZ77
#define LZ77

#pragma once
#include "libs.h";

struct Node
{
    int offset;
    int length;
    char next;

    Node(int of, int le, char ne) :  offset(of), length(le), next(ne){}
};


vector<Node*> LZ77_ENCODE(string s)
{
    vector<Node*> answer;

    const int buf_size = 3072;
    const int preview_size = 1024;

    int position = 0;

    while (position < s.length())
    {
        int max_index = 0, max_length = 0, cur_index, cur_length;
        for (int j = max(0, (position - buf_size)); j < position; j++)
        {
            cur_index = j, cur_length = 0;

            while (s[cur_index] == s[cur_length + position] && cur_index < min((position + preview_size), (int)s.length()))
            {
                cur_index++;
                cur_length++;
            }

            if (cur_length > max_length)
            {
                max_index = position - j;
                max_length = cur_length;
            }
        }

        position += max_length;
        answer.push_back(new Node(max_index, max_length, s[position]));
        position++;
    }

    return answer;
}

string LZ77_DECODE(const vector<Node*> encoded)
{
    string answer;
    for (auto& node : encoded)
    {
        if (node->length > 0)
        {
            int start = answer.length() - node->offset;
            for (int k = 0; k < node->length; k++)
                answer += answer[start + k];
        }
        //cout << answer << node->next << " (" << node->offset << " " << node->length << " " << node->next << ") " << endl;
        answer += node->next;
    }
    return answer;
}

void lz77(string test) {
    cout << endl << "LZ77 =>" << endl;
    std::vector<Node*> lz77 = LZ77_ENCODE(test);
    for (auto& node : lz77) cout << node->offset << node->length << node->next;
    cout << endl << LZ77_DECODE(lz77) << endl;
}

#endif