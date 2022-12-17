#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Menu {
private:
	void list();
	vector<std::string> commands;

public:
	int prompt();
	Menu(vector<std::string> arg) : commands(arg){}
};