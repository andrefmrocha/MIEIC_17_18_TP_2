#include <climits>
#include "cwcreator.h"
#ifdef __unix__
#define EOF_COMMAND "CTRL - D"    // this special situation checks the user OS and since linux and windows have different
#else							  // hotkeys to do cin.eof(), when its use is necessary, the message will show the appropriate key
#define EOF_COMMAND "CTRL - Z"
#endif

/***************************************************************************
* *************************** UpperInput ***********************************
* String manipulation function that makes the program case insensitive by 
* receiving the user input, whether its capitalized or not and alters it so 
* it can be read by the program functions
* @param &input
*/
void UpperInput(string &input) {
	for (int i = 0; i < input.length(); i++) {
		input[i] = toupper(input[i]);  //goes through the string using toupper to every character belonging to the string
	}
}

/***************************************************************************
* *************************** validDic *************************************
* This simple funtion checks if the file opened to the dictionary class was
* valid. This is more of an control method to make the code more robust 
* against invalid inputs.
* @param board
*/
bool validDic(cwcreator board) {
	if (board.getWords() == -1)  // -1 is the chosen "flag" to indicate invalid dictionaries, set in the board attribute words
		return false;
	else return true;
}

/*********************************************************************************
* ****************************** constructboard **********************************
* This is the module function to build a board, according to the user directives.
* It's very robust against invalid inputs and always updates the board and presents
* it to the user everytime a change is made for a better interaction.
* @param brd
*/
void constructboard(cwcreator brd) {
	brd.board_show(); // it shows the board initially, empty
	cout << endl;
	string pos, word;	// these strings as the name indicates, will hold the position and the word(or the special functions)
	do {
		cout << endl << "Position(LCD /";
		cout << EOF_COMMAND;
		cout <<"= stop) ? ";          //asks for position according to the specific format (LCD).
		cin >> pos;													
		if (cin.eof()) {													
			cin.clear();
			break;
		}
		else if (!brd.positionalCheck(pos)) {				//checks if the input is a valid position
			cout << endl;
			continue;
		}
		cout << endl << "Word ( - = remove / ? = help ) ? ";		//asks for word, or the other special functions: remove or help
		do {
			cin >> word;
			if (cin.eof())
				cin.clear();
			else if (word == "x" || word == "X")					// this is specified in the program instructions, to make returns easier, without having to close the program
				break;
			else break;
		} while (true);
		if (word == "-") {
				cout << endl;
			if(!brd.eraseWord(pos))					// this tests if its possible to erase the word in said position 
			{
				cout <<"No word was found on that position." << endl;
				continue;
			}
			else
			{
				cout << endl << endl;
				brd.board_show();		// as said previously, after a effective change, the board will be presented to the user, so he/she can keep track of the board status
				cout << endl;
				continue;
			}
		}
		else if (word == "?") {              // when the user needs help bulding the board, he can call the help and have a reloadable list of possible words to fit in the desired position
			if (!brd.helpWord(pos))			// since the help function is a boolean function, already helping when a error occurs, 
				continue;                   // when this happens it goes back to the beggining of the cycle allowing a better flow of user-program interaction
			cout << "Word ? ";					
			do {							// after the list of possible words are presented, it is asked for a word, so the user can easily check the list before writing it to the program
				cin >> word;
				if (cin.eof())
					cin.clear();
				else break;
			} while (true);
		}
		UpperInput(word);
		if (word == "X")
			continue;
		else if (!brd.addWord(pos, word))		// this point is reached through normal addition of word or when the help function is called
			continue;						// then the add function is called, being a boolean function, allowing again a non-stop flow of the program interactions
		brd.board_show();              // again, the board is shown updated to the user
		cout << endl;
	} while (true);				// and so this goes on until the user doesn't want to edit the words in the board anymore
	cin.clear();            // this cin.clear() allows more input from the user since the cin.eof() sets the cin flag to bad
	cout << endl << "Do you wish to save your board, finish the board or exit without saving (and lose all progress) ?" << endl;
	cout << " (S = save and resume later / F = finish / X = exit) ";				// At this point the user can either save the board to be resumed later, 
	string ans;			//this string will hold the user answer						// finish the board (after that no more modifications are allowed)
	bool valinput = true;															// or exit the creation of the puzzle, losing all progress done
	do {
		do {
			cin >> ans;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);
		UpperInput(ans);
		if (ans == "S") {
			brd.board_save(); // calls the save function
			valinput = true;
		}
		else if (ans == "F") {
			brd.finishBoard();  // finish the board and saves
			brd.board_save();	// since this saving method is different from the above, a different message will also appear
			return;
		}
		else if (ans == "X") {
			cout << "Exiting..." << endl<< endl;   // this will exit the function
			return;
		}
		else {
			valinput = false;					// the valinput will insure no other input interfer, asking for input again
			cout << endl << "Incorrect input, please answer again: ";
		}
	} while (!valinput);
}

/***********************************************************************************
* ******************************** createpuzzle ************************************
* The main function to create a new puzzle. It asks for the board size and dictionary
* to start preparing a new board.
*/
void createpuzzle() {
	for (int i = 0; i < 55; i++)
		cout << "-";
	cout << endl << "CREATE PUZZLE" << endl;
	for (int i = 0; i < 55; i++)
		cout << "-";
	bool valid = false; // boolean to be used as a flag for incorrect input
	int l, c;			// number of lines and columns chosen by user
	string dicfile;  //will receive the dictionary file name specified by the user
	do {
		cout << endl << "Board size (lines columns) ? ";
        while (!(cin >> l))
        {
            cin.clear(); // clear the error flags						// this functions prevent the program from crashing
            cin.ignore(INT_MAX, '\n'); // discard the row				// when strings or chars are loaded into the int variables
        }
        while (!(cin >> c))
        {
            cin.clear(); // clear the error flags
            cin.ignore(INT_MAX, '\n'); // discard the row
        }
		cout << endl << "Dictionary file name ? ";
        cin >> dicfile;
		if (cin.eof())
		    cin.clear();
		if (dicfile == "x" || dicfile == "X")
		    return;
		cwcreator dummyb(l, c, dicfile);  //creates a dummy board with the arguments from the user to check if its valid. its a dummy since outside the cycle this object will not exist
		valid = validDic(dummyb); //validates the dictionary
	} while (!valid);
	cwcreator brd(l, c, dicfile);  //then creates the "real" board to be built in the constructboard() function
	cout << endl;
	constructboard(brd);
}

/***********************************************************************************
* ******************************** resumepuzzle ************************************
* This is the main function to resume the construction of a board. The user will
* have to give the file name where a board is stored. From there the construction
* function will be called and work in the same way as in the createpuzzle() function.
*/
void resumepuzzle() {
	cout << "Which board do you want to resume (bXXX.txt - from 001 to 999) ? ";
	string boardname;		// this string will hold the filename the user specifies
	cwcreator resboard;		// this board is created, as default, to be modified in the loading function and resume the puzzle creating
	do {
		do {
			cin >> boardname;
			if (cin.eof())
				cin.clear();
			else if (boardname == "x" || boardname == "X")
				return;
			else break;
		} while (true);		
		if (!resboard.readFile(boardname)) {			// this is the loading function, boolean aswell, and will read the contents
			cout << "Please write again: ";				//  of the saved board and load them into the resboard (contents of Board class)
			continue;						
		}
		else {
			resboard.getDict(boardname);		// this will load the dictionary into the board, to allow further puzzle construction (contents of Dictionary class)
			if (resboard.checkFinished()) {													// if this board is an already finished one, any further modification 
				cout << endl << "This board is finished, it can't be modified." << endl;	// won't be allowed, exiting the function
				return;
			}
			resboard.checkWords();		// this will check which words are in fact in the dictionary (since its an requirement to properly finish a board)
			constructboard(resboard);
			break;
		}
	} while (true);
}

/***********************************************************************************
* ******************************** introduction ************************************
* This function was separated from the main function because it has big quantity of
* text to be shown. The program is presented to the user, aswell its instructions.
*/
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
	cout << "3 - Position (LcD / " << EOF_COMMAND << " = stop ):" << endl;
	cout << " LCD stands for Line column and Direction." << endl;
	cout << " E.g.: AaV - Line A, column a and vertical direction." << endl;
	cout << "4 - Word ( - = remove / ? = help ):" << endl;
	cout << " Choose the word you want to insert in the board " << endl;
	cout << " or choose an alternative option, to remove a word " << endl;
	cout << " from the board writing '-' or if you're in a dead" << endl;
	cout << " end, ask for a possible word with the help option '?'." << endl;
	cout << "5 - Enter X to go back (NOTE: you may lose your progress). " << endl << endl;
}

/***********************************************************************
* ****************************** main **********************************
* The main function of the Program 1. It works has the main menu of the
* CROSSWORDS PUZZLE CREATOR. After create or resume puzzle are called it
* returns to the main menu, allowing the user to use all functionalties
* without ever having to shut down.
*/
int main() {
	introduction();  //calls the introduction function and shows the messages
	for (int i2 = 0; i2 < 55; i2++)
		cout << "-";
	bool flag = true;
	do {
		cout << endl << "OPTIONS :" << endl << "1 - Create puzzle" << endl;		//inside the cycle the user will choose if he/she wants to create,
		cout << "2 - Resume puzzle" << endl << "0 - Exit" << endl;				// resume a puzzle or simply exit the program
		cout << endl << "Option ? ";
		int op;
		do {
			cin >> op;
			if (cin.eof())
				cin.clear();
			else break;
		} while (true);
		switch (op) {					//the option selection is implemented with the switch case
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