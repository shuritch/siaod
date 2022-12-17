#define _CRT_SECURE_NO_WARNINGS
#include "HashMap.h"
#include "File.h"

void HashMap::search(string key){
	size_t index = hash(key); 
	size_t position;
	
	while (table[index].key != key) {
		index++;
		if (index > size) {
			cerr << "404" << endl;
			return;
		}
	}

	position = table[index].position;
	File::search(fileName, position);
}

void HashMap::log() {
	for (size_t i = 0; i < size; i++) {
		if (!table[i].key[0]) continue;
		cout << "Hash: " << i << endl;
		cout << "Key: " << table[i].key << endl;
		cout << "Position: " << table[i].position << endl;
		if (i != hash(table[i].key) % size) cout << "COLLISION" << endl;
	}
}

void HashMap::add() {
	char en[30], ru[30];
	cout << "English word: ";
	cin >> en;
	cout << "Russian translate: ";
	cin >> ru;

	File::add(fileName, en, ru);

	int index = hash(en);
	while (table[index].key[0] != NULL) ++index;

	strcpy(table[index].key, en);
	table[index].position = length() + 1;
}

int HashMap::length() {
	int max = 0;
	for (size_t i = 0; i < size; i++)
		if (table[i].position != NULL && table[i].position > max)
			max = table[i].position;
	return (max);
}

unsigned long HashMap::hash(string str) {
	unsigned long i = 0;
	for (size_t j = 0; str[j]; j++) i += str[j];
	return i % size;
}

void HashMap::create(){
	ifstream read;
	Record record;
	read.open(fileName, ios::in | ios::binary);
	if (!read) cerr << "Can't open file" << endl;
	read.read((char*)&record, sizeof(Record));
	unsigned long index;
	int i = 0;
	
	while (!read.eof()) {
		unsigned long index = hash(record.en);
		while(table[index].key[0] != NULL) ++index;
		strcpy(table[index].key, record.en);
		table[index].position = i;
		i++;
		read.read((char*)&record, sizeof(Record));
	}

	read.close();
}

HashMap::HashMap(string name) : fileName(name) {
	create();
	Menu menu({ "Return", "Log table", "Add record", "Remove record", "Search record" });
	int command = menu.prompt();
	while (command != 0) {
		if (command == 1) {
			log();
		} else if (command == 2) {
			add();
		} else if (command == 3 || command == 4) {
			string key; cout << "Key: "; cin >> key;
			command == 3 ? remove(key) : search(key);
		}
		command = menu.prompt();
	}
}

void HashMap::remove(string key) {
	for (size_t i = 0; i < size; i++) {
		if (table[i].key != key) continue;
		File::remove(fileName, key);
		for (size_t i = 0; i < size; i++) table[i] = { NULL };
		create();
		break;
	}
}