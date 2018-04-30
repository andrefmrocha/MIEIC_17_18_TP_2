//
// Created by joaom on 26-04-2018.
//

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

void Board::board_show()
{
    writeAllWords();
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            cout << board.at(i).at(j) << "  ";
        }
        cout << endl;
    }
    clear();
}

bool Board::addWord(string position, string word)    // Adds the word to the board, returns false if it can't
{
    if(position.size() > 3)
    {
        cout << "Too many positional arguments." << endl;
        return false;
    }
    int pos_v = static_cast<int>(position[1]-'a');  //save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];
    if(pos_h > lines || pos_v > columns || (direc != 'V' && direc !='H'))
    {
        cout << "Wrong Position" << endl;
        return false;
    }
    writeAllWords();
    if(direc == 'V')
    {
        if((pos_h + word.size()) > lines )
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
                if(board[hori][pos_v] != '.' && board[hori][pos_v] != i)
                {
                    cout << "Word unfitting for this position" << endl;
                    clear();
                    return false;
                }
                hori++;
            }
        }
    }
    else
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
    wordPos.push_back(pair<string, string>(word, position));
    clear();
    return true;
}

void Board::writeWord(string position, string word)
{
    int pos_v = static_cast<int>(position[1]-'a');  //save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];
    if(direc == 'V')
    {
        for (auto i: word)
        {
            board[pos_h][pos_v] = i;
            pos_h++;
        }
    }
    else
    {
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