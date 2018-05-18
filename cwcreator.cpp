//
// Created by andrefmrocha on 02-05-2018.
//
#include "cwcreator.h"
using namespace std;

bool cwcreator::helpWord(string position)
{
    if(position.size() != 3) //Checks if the position argument was passed correctly
    {
        cout << endl << "Too many positional arguments." << endl << endl;
        return false;
    }
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   // The direction is saved as a char
    string wildcardWord;
    vector<string> possibleWords;
    fillBoard();
    if(direc == 'V')
    {
        for(pos_h; pos_h < lines; pos_h++)
        {
            if(board[pos_h][pos_v] >= 'A' && board[pos_h][pos_v] <= 'Z')//If a letter was found
            {
                wildcardWord.push_back(board[pos_h][pos_v]); //The letter is saved
                wildcardWords(wildcardWord,possibleWords); //and the word vector is searched once more
            }
            else if(board[pos_h][pos_v] == '#')
            {
                break; //If it's found a '#', the search is over
            }
            else
            {
                wildcardWord.push_back('?'); //If there's a blank space, a '?' is written
                wildcardWords(wildcardWord,possibleWords);
            }
        }
    }
    else //The same process is done horizontally
    {
        for(pos_v; pos_v < columns; pos_v++)
        {
            if(board[pos_h][pos_v] >= 'A' && board[pos_h][pos_v] <= 'Z')
            {
                wildcardWord.push_back(board[pos_h][pos_v]);
                wildcardWords(wildcardWord,possibleWords);
            }
            else if(board[pos_h][pos_v] == '#')
            {
                break;
            }
            else
            {
                wildcardWord.push_back('?');
                wildcardWords(wildcardWord,possibleWords);
            }
        }
    }
    if(!possibleWords.empty())
    {
        int i = 1;
        char choice;
		bool flag = true;
        do
        {   do
            {
                if(possibleWords.size() == 0)
                {
                    cout << "There are no more options." << endl;
                    return true;
                }
                srand(time(NULL)+i);
                unsigned long index = rand() % possibleWords.size();
                cout << i << "-" << possibleWords[index] << endl;
                possibleWords.erase(possibleWords.begin()+index);
                i++; //Synonyms are randomyl chosen and removed in order to prevent repetitiveness
            }while (i % 10);
			cout << endl << "Would you like more options? (Y/N)"; //The user is asked if he wants more words
			do {
				cin >> choice;
				if (cin.eof()) {
					cin.clear();
					continue;
				}
				if (choice == 'Y' || choice == 'y' )
				{
					break;
				}
				if (choice == 'N' || choice == 'n')
				{
					flag = false;
					break;
				}
				cout << endl << "Not a valid option. Please choose again(Y/N)";
			} while (true); //If the option is not valid, the user is asked again
        }while(flag);
        return true;
    } else
    {
        cout << "There are no options available for this position" << endl;
        return false;
    }
}

bool cwcreator::wildcardMatch(const char *str, const char *strWild)
{
    // We have a special case where string is empty ("") and the mask is "*".
    // We need to handle this too. So we can't test on !*str here.
    // The loop breaks when the match string is exhausted.
    while (*strWild)
    {
        // Single wildcard character
        if (*strWild== '?')
        {
            // Matches any character except empty string
            if (!*str)
                return false;
            // OK next
            ++str;
            ++strWild;
        }
        else if (*strWild== '*')
        {
            // Need to do some tricks.
            // 1. The wildcard * is ignored.
            // So just an empty string matches. This is done by recursion.
            // Because we eat one character from the match string,
            // the recursion will stop.
            if (wildcardMatch(str,strWild+1))
                // we have a match and the * replaces no other character
                return true;
            // 2. Chance we eat the next character and try it again,
            // with a wildcard * match. This is done by recursion.
            // Because we eat one character from the string,
            // the recursion will stop.
            if (*str && wildcardMatch(str+1,strWild))
                return true;
            // Nothing worked with this wildcard.
            return false;
        }
        else
        {
            // Standard compare of 2 chars. Note that *str might be 0 here,
            // but then we never get a match on *strWild
            // that has always a value while inside this loop.
            if (toupper(*str++)!=toupper(*strWild++))
                return false;
        }
    }
    // Have a match? Only if both are at the end...
    return !*str && !*strWild;
}

void cwcreator::wildcardWords(string word, vector<string> &possiblewords)
{
    for(auto i: synonymDict)
    {
        if(wildcardMatch(i.first.c_str(), word.c_str()))
        {
            possiblewords.push_back(i.first);
        }
    }
}





