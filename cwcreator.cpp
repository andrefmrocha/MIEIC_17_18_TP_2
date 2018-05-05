//
// Created by andrefmrocha on 02-05-2018.
//
//#include "stdafx.h"
#include "cwcreator.h"
/*cwcreator::cwcreator()
{
    Dictionary();
    Board();
}*/
bool cwcreator::helpWord(string position)
{
    if(position.size() > 3) //Checks if the position argument was passed correctly
    {
        cout << endl << "Too many positional arguments." << endl << endl;
        return false;
    }
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   // The direction is saved as a char
    if(pos_h > lines || pos_v > columns || (direc != 'V' && direc !='H'))   //Checks if all the arguments are valid for the given board
    {
        cout << endl << "Wrong Position" << endl << endl;
        return false;
    }
    string wildcardWord;
    vector<string> possibleWords;
    writeAllWords();
    if(direc == 'V')
    {
        for(pos_h; pos_h < lines; pos_h++)
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
    else
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
        cout << endl << "Lista de palavras possíveis: " << endl << endl;
        for(int i = 0; i < possibleWords.size(); ++i)
        {
            cout << i+1 << " - " << possibleWords[i] << endl;
        }
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

void cwcreator::board_save(string filename) {
	ofstream outfile(filename);
	outfile << "THIS IS GOING TO DISPLAY THE DICTIONARY FILENAME" << endl << endl;
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			outfile << board.at(i).at(j) << "  ";
		}
		outfile << endl;
	}
	outfile << endl;
	for (int i2 = 0; i2 < wordPos.size(); i2++) {
		outfile << wordPos.at(i2).first << " " << wordPos.at(i2).second << endl;
	}
	clear();
}


/*************************************************************
 * ******************** addWord ******************************
 * addWord method has the purpose of checking if a word is valid for the given position by the user
 * A word is never added to the board itself, it is stored on our vector of pairs where we only store the word and the string
 * related to its position
 * @param position
 * @param word
 * @return true if word
 * is valid for the selected position
 **************************************************************/
bool cwcreator::addWord(string position, string word)    // Adds the word to the board, returns false if it can't
{
    if(position.size() > 3) //Checks if the position argument was passed correctly
    {
        cout  << endl << "Too many positional arguments." <<endl << endl;
        return false;
    }

    if(!isWordinDict(word))
    {
        cout << endl << "Word is not in the dictionary." << endl << endl;
        return false;
    }
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   // The direction is saved as a char
    if(pos_h > lines || pos_v > columns || (direc != 'V' && direc !='H'))   //Checks if all the arguments are valid for the given board
    {
        cout << endl << "Wrong Position" << endl << endl;
        return false;
    }
    writeAllWords();    //Writes the words in the board in order to analyze if the new word was given a valid position
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
