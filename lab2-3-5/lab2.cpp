#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Menu.h";
#include "File.h";
using namespace std;

int main() {
	system("cls");
	setlocale(LC_ALL, "rus");
	Menu menu({ "Exit", "Open / Create file", "txt->bin", "Random txt gen", "Log txt file" });
	int command = menu.prompt();
	while (command != 0) {
		string fileName, txt, bin;
		if (command == 1) {
			cout << "File name: ";
			cin >> fileName;
			File file(fileName);
		} else if(command == 2) {
			cout << "Txt name: ";  cin >> txt; cout << "Bin name: "; cin >> bin;
			File::convert(txt, bin, false);
		} else if (command == 3) {
			cout << "File name: ";
			cin >> fileName;
			File::random(fileName);
		} else if (command == 4) {
			cout << "File name: ";
			cin >> fileName;
			File::log(fileName, false);
		}

		command = menu.prompt();
	};
	
	return 0;
}