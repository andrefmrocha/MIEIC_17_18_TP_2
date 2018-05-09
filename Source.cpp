#include "stdafx.h"
#include "cwcreator.h"
#include <stdio.h>

//String manipulation function that makes the program case insensitive by receiving the user input,
// whether its capitalized or not and alters it so be readble by the program functions

void UpperInput(string &input) {
	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);  //goes through the string using toupper to every character belonging to the string
	}
}

bool validDic(cwcreator board) {
	if (board.getWords() == -1)
		return false;
	else return true;
}

void createpuzzle() {
	for (int i = 0; i < 55; i++)
		cout << "-";
	cout << endl << "CREATE PUZZLE" << endl;
	for (int i = 0; i < 55; i++)
		cout << "-";
	bool valid = false; // boolean to be used as a flag for incorrect input
	int l, c;
	string dicfile;  //will receive the dictionary file name specified by the user
	do {
		cout << endl << "Board size (lines columns) ? ";
		cin >> l >> c;
		cout << endl << "Dictionary file name ? ";
		cin >> dicfile;
		cwcreator dummyb(l, c, dicfile);  //creates a dummy board with the
		valid = validDic(dummyb); //validates the dictionary 
	} while (!valid);
	cwcreator brd(l, c, dicfile);
	cout << endl;
	brd.board_show();
	cout << endl;
	string pos, word;
	do {
		cout << endl << "Position(LCD / CTRL - Z = stop) ? ";
		cin >> pos;
		if (cin.eof())
			break;
		cout << endl << "Word ( - = remove / ? = help ) ? ";
		cin >> word;
		if (word == "-") {
			string toerase;
			do {
				cout << endl << "Which word do you want to erase ? ( X = back ) ";
				cin >> toerase;
				UpperInput(toerase);
				if (toerase == "X")
					break;
				cout << endl;
			} while (!brd.eraseWord(toerase));
			cout << endl << endl;
			brd.board_show();
			cout << endl;
			continue;
		}
		else if (word == "?") {
			 if (!brd.helpWord(pos))
				continue;
			cout << "Word ? ";
			cin >> word;
		}
		UpperInput(word);
		if (!brd.addWord(pos, word))
			continue;
		brd.board_show();
		cout << endl;
	} while (true);
	cin.clear();
	cout << "Do you wish to save your board or exit the program (and lose all progress)? ( S = save / X = exit) ";
	string ans;
	bool valinput = true;
	do {
		cin >> ans;
		UpperInput(ans);
		if (ans == "S") {
			brd.board_save();
			valinput = true;
		}
		else if (ans == "X")
			return;
		else
			valinput = false;
			cout << endl << "Incorrect input, please answer again: ";
	} while (!valinput);
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