#define _CRT_SECURE_NO_WARNINGS
#include "File.h";
#include "HashMap.h";
#include "BinTree.h";
#include "BalanceTree.h";

void File::log(string fileName, bool flag) {
	ifstream read;
	auto type = flag ? ios::in | ios::binary : ios::in;
	read.open(fileName, type);
	if (!read) cerr << "404" << endl;
	Record record;
	read.read((char*)&record, sizeof(Record));
	while (!read.eof()){
		if (flag) {
			cout << record.en << ", " << record.ru << endl;
			read.read((char*)&record, sizeof(Record));
		} else {
			string en; string ru;
			getline(read, en);
			getline(read, ru);
			cout << en << ", " << ru << endl;
		}
	}
	read.close();
}

void File::convert(string txt, string bin, bool flag) {
	fstream binStream; 
	fstream txtStream;
	Record record;

	auto t2 = ios::in | ios::out;
	auto t1 = t2 | ios::binary;
	binStream.open(bin, !flag ? t1 | ios::trunc : t1);
	txtStream.open(txt, flag ? t2 | ios::trunc : t2);

	if (!txtStream || !binStream) cerr << "Can't open file" << endl;

	if (flag) {
		binStream.read((char*)&record, sizeof(Record));
		while (!binStream.eof()) {
			txtStream << record.en << endl;
			txtStream << record.ru << endl;
			binStream.read((char*)&record, sizeof(Record));
		}
	} else {
		while (!txtStream.eof()) {
			txtStream.getline(record.en, 30);
			txtStream.getline(record.ru, 30);
			binStream.write((char*)&record, sizeof(Record));
		}
	}

	binStream.close();
	txtStream.close();
}

void File::random(string fileName) {
	ofstream write;
	srand(time(NULL));
	write.open(fileName, ios::out | ios::trunc);
	Record record;

	int count = rand() % 30 + 5;
	char enDict[27] = "abcdefghijklmnopqrstuvwxyz";
	char ruDict[34] = "àáâãäå¸æçèéêëìíîïðñòóôõö÷øùúûüýþÿ";
	for (int i = 0; i < count; ++i) {
		char en[30]; char ru[30];
		int j = 0;
		int size = rand() % 20 + 5;
		for (j = 0; j < size; ++j) {
			int enRandom = rand() % (26);
			en[j] = enDict[enRandom];
			int ruRandom = rand() % (33);
			ru[j] = ruDict[ruRandom];
		}
		en[j] = '\0';
		ru[j] = '\0';

		write << en << endl;
		write << ru;
		if (i != count - 1) write << endl;
	}
	write.close();
}

void File::replaceByLast(string key, Record record) {
	bool flag = false;

	fstream stream;
	stream.open(fileName, ios::in | ios::out | ios::binary);
	if (!stream) cerr << "Can't open file" << endl;
	stream.read((char*)&record, sizeof(Record));

	int i = 0;
	while (!stream.eof()){
		if (record.en == key) {
			int recSize = sizeof(Record);
			stream.seekg(-recSize, ios::cur);
			stream.write((char*)&record, sizeof(Record));
			flag = true;
			break;
		} else {
			i++;
			stream.read((char*)&record, sizeof(Record));
		}
	}

	if (!flag) cout << "404" << endl;
	stream.close();
}

Record File::last() {
	Record record;
	ifstream stream;

	stream.open(fileName, ios::in | ios::binary);
	if (!stream) cerr << "Can't open file" << endl;
	int recSize = sizeof(Record);
	stream.seekg(-recSize , ios::end);
	stream.read((char*)&record, sizeof(Record));
	stream.close();

	return record;
}

void File::list(char letter) {
	ifstream read;
	Record record;

	read.open(fileName, ios::in | ios::binary);
	if (!read) cerr << "Can't open file" << endl;

	read.read((char*)&record, sizeof(Record));
	while (!read.eof()){
		if (record.en[0] == letter) cout << record.en << ", " << record.ru << endl;
		read.read((char*)&record, sizeof(Record));
	}

	read.close();
}

void File::search(string fileName, int position) {
	Record record;
	ifstream read;

	read.open(fileName, ios::in | ios::binary);
	if (!read) cerr << "Can't open file" << endl;

	read.seekg((position - 1) * sizeof(Record), ios::beg);
	read.read((char*)&record, sizeof(Record));
	if (!read.eof()) cout << record.en << ", " << record.ru << '\n';
	else cerr << "404" << endl;
	read.close();
}

void File::remove(string fileName, string key) {
	fstream stream;
	stream.open(fileName, ios::in | ios::binary);
	Record a[10000];
	int k = 0;
	stream.read((char*)&a[k], sizeof(Record));

	while (!stream.eof()) {
		if (a[k].en == key) stream.read((char*)&a[k], sizeof(Record));
		else {
			k++;
			stream.read((char*)&a[k], sizeof(Record));
		}
	}

	stream.close();

	stream.open(fileName, ios::out | ios::binary | ios::trunc);
	for (size_t j = 0; j < k; j++) stream.write((char*)&a[j], sizeof(Record));
	stream.close();
}

void File::update(string en, string ru) {
	Record record;
	fstream stream;
	bool flag = false;
	
	stream.open(fileName, ios::in | ios::out | ios::binary);
	if (!stream) cerr << "Can't open file" << endl;

	stream.read((char*)&record, sizeof(Record));
	while (!stream.eof()) {
		if (record.en == en) {
			for (int i = 0; i < ru.length(); i++) record.ru[i] = ru[i];
			for (int i = ru.length(); i < 30; i++) record.ru[i] = 0;
			record.ru[ru.length()] = '\0';
			int recSize = sizeof(Record);
			stream.seekg(-recSize, ios::cur);
			stream.write((char*)&record, sizeof(Record));
			flag = true;
			return;
		}
		stream.read((char*)&record, sizeof(Record));
	}

	if (flag == false) cout << "404" << endl;
	stream.close();
}

void File::add(string fileName, char en[30], char ru[30]) {
	ofstream write;
	write.open(fileName, ios::out | ios::binary | ios::app);
	if (!write) cerr << "Can't open file" << endl;
	Record record;

	strcpy(record.en, en);
	strcpy(record.ru, ru);

	write.write((char*)&record, sizeof(Record));
	write.close();
}

File::File(string name) : fileName(name) {

	Menu menu({ "Return", "->txt", "Log", "Replace by last", "First letter list", "Update translation", "Hash map operations", "Bin tree operations", "Balance tree operations" });
	int command = menu.prompt();

	while (command != 0) {
		if (command == 1) {
			string txt; cout << "Txt file name: ";  cin >> txt;
			convert(txt, fileName, true);
		}
		else if (command == 2) {
			Menu submenu({ "All", "By position" });
			int command = submenu.prompt();
			if (command == 0) log(fileName, true);
			else {
				int position; cout << "Position: ";  cin >> position;
				search(fileName, position);
			}
		}
		else if (command == 3) {
			string key; cout << "Key: ";  cin >> key;
			replaceByLast(key, last());
		}
		else if (command == 4) {
			char letter; cout << "Letter: "; cin >> letter;
			list(letter);
		}
		else if (command == 5) {
			string key, ru; cout << "Key: ";  cin >> key; cout << "RU: "; cin >> ru;
			update(key, ru);
		}
		else if (command == 6) HashMap hashmap(fileName);
		else if (command == 7) BinTree tree(fileName);
		else if (command == 8) BTree tree(3, fileName);

		command = menu.prompt();
	};
}