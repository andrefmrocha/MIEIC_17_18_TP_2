//
// Created by joaom on 26-04-2018.
//
#include "stdafx.h"
#include "Board.h"


Board::Board(unsigned int lines, unsigned int columns) {
    this->lines=lines;
    this->columns=columns;
    vector<char> cenas;
     for (int i = 0; i < columns; i++) {
        cenas.push_back('.');
    }
    for (int j = 0; j < lines; j++){
        board.push_back(cenas);
    }
}

void Board::board_show()    //All the words are written in their positions in order to show it to the user
{
    writeAllWords();
    setcolor(RED);
	cout << "  ";
	for (int i2 = 0; i2 < columns; i2++) {
		cout << (char)(i2 + 97) << "  ";
	}
	cout << endl;
    for (int i = 0; i < lines; i++) {
		setcolor(RED);
		cout << (char)(i + 65) << " ";
		for (int j = 0; j < columns; j++) {
			setcolor(BLACK, LIGHTGRAY);
			if (board.at(i).at(j) == '#') {
				setcolor(WHITE, BLACK);
				cout << board.at(i).at(j) << "  ";
				setcolor(BLACK, LIGHTGRAY);
			}
            else cout << board.at(i).at(j) << "  ";
        }
		setcolor(WHITE, BLACK);
        cout << endl;
    }
	setcolor(WHITE, BLACK);
    clear();            //After showing it, the board itself is cleared
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
bool Board::addWord(string position, string word)    // Adds the word to the board, returns false if it can't
{
    if(position.size() > 3) //Checks if the position argument was passed correctly
    {
        cout << "Too many positional arguments." << endl;
        return false;
    }
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   // The direction is saved as a char
    if(pos_h > lines || pos_v > columns || (direc != 'V' && direc !='H'))   //Checks if all the arguments are valid for the given board
    {
        cout << "Wrong Position" << endl;
        return false;
    }
    writeAllWords();    //Writes the words in the board in order to analyze if the new word was given a valid position
    if(direc == 'V')
    {
        if((pos_h + word.size()) > lines )  //In case there isn't enough space on the board, the word is ignored
        {
            cout << "Not enough space" << endl;
            clear();
            return false;
        }
        else
        {
            int hori = pos_h;
            for(auto i: word)
            {
                if(board[hori][pos_v] != '.' && board[hori][pos_v] != i)    //If any of positions of the board are
                {                                                           // taken with letters different from the word
                    cout << "Word unfitting for this position" << endl;     // it is ignored
                    clear();
                    return false;
                }
                hori++;
            }
        }
    }
    else    //The same process is repeated for an horizontal word
    {
        if((pos_v + word.size()) > columns)
        {
            cout << "Not enough space." << endl;
            clear();
            return false;
        }
        else
        {
            int verti = pos_v;
            for(auto i: word)
            {
                if(board[pos_h][verti] != '.' && board[pos_h][verti]!= i)
                {
                    cout << "Word unfitting for this position" << endl;
                    clear();
                    return false;
                }
                verti++;
            }
        }
    }
    wordPos.push_back(pair<string, string>(word, position)); //If everything checks out, the word is saved in the vector of pairs
    clear();    //The words are removed from the board once again
    return true; //A true boolean is passed on, in order for it to know the word was stored
}
/***************************************************************************
 * *************************** writeWord ***********************************
 * writeWord method is used to actually write a Word a word in the board
 * Various methods require a filled board to analyze and make several decisions
 * @param position
 * @param word
 */
void Board::writeWord(string position, string word)
{
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   //Saves the direction as a char
    if(direc == 'V')
    {
        if(pos_h != 0)
        {
            if(board[pos_h-1][pos_v] =='.')
                board[pos_h-1][pos_v] = '#';    //Checks if there's space before the word to write a '#'
        }
        if((pos_h + word.size()) <= lines)
        {
            if(board[pos_h+(word.size())][pos_v] == '.')
                board[pos_h+(word.size())][pos_v] = '#';    //Checks if there's space after the word to write a '#
        }
        for (auto i: word)
        {
            board[pos_h][pos_v] = i;        //Writes the actual word
            pos_h++;
        }
    }
    else    //Repeats the process for an horizontal word
    {
        if(pos_v != 0)
        {
            if(board[pos_h][pos_v-1] == '.')
                board[pos_h][pos_v-1] = '#';
        }
        if((pos_h + word.size()) <= columns)
        {
            if(board[pos_h][pos_v+(word.size())] =='.')
                board[pos_h][pos_v+(word.size())] = '#';
        }
        for (auto i: word)
        {
            board[pos_h][pos_v] = i;
            pos_v++;
        }
    }
}
/*********************************************************
 ********************* writeAllWords *********************
 * writeAllWords method is used to run the vector of pairs
 * and indicate to writeWord, the parameters for it to
 * write.
 */
void Board::writeAllWords()
{
    for(auto i: wordPos)
    {
        writeWord(i.second, i.first);
    }
}
/*************************************************************
 *************************** clear ***************************
 * The clear method is used to clean the board after analyzing
 * it. Our board has a standard to be left clean after each
 * operation.
 */
void Board::clear()
{
    for (auto& i: board)
    {
        for(int i2 = 0; i2 < i.size(); i2++)
        {
            i[i2] = '.';
        }
    }
}
/*************************************************************
 *************************** eraseWord************************
 * The eraseWord method gives the possibility to the user to
 * delete a selected word from vector of pairs.
 * @param word
 */
void Board::eraseWord(string word)
{
    for (int i = 0; i < wordPos.size(); ++i)
    {
        if(wordPos[i].first == word)
        {
            wordPos.erase(wordPos.begin() + i);
        }
    }
}
