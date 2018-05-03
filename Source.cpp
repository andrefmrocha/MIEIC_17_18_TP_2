#include "stdafx.h"
#include "cwcreator.h"
void createpuzzle() {
	for (int i = 0; i < 55; i++)
		cout << "-";
	cout << endl << "CREATE PUZZLE" << endl;
	for (int i = 0; i < 55; i++)
		cout << "-";
	cout << endl << "Board size (lines columns) ? ";
	int l, c;
	cin >> l >> c;
	cwcreator b1(l, c);  //creates a new board with the user specified settings
	cout << endl;
	b1.board_show();
	string pos, word;
	do {
		cout << "Position(LCD / CTRL - Z = stop) ? ";
		cin >> pos;
		if (cin.eof())
			break;
		cout << "Word ( - = remove / ? = help ) ? ";
		cin >> word;
		b1.addWord(pos, word);
		b1.board_show();
		cout << endl;
	} while (true);
}

void resumepuzzle() {}

//just a function to present the first program and its instructions to the user
void introduction() {
	cout << "CROSSWORDS PUZZLE CREATOR" << endl;
	for (int i = 0; i < 55; i++)
		cout << "=";
	cout << endl << endl;
	cout << "INSTRUCTIONS:" << endl << endl;
	cout << "1 - Dictionary file name:" << endl;
	cout << " Specify the text file where the dictionary is from." << endl;
	cout << "2 - Board size (lines columns):" << endl;
	cout << " Choose how many lines and columns the board will have." << endl;
	cout << "3 - Position (LCD / CTRL-Z = stop ):" << endl;
	cout << " LCD stands for Line Column and Direction." << endl;
	cout << "4 - Word ( - = remove / ? = help ):" << endl;
	cout << " Choose the word you want to insert in the board " << endl;
	cout << "or choose an alternative option, to remove a word " << endl;
	cout << "from the board writing '-' or if you're in a dead end," << endl;
	cout << "ask for a possible word with the help option '?'." << endl << endl;
}

int main() {
	introduction();
	for (int i2 = 0; i2 < 55; i2++)
		cout << "-";
	cout << endl << "OPTIONS :" << endl << "1 - Create puzzle" << endl;
	cout << "2 - Resume puzzle" << endl << "0 - Exit" << endl;
	cout << endl << "Option ? ";
	int op;
	cin >> op;
	switch (op) {
	case 1: createpuzzle();
	case 2: resumepuzzle();
	case 0: return 0;
	}
}