//
// Created by joaom on 26-04-2018.
//
#include "Board.h"
using namespace std;
Board::Board()
{
    lines = 0;
    columns = 0;
    finished = false;
}

Board::Board(unsigned int lines, unsigned int columns) {
    this->lines=lines; //Updates lines
    this->columns=columns; //Updates columns
    vector<char> vec_columns;
     for (int i = 0; i < columns; i++) {
        vec_columns.push_back('.');
    }
    for (int j = 0; j < lines; j++){ // Creates the vector of char vectors
        board.push_back(vec_columns);
    }
    finished = false;
	boardname = ""; //The name of the board is saved as an empty string
}


void Board::resizeBoard(unsigned int lines, unsigned int columns)
{
    this->lines=lines; //Updates lines
    this->columns=columns; //Updates columns
    board.clear();
    vector<char> cenas;
    for (int i = 0; i < columns; i++) {
        cenas.push_back('.');
    }
    for (int j = 0; j < lines; j++){
        board.push_back(cenas);
    } // Creates the new vector
}


void Board::board_show()    //All the words are written in their positions in order to show it to the user
{
    fillBoard(); //Prepares the board to be shown
    setcolor(RED); //Sets the color of the words to red
	cout << "  ";
	for (int i2 = 0; i2 < columns; i2++) {
		cout << (char)(i2 + 97) << "  ";
	} //Writes the first line of letters as a means of detailing vertical coordinates
	cout << endl;
    for (int i = 0; i < lines; i++) {
		setcolor(RED);
		cout << (char)(i + 65) << " "; //Writes all the columns of letters for horizontal coordinates
		for (int j = 0; j < columns; j++) {
			setcolor(BLACK, LIGHTGRAY);
			if (board.at(i).at(j) == '#') {
				setcolor(WHITE, BLACK_B);
				cout << board.at(i).at(j) << "  ";
				setcolor(BLACK, LIGHTGRAY);
			}
            else cout << board.at(i).at(j) << "  ";
        } //shows the whole board
        setcolor(BLACK_B, BLACK_B);
        cout << endl;
    }
	setcolor(WHITE, BLACK_B);
    clear();            //After showing it, the board itself is cleared
}


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

void Board::writeAllWords()
{
    for(auto i: wordPos)
    {
        writeWord(i.second, i.first);
    }
}

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

bool Board::eraseWord(string position)
{
    for (int i = 0; i < wordPos.size(); ++i)
    {
        if(wordPos[i].second.substr(0,3) == position)
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
        if(i.second[3] == 'F') //Searches for the 'F' character
        {
            return;
        }
    }
    finished = true; //Updates finished if all words are valid
}

void Board::fillBoard()
{
    writeAllWords();
    if(finished) //If the board is finished it is filled with '#'
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


int Board::countColumn(string savingString)
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
    ifstream infile(iname); //Opens the file
    if(!infile.is_open()) //Checks if file was opened
    {
        cout << "File not found. " << endl;
        return false;
    }
    string savingString, word, position, extract;
    int lines = 0, columns = 0;
    while (getline(infile, savingString)) //Extracts if the board is finished
    {
        if(savingString.empty()) //Nothing written on the second line, so the board isn't finished
        {
            finished = false;
            break;
        }
        if(savingString == " ") //If there is a space on the second line, the board is finished
        {
            finished = true;
            break;
        }
    }
    while (getline(infile,savingString)) //Second iteration will search for information on the board
    {
        if (!savingString.empty())
        {
            lines++; //Counts the number of lines on the board
            if(columns == 0)
            {
                columns = countColumn(savingString);  //Counts the number of columns in a board
            }
        }
        else
        {
            break;  //When the string is empty, the next iteration comes forward
        }
    }
    while (getline(infile, savingString)) //The third iteration will search for information on the words
    {
        for(auto i: savingString)
        {
            if(i == ' ')
            {
                position = extract; //When a space is found, the position of the word is found
                extract.clear();
            }
            else
            {
                extract.push_back(i);
            }

        }
        word = extract;
        extract.clear();
        wordPos.push_back(pair<string, string>(word, position)); //Saves the word to our vector of pairs
    }
    this->columns = columns;
    this->lines = lines;
    resizeBoard(lines, columns);
	boardname = iname; //Updates all the information regarding the board
	return true;
}

bool Board::positionalCheck(string position)
{
    if(position.size() != 3) //Checks if the position argument was passed correctly
    {
        cout  << endl << "Invalid number of positional arguments." <<endl << endl;
        return false;
    }
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   // The direction is saved as a char
    if(pos_h > lines || pos_v > columns || (direc != 'V' && direc !='H'))   //Checks if all the arguments are valid for the given board
    {
        cout << endl << "Wrong Position." << endl << endl;
        return false;
    }
    if(board[pos_h][pos_v] == '#')
    {
        cout << "Invalid position." << endl << endl;
        return false;
    }
    return true;
}

void Board::setBoardname(string bname) {
	boardname = bname;
}


string Board::giveBoardName() {
	return boardname;
}


bool Board::checkFinished()
{
    return finished;
}