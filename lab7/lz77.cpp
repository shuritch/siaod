#include "lz77.h";

string LZ77_DECODE(const vector<Node*> encoded) {
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

vector<Node*> LZ77_ENCODE(string s) {
    vector<Node*> answer;
    const int buf_size = 3072;
    const int preview_size = 1024;
    int position = 0;
    while (position < s.length()) {
        int max_index = 0, max_length = 0, cur_index, cur_length;
        for (int j = max(0, (position - buf_size)); j < position; j++) {
            cur_index = j, cur_length = 0;
            while (s[cur_index] == s[cur_length + position] && cur_index < min((position + preview_size), (int)s.length())) {
                cur_index++;
                cur_length++;
            }
            if (cur_length > max_length) {
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

void lz77(string test) {
    std::vector<Node*> encoded = LZ77_ENCODE(test);
    string decoded = LZ77_DECODE(encoded);
    string result; 
    for (auto& node : encoded) {
        result += to_string(node->offset);
        result += to_string(node->length);
        result += to_string(node->length);
    }

    cout << "LZ77 =>" << endl;
    cout << "Encoded: " << result << endl;
    cout << "Decoded: " << decoded << endl;
    cout << "%: " << (float)(decoded.length() * 8) / (float)(result.length() * encoded.size()) << endl << endl;
}