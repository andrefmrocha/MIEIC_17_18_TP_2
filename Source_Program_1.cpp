#include "stdafx.h"
#include "cwcreator.h"

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

void constructboard(cwcreator brd) {
	brd.board_show();
	cout << endl;
	string pos, word;
	do {
		cout << endl << "Position(LCD / CTRL - Z = stop) ? ";
		cin >> pos;
		if (cin.eof())
			break;
		cout << endl << "Word ( - = remove / ? = help ) ? ";
		do {
			cin >> word;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);
		if (word == "-") {
			string toerase;
			do {
				cout << endl << "Which word do you want to erase ? ( X = back ) ";
				do {
					cin >> toerase;
					if (cin.eof())
						cin.clear();
					else {
						UpperInput(toerase);
						break;
					}
				} while (true);
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
			do {
				cin >> word;
				if (cin.eof())
					cin.clear();
				else break;
			} while (true);
		}
		UpperInput(word);
		if (!brd.addWord(pos, word))
			continue;
		brd.board_show();
		cout << endl;
	} while (true);
	cin.clear();
	cout << endl << "Do you wish to save your board, finish the board or exit without saving (and lose all progress) ?" << endl;
	cout << "(S = save and resume later / F = finish / X = exit) ";
	string ans;
	bool valinput = true;
	do {
		do {
			cin >> ans;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);
		UpperInput(ans);
		if (ans == "S") {
			brd.board_save();
			cout << endl << "Saved successfully!" << endl;
			valinput = true;
		}
		else if (ans == "F") {
			brd.finishBoard();
			brd.board_save();
			cout << endl << "Finished! " << endl;
			return;
		}
		else if (ans == "X") {
			cout << "Exiting..." << endl<< endl;
			return;
		}
		else {
			valinput = false;
			cout << endl << "Incorrect input, please answer again: ";
		}
	} while (!valinput);
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
		do {
			cin >> l;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);
		do {
			cin >> c;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);
		cout << endl << "Dictionary file name ? ";
		do {
			cin >> dicfile;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);
		cwcreator dummyb(l, c, dicfile);  //creates a dummy board with the
		valid = validDic(dummyb); //validates the dictionary
	} while (!valid);
	cwcreator brd(l, c, dicfile);
	cout << endl;
	constructboard(brd);
}

void resumepuzzle() {
	cout << "Which board do you want to resume (bXXX.txt - from 001 to 999) ? ";
	string boardname;
	cwcreator resboard;
	do {
		do {
			cin >> boardname;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);		
		if (!resboard.readFile(boardname)) {
			cout << "Please write again: ";
			continue;
		}
		else {
			resboard.getDict(boardname);
			constructboard(resboard);
			break;
		}
	} while (true);
}

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
	cout << "3 - Position (LcD / CTRL-Z = stop ):" << endl;
	cout << " LCD stands for Line column and Direction." << endl;
	cout << " E.g.: AaV - Line A, column a and vertical direction." << endl;
	cout << "4 - Word ( - = remove / ? = help ):" << endl;
	cout << " Choose the word you want to insert in the board " << endl;
	cout << " or choose an alternative option, to remove a word " << endl;
	cout << " from the board writing '-' or if you're in a dead" << endl;
	cout << " end, ask for a possible word with the help option '?'." << endl << endl;
}

int main() {
	introduction();
	for (int i2 = 0; i2 < 55; i2++)
		cout << "-";
	bool flag = true;
	do {
		cout << endl << "OPTIONS :" << endl << "1 - Create puzzle" << endl;
		cout << "2 - Resume puzzle" << endl << "0 - Exit" << endl;
		cout << endl << "Option ? ";
		int op;
		do {
			cin >> op;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);
		switch (op) {
		case 1: createpuzzle();
			break;
		case 2: resumepuzzle();
			break;
		case 0: flag = false;
			break;
		}
	} while (flag);
	return 0;
}