bool cwcreator::addWord(string position, string word)    // Adds the word to the board, returns false if it can't
{
    if(isWordinDict(word))
    {
       position.push_back('T'); //If the word is in the dictionary, a 'T is added to the positional string
    }
    else
    {
        position.push_back('F'); //If the word is not in the dictionary, a 'F is added to the positional string
    }
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   // The direction is saved as a char
    fillBoard();    //Writes the words in the board in order to analyze if the new word was given a valid position
    if(direc == 'V')
    {
        if((pos_h + word.size()) > lines )  //In case there isn't enough space on the board, the word is ignored
        {
            cout << endl << "Not enough space" << endl << endl;
            clear();
            return false;
        }
        else
        {
            for(auto i: word)
            {
                if(board[pos_h][pos_v] != '.' && board[pos_h][pos_v] != i)    //If any of positions of the board are
                {                                                           // taken with letters different from the word
                    cout  << endl << "Word unfitting for this position" << endl << endl;     // it is ignored
                    clear();
                    return false;
                }
                pos_h++;
            }
        }
    }
    else    //The same process is repeated for an horizontal word
    {
        if((pos_v + word.size()) > columns)
        {
            cout << endl << "Not enough space." << endl << endl;
            clear();
            return false;
        }
        else
        {
            for(auto i: word)
            {
                if(board[pos_h][pos_v] != '.' && board[pos_h][pos_v]!= i)
                {
                    cout << endl << "Word unfitting for this position" << endl<< endl;
                    clear();
                    return false;
                }
                pos_v++;
            }
        }
    }
    wordPos.push_back(pair<string, string>(word, position)); //If everything checks out, the word is saved in the vector of pairs
    clear();    //The words are removed from the board once again
    return true; //A true boolean is passed on, in order for it to know the word was stored
}

string cwcreator::getDictName() {
	return dictName;
}


string cwcreator::getBoardName() {
	string boardattr = giveBoardName(); // if the boards has been created already and is being loaded
	if (!(boardattr == ""))				// this part of the code will verify it
		return boardattr;
	string b000_009 = "b00";			// these strings are to be used according to the number of the board that is being created
	string b010_099 = "b0";
	string b100_999 = "b";
	string ext = ".txt";
	string cvti;
	string filename;
	bool flag = false;
	for (int i = 1; i < 10; i++) {				// these loops while try to open files with the format
		cvti = to_string(i);					// the first checks from 001 to 009
		filename = b000_009 + cvti + ext;		// if they open, it means they already exist so the number must be incremented
		ifstream checkfile(filename);			// to prevent overwriting
		if (checkfile.is_open())
			continue;
		else
			flag = true;
		break;
	}
	if (!flag) {								// this loop will check files from 010 to 099
		for (int i = 10; i < 100; i++) {
			cvti = to_string(i);
			filename = b010_099 + cvti + ext;
			ifstream checkfile(filename);
			if (checkfile.is_open())
				continue;
			else
				flag = true;
			break;
		}
	}
	if (!flag) {									// this loop will check files from 100 to 999
		for (int i = 100; i < 1000; i++) {
			cvti = to_string(i);
			filename = b100_999 + cvti + ext;
			ifstream checkfile(filename);
			if (checkfile.is_open())
				continue;
			else
				flag = true;
			break;
		}
	}
	if (flag) {						// after the available board is found, the name will be set as boardname
		setBoardname(filename);
		return filename;
	}
	else { // if all 1000 boards are already created, then no other is going to be created
		cout << "A new board cannot be created, please select an already created puzzle." << endl;
		return "error";
	}
}


void cwcreator::board_save()
{
	fillBoard(); // The board is prepared to be written
	string boardname = getBoardName(); // The name is chosen
	if (boardname == "error")
		return;
	ofstream outfile(boardname); //The file is opened
	outfile << dictName << endl; //The name of the dictionary is stored
	if (finished)
	{
		outfile << static_cast<char>(32) << endl; //If the board is finished a space is placed on the second line
	}
	else
	{
		outfile << endl;
	}
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			outfile << board.at(i).at(j) << "  ";
		}
		outfile << endl; //The board is written on the file
	}
	outfile << endl;
	for (int i2 = 0; i2 < wordPos.size(); i2++) {
		outfile << wordPos.at(i2).second.substr(0,3) << " " << wordPos.at(i2).first << endl;
	} //The words are written on the file
	clear(); //The actual board is cleared
	if (checkFinished())
		cout << endl << "Finished! " << endl;
	else cout << endl << "The board was saved, but not finished. " << endl;
}


void cwcreator::checkWords()
{
    for(auto i: wordPos)
    {
        if(isWordinDict(i.first))
            i.second.push_back('T');
        else
            i.second.push_back('F');
    }
}
