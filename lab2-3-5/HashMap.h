#pragma once
#include "Menu.h";
#include "File.h";

struct Hash {
	char key[30];
	int position;
};

class HashMap {
private:
	string fileName;
	size_t size = 10000;
	void search(string key);
	void remove(string key);
	void create();
	void add();
	void log();
	int length();
	unsigned long hash(string str);

public: 
	Hash table[10000] = { 0 };
	HashMap(string fileName);
};