#include "Menu.h";

void Menu::list() {
	size_t i = 0;
	for (auto command : commands) { cout << i << ") " << command << endl; ++i; }
}

int Menu::prompt() {
	cout << "+--------------------------------------------------------------------------+" << endl;
	this->list();
	int choice = -1;
	cout << "Command: ";
	cin >> choice;
	return choice;
	cout << "+--------------------------------------------------------------------------+" << endl;
}


