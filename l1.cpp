#include <iostream>
#include <vector>
using namespace std;

class Menu {
private:
	void list(); 
	vector<std::string> commands;

public:
	int prompt();
	Menu(vector<std::string> arg) : commands(arg) {}
};

void Menu::list() {
	size_t i = 0;
	for (auto command : commands) { cout << i << " => " << command << endl; ++i; }
}

int Menu::prompt() {
	this->list();
	int choice = -1;
	cout << "Command: ";
	cin >> choice;
	return choice;
}

void log(int x) {
	for (int i = 15; i >= 0; i--) {
		cout << ((x >> i) & 1);
	}
	cout << "\n";
}

int program_1(int x) {
	int mask = 0xf;
	cout << "Маска: "; log(0xf);
	return x | mask;
}


int program_2(int x) {
	long long mask = 4294965207;
	cout << "Маска: "; log(mask);
	return x & mask;
}

int program_3(int x) { return(x << 4); }
int program_4(int x) { return(x >> 4); }
int program_5(int x, int n) {
	long long mask = pow(2, 32);
	mask = mask >> (32 - n);
	return x | mask;
}


int main() {
	setlocale(LC_ALL, "rus");
	Menu menu({"Выход", "Задание 1", "Задание 2", "Задание 3", "Задание 4", "Задание 5"});
	int command = menu.prompt();
	while (command != 0) {
		int temp, n;
		if (command == 1) {
			cout << "Перевод 4-х младших бит в значение 1" << "\n";
			cout << "Число: 256 = 100 = "; log(0x100);
			temp = program_1(0x100);
			cout << "Стало: "; log(temp);
		}
		else if (command == 2) {
			cout << "Обнулить 3-ий, 11-ый, 5-ый биты" << "\n";
			cout << "Введите число: ";
			cin >> temp;
			cout << "Было: "; log(temp);
			temp = program_2(temp);
			cout << "Стало: "; log(temp);
		}
		else if (command == 3) {
			cout << "Умножить число на 16" << "\n";
			cout << "Введите число: ";
			cin >> temp;
			cout << "Было: "; log(temp);
			temp = program_3(temp);
			cout << "Стало: "; log(temp);
		}
		else if (command == 4) {
			cout << "Поделить число на 16" << "\n";
			cout << "Введите число: ";
			cin >> temp;
			cout << "Было: "; log(temp);
			temp = program_4(temp);
			cout << "Стало: "; log(temp);
		}
		else if (command == 5) {
			cout << "Перевод n-го бита в 1 используя маску 2" << "\n";
			cout << "Введите число: ";
			cin >> temp;
			cout << "Введите номер бита: ";
			cin >> n;
			cout << "Было: "; log(temp);
			temp = program_5(temp, n);
			cout << "Стало: "; log(temp);
		}
		command = menu.prompt();
	}

	return 0;
}
