//
// Created by joaom on 26-04-2018.
//
#include "stdafx.h"
#include "Board.h"

Board::Board()
{
    lines = 0;
    columns = 0;
    finished = false;
}
Board::Board(unsigned int lines, unsigned int columns) {
    this->lines=lines;
    this->columns=columns;
    vector<char> vec_columns;
     for (int i = 0; i < columns; i++) {
        vec_columns.push_back('.');
    }
    for (int j = 0; j < lines; j++){
        board.push_back(vec_columns);
    }
    finished = false;
}

void Board::resizeBoard(unsigned int lines, unsigned int columns)
{
    this->lines=lines;
    this->columns=columns;
    board.clear();
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
    fillBoard();
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
				setcolor(WHITE, BLACK_B);
				cout << board.at(i).at(j) << "  ";
				setcolor(BLACK, LIGHTGRAY);
			}
            else cout << board.at(i).at(j) << "  ";
        }
        setcolor(BLACK_B, BLACK_B);
        cout << endl;
    }
	setcolor(WHITE, BLACK_B);
    clear();            //After showing it, the board itself is cleared
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
        if((pos_h + word.size()) < lines)
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
        if((pos_v + word.size()) < columns)
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
bool Board::eraseWord(string word)
{
    for (int i = 0; i < wordPos.size(); ++i)
    {
        if(wordPos[i].first == word)
        {
            wordPos.erase(wordPos.begin() + i);
			return true;
        }
    }
	return false;
}

void Board::finishBoard()
{
    for (auto i: wordPos)
    {
        if(i.second[3] == 'F')
        {
            return;
        }
    }
    finished = true;
}

void Board::fillBoard()
{
    writeAllWords();
    if(finished)
    {
        for(auto & i: board)
        {
            for(auto & j: i)
            {
                if(j == '.')
                    j = '#';
            }

        }
    }
}

int Board::countLine(string savingString)
{
    int num = 0;
    for(auto i: savingString)
    {
        if( (i >= 'A' && i <= 'Z') || i == '#' || i == '.')
            num++;
    }
    return num;
}
bool Board::readFile(string iname)
{
    ifstream infile(iname);
    if(!infile.is_open())
    {
        cout << "File not found. " << endl;
        return false;
    }
    string savingString, word, position, extract;
    int lines = 0, columns = 0;
    while (getline(infile, savingString))
    {
        if(savingString.empty()) // Introduzir o que vai estar escrito
        {
            finished = false;
            break;
        }
        if(savingString == " ")
        {
            finished = true;
            break;
        }
    }
    while (getline(infile,savingString))
    {
        if (!savingString.empty())
        {
            lines++;
            if(columns == 0)
            {
                columns = countLine(savingString);
            }
        }
        else
        {
            break;
        }
    }
    while (getline(infile, savingString))
    {
        for(auto i: savingString)
        {
            if(i == ' ')
            {
                word = extract;
                extract.clear();
            }
            else
            {
                extract.push_back(i);
            }

        }
        position = extract;
        extract.clear();
        wordPos.push_back(pair<string, string>(word, position));
    }
    this->columns = columns;
    this->lines = lines;
    resizeBoard(lines, columns);
}

bool Board::positionalCheck(string position)
{
    if(position.size() > 3) //Checks if the position argument was passed correctly
    {
        cout  << endl << "Too many positional arguments." <<endl << endl;
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

}