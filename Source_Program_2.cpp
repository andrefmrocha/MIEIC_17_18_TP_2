#include "cwplayer.h"
#include "Player.h"
#ifdef __unix__
#define EOF_COMMAND "CTRL - D"	//this special situation checks the user OS and since linux and windows have different
#else
#define EOF_COMMAND "CTRL - Z"	//hotkeys to do cin.eof(), when its use is necessary, the message will show the appropriate key
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

/*******************************************************************************
* *************************** getdestination ***********************************
* Picks up the boardname and inserts the "_p" key in the middle of string since
* it's the desired format to save the game.
* @param board
*/
string getdestination(string board) {
	string middle = "_p";
	string part1 = board.substr(0, 4); // this will catch the "bXXX" part of the name, XXX being the board number
	string part2 = board.substr(4, 4); // this will catch the file extension ".txt"
	return part1 + middle + part2;	   // returns the name of the file to be saved
}

/******************************************************************************
* *************************** introduction ***********************************
* This function is called in the beggining of the program to show the user the
* instructions and informations about the game.
*/
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

/***************************************************************************
* *************************** finishplay ***********************************
* After a game reaches its end and the user wins the game, this function will
* call the finishing function and save the game data in the destination file
* as specified in the Program directives.
* @param game
* @param p1
* @param dest
*/
void finishplay(cwplayer game, Player p1,string dest) {
	ofstream outfile(dest);		// sets the output to the file desired
	unsigned long duration = p1.finishGame(); // gets the time (in seconds) that took the user to finish the game
	outfile << p1.GetName() << " - Elapsed time: " << duration << " seconds. Number of hints used: " << game.getNumHints();
}

/*****************************************************************************
* ***************************** playgame *************************************
* As the name indicates, this is the function where the game will mainly occur
* It will be asked to the user to select where and what word he want to write
* in the board, with all failsafes needed. Besides adding words, the user can 
* remove a previously written word or ask for help, and receive new hint for
* the word. After the user finishes writing words, the program will call a 
* check function to verify if the board has been filled correctly. If not the
* user will be able to make modifications until it is. The game is finished and
* the game data saved.
* @param game
* @param p1
* @param board
*/
void playgame(cwplayer game, Player p1, string board) {
	string pos, word; //these will hold the position and word to be added
	string confirm;  // this will be hold the confirmation string to ensure that the user wants to leave the game
	do {
		do {
			cout << endl << "Position(LCD /";
			cout << EOF_COMMAND;
            cout <<"= stop) ? ";
			cin >> pos;
			if (cin.eof()) {   // as seen in the Program 1 this condition clear the cin status in case the user calls cin.eof()
				cin.clear();
				break;
			} else if (!game.positionalCheck(pos)) {  // will only proceed if the position entered is a valid one
				cout << endl;
				continue;
			}
			cout << endl << "Word ( - = remove / ? = help ) ? ";
			do {
				cin >> word;
				if (cin.eof())
					cin.clear();
				else if (word == "x" || word == "X") {
					cout << "You lose all progress, are you sure you want to exit? (Enter Y to confirm): ";
					cin >> confirm;
					UpperInput(confirm);        // will only leave the program after confirmation to avoid
					if (confirm == "Y")            // accidental exits
						return;
				} else break;
			} while (true);
			if (word == "-") {                    // if the user wants to remove a word, it will be asked and verified
				cout << endl;
				if(game.removePlayerWord(pos)) // the loop will go on until a valid removal operation occurs
				{
					cout << endl << endl;
					game.game_show();            // then the board is shown after the update
					cout << endl;
					continue;
				}
				else
				{
					continue;
				}
			} if (word ==
					   "?") {            // if the user needs help the "?" call will present hints while available
				if (game.getNumHints() ==
					p1.getDifficulty()) {                // if the user reaches the max number of hints set by the difficulty
					cout << "You reached the limit of hints allowed, no more help now :( "
						 << endl;  // a message will appear and leave this part of the function
					continue;
				} else if (!game.helpPlayerword(
						pos))        // then the help function will be called. if it works will return true, otherwise the loop will go on
					continue;
				else {
					cout << "Word ? ";            //after the user is presented with a new hint a word will be asked
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
			if (word == "X")
				continue;
			else if (!game.addPlayerWord(pos,
									word)) {        //normal addition and the help function converge at this point where the
				cout << endl;                            // user input word will be added if valid
				continue;
			}
			game.game_show();            // after the modification the board will be shown
			cout << endl;
		}while(true);
	cin.clear();			// this clears the cin flag after the eof call by the user
	if(!game.checkBoard())
	{
		cout << "The board was not sucessfully finished. Press X if you would like to leave" << endl;
	} else
	{
		break;
	}
	}while(true);
	cin.clear();
	string dest = getdestination(board);  // this call will get the name of the file where the game data will be saved
	cout << endl << " Congratulations, you won!" <<  endl << " Your data will be saved in the file: " << dest << "." << endl << endl;
	finishplay(game, p1,dest);  // the ending function is now called and the game is over

}

/*******************************************************************************
* ******************************** main ****************************************
* The main function of the Program 2. Is the main menu of the game. The user will
* be presented with the instructions and then the player name will be asked. Then
* he/she gets to choose the difficulty: Easy, Normal or Hard. At this point the
* user will have to give a valid board for him/her to play in.
*/
int main() {
	introduction();		// this is where the introduction is called
	string playername;		// this string will hold the name of the player
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
	string dif;
	cout << "Select a difficulty: Easy(E), Normal(N), Hard(H) ";		// the difficulty is represented by a char
	do {
		cin >> dif;
		UpperInput(dif);
		if (cin.eof())
		{
			cin.clear();
			continue;
		}
		else if (dif == "E" || dif == "N" || dif == "H")			// only if a valid option is entered by the user this step
		    break;												// will be moved on from
		else
        {
            cout << "That is not a possible difficulty. Please enter again: ";
        }
	} while (true);
	Player p1(playername,dif);		// then a new player is created with the attributes needed: name and difficulty
	string board;
	cwplayer game1;					// and new game as well, the board and dictionary will be loaded into this game
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
		else if (!game1.readFile(board)) {		// after the user enters a board name, it will be loaded if valid or this step will be repeated (Board contents)
			cout << "Try again : ";
			continue;
		}
		else {
			game1.getDict(board);		// after the board has been validated the dictionary will be loaded too (Dictionary contents)
			if (!game1.checkFinished()) {		// if the board wasn't finished before, the program won't allow the game to play and ask for another board
				cout << endl << "This board isn't finished, you can't play in it. Write again: " << endl;
				continue; 
			}
			break;
		}
	} while (true);
	game1.startGame();		// after everything's checked out the game is setup
	playgame(game1, p1,board); // and the user plays in it
	cout << endl << "The game is over. Hope you had fun!" << endl;
	getchar();
}