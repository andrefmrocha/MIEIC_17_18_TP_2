#include "stdafx.h"
#include "cwplayer.h"
#include "Player.h"

//String manipulation function that makes the program case insensitive by receiving the user input,
// whether its capitalized or not and alters it so be readble by the program functions

void UpperInput(string &input) {
	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);  //goes through the string using toupper to every character belonging to the string
	}
}

string getdestination(string board) {
	string middle = "_p";
	string part1 = board.substr(0, 4);
	string part2 = board.substr(4, 4);
	return part1 + middle + part2;
}

void introduction() {
	cout << "CROSSWORDS PLAYER" << endl;
	for (int i = 0; i < 114; i++)
		cout << "=";
	cout << endl << "Welcome to CROSSWORDS PLAYER!" << endl;
	cout << "In this game you'll be presented with an empty board and asked to fill with valid words" << endl;
	cout << "The board has lines indicated with capitalized letters (e.g.: A or B)" << endl;
	cout << "and columns are indicated withuncapitilazed letters (e.g.: a or b)" << endl;
	cout << "Lets go over some quick rules to get you set up to play this fun game (and win, obviously):" << endl;
	for (int i2 = 0; i2 < 114; i2++)
		cout << "_";
	cout << endl << "1 - Type your name. "<<endl;
	cout << " If you want others to know who is the Crosswords King, you have to put your name in it." << endl;
	cout << endl << "2 - Write the name of the board you want to play." << endl;
	cout << " To call a board, write: bXXX.txt (e.g.: b001.txt or b420.txt)." << endl;
	cout << endl << "3 - Then you'll be shown an empty board, followed by hints to the words separated " << endl;
	cout << " by their position and direction." << endl;
	cout << " We wouldn't want to make things too hard for you, so now there's no excuses " << endl;
	cout << " for a perfect game!" << endl;
	cout << "4 - Indicate the position where you want to insert a word using the format LcD." << endl;
	cout << " This stands for Line, column and Direction. Remember, the case is important!" << endl;
	cout << endl << "5 - You choose where do you want to insert a word or if you want to remove" << endl;
	cout << " a previously inserted word. " << endl;
	cout << " Don't worry if you mess up, we have your back! Use '-' to remove a word." << endl;
	cout << endl << "6 - If you need help, you can call it writing '?' when asked for a word." << endl;
	cout << " If the first hint wasn't enough, here you go. But attention, "<< endl;
	cout << " we are keeping an eye on the number of hints you use so watch out!" << endl;
	cout << endl << "7 - If you want to go back enter X, but be careful you might lose all progress!" << endl;
	cout << endl << "8 - When you finish the board, we'll check if all words are valid." << endl;
	cout << " If so, your performance will be saved, with your name, time spent of the board and number of hints used." << endl;
	cout << " Otherwise you get to erase the invalid words and try again " << endl;
	cout << endl << "HAVE FUN!" << endl;
	for (int i3 = 0; i3 < 114; i3++)
		cout << "-";
	cout << endl;
}

void finishplay(cwplayer game, Player p1,string dest) {
	ofstream outfile(dest);
	unsigned long duration = p1.finishGame();
	outfile << p1.GetName() << " - Elapsed time: " << duration << " seconds. Number of hints used: " << game.getNumHints();//<< number of hints
}

void playgame(cwplayer game, Player p1, string board) {
	string pos, word;
	string confirm;
	bool flag;
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
			if (word == "x" || word == "X") {
				cout << "You lose all progress, are you sure you want to exit? (Enter Y to confirm): ";
				cin >> confirm;
				UpperInput(confirm);
				if (confirm == "Y")
					return;
			}
			else break;
		} while (true);
		if (word == "-") {
			do {
				cout << endl << "Which word do you want to erase ? ( X = back ) ";
				do {
					cin >> word;
					if (cin.eof())
						cin.clear();
					else {
						UpperInput(word);
						break;
					}
				} while (true);
				if (word == "X")
					break;
				cout << endl;
			} while (!game.removePlayerWord(word));
			cout << endl << endl;
			game.game_show();
			cout << endl;
			continue;
		}
		else if (word == "?") {
			if (!game.helpPlayerword(pos)) //needs changing - help function
				continue;
			else {
				cout << "Word ? ";
				do {
					cin >> word;
					if (cin.eof())
						cin.clear();
					else break;
				} while (true);
				cout << endl;
			}
		}
		UpperInput(word);
		if (!game.addPlayerWord(pos, word)) {
			cout << endl;
			continue;
		}
		game.game_show();
		cout << endl;
	} while (true);
	cin.clear();
	while (!game.checkBoard()) {
		do {
			cout << endl << "Which word do you want to replace ? ";
			do {
				cin >> word;
				if (cin.eof())
					cin.clear();
				else {
					UpperInput(word);
					break;
				}
			} while (true);
			if (word == "X") {
				cout << "You lose all progress, are you sure you want to exit? (Enter Y to confirm): ";
				do {
					cin >> confirm;
					if (cin.eof())
						cin.clear();
					else {
						UpperInput(confirm);
						break;
					}
				} while (true);
				if (confirm == "Y")
					return;
			}
			cout << endl;
		} while (!game.removePlayerWord(word));
		cout << endl << endl;
		pos = game.findPosition(word);
		game.game_show();
		cout << "What word do you want write instead ? ";
		do {
			do {
				cin >> word;
				if (cin.eof())
					cin.clear();
				else {
					UpperInput(word);
					break;
				}
			} while (true);
			if (!game.addPlayerWord(pos, word)) {
				cout << endl;
				continue;
			}
			else break;
		} while (true);
	}
	string dest = getdestination(board);
	cout << " Congratulations, you won!" << endl << endl << " Your data will be saved in the file: " << dest << "." << endl;
	finishplay(game, p1,dest);

}

int main() {
	introduction();
	string playername;
	cout << "What is your name ? ";
	do {
		cin >> playername;
		if (cin.eof())
		{
			cin.clear();
			continue;
		}
		else break;
	} while (true);
	Player p1(playername);
	string board;
	cwplayer game1;
	cout << endl << "What board do you want play in ? ";
	do {
		cin >> board;
		if (cin.eof())
		{
			cin.clear();
			continue;
		}
		else if (board == "x" || board == "X") {
			cout << "The game is over. Hope you had fun!" << endl;
			return 0;
		}
		else if (!game1.readFile(board)) {
			cout << "Try again : ";
			continue;
		}
		else {
			game1.getDict(board);
			break;
		}
	} while (true);
	game1.startGame();
	playgame(game1, p1,board);
	cout << endl << "The game is over. Hope you had fun!" << endl;
}