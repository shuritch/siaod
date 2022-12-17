#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <ctime>
#include "Menu.h";
using namespace std;

struct Record {
	char en[30];
	char ru[30];
};

class File {
private:
	string fileName;
	Record last();
	void replaceByLast(string en, Record record);
	void list(char letter);
	void update(string en, string ru);

public:
	static void search(string fileName, int position);
	static void add(string fileName, char en[30], char ru[30]);
	static void convert(string txt, string bin, bool flag);
	static void random(string fileName);
	static void log(string fileName, bool flag);
	static void remove(string fileName, string key);
	File(string name);
};