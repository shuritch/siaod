#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class FileMenu {
public:
    ifstream fin;
    ofstream fout;

    void init(int option) {
        switch (option) {
        case 0: {
            bool status = fin.good();
            bool status2 = fout.good();
            if (!status || !status2) cout << "ERROR while closing file" << endl;
            fin.close();
            fout.close();
            cout << "File closed" << endl;
            return;
        };
        case 1: {
            logFile();
            break;
        }
        case 2: {
            int orderNumber, number;
            cout << "Order number: ";
            cin >> orderNumber;
            number = logNumber(orderNumber);
            if (fin.eof() && number != 0) cout << "Not matched" << endl;
            else cout << "Number: " << number << endl;
            break;
        }
        case 3: {
            addRow();
            break;
        }
        case 4: {
            numbersCounter();
            break;
        }
        case 5: {
            string newName;
            cout << "New file name: ";
            cin >> newName;
            createFileFromExists(newName);
            break;
        }
        case 100: {
            string fileName;
            cout << "File name: ";
            cin >> fileName;
            openFile(fileName);
            if (!fin.is_open()) {
                cout << "Error on file opening" << endl;
                return;
            };
            cout << "File opened" << endl;
            break;
        }
        default: cout << "Option not found" << endl;
        }
        optionCheck();
    }
    void addRow() {
        string row;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Row: ";
        getline(cin, row);
        fout << row << endl;
    }
    void optionCheck() {
        int option;
        list();
        cout << "Option: ";
        cin >> option;
        init(option);
    }
    void logFile() {
        std::streamoff p = 0;
        string log;
        fin.seekg(p);
        while (getline(fin, log)) {
            cout << log << endl;
            if (fin.tellg() == -1) p = p + log.size();
            else p = fin.tellg();
        }
        fin.clear();
    }
    int logNumber(int num) {
        std::streamoff p = 0;
        fin.seekg(p);
        int number = 100;
        while (num != 0 && !fin.eof()) {
            --num;
            fin >> number;
        }
        return number;
    }
    void numbersCounter() {
        std::streamoff p = 0;
        fin.seekg(p);
        size_t numbers_counter = 0;
        std::string buffer;
        while (fin >> buffer) ++numbers_counter;
        cout << "Numbers count: " << numbers_counter << endl;
        fin.clear();
    }
    void openFile(string name) {
        fin.open(name.c_str(), fstream::in | ios_base::app);
        fout.open(name.c_str(), fstream::out | ios_base::app);
    }
    void list() {
        cout << endl;
        cout << "\tFILE MENU" << endl;
        cout << "Enter list number to continue" << endl;
        cout << "0: Close file" << endl;
        cout << "1: Log file" << endl;
        cout << "2: Log number by order number" << endl;
        cout << "3: Add new row" << endl;
        cout << "4: Numbers counter" << endl;
        cout << "5: Create file from this file (even values * max)" << endl;
    }
    void createFileFromExists(string newName) {
        ofstream fout2;
        fout2.open(newName, fstream::in | fstream::out | fstream::trunc);
        std::streamoff p = 0;
        fin.seekg(p);
        vector<int> numbers;
        int max = INT_MIN;
        while (!fin.eof()) {
            int number;
            fin >> number;
            numbers.push_back(number);
            if (max < number) max = number;
        }
        for (int& number : numbers) {
            number *= max;
            fout2 << number << ' ';
        }
        if (!fout2.good()) cout << "Error on new file closing" << endl;
        fout2.close();
        fin.clear();
    }
};

class Menu {
public:
    void init() {
        cout << endl;
        list();
        int option;
        cout << "Option number: ";
        cin >> option;
        if (option == 0) return;
        if (option == 1) {
            FileMenu fileMenu;
            fileMenu.init(100);
        }
        init();
    }

protected:
    void list() {
        cout << "\tMAIN MENU" << endl;
        cout << "Enter list number to continue" << endl;
        cout << "0: Exit" << endl;
        cout << "1: Create/Open file" << endl;
    }
};

int main()
{
    Menu menu;
    menu.init();
    cout << endl << "Program finsihed" << endl;
}