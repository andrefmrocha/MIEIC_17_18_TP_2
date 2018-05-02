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
        if(pos_h != 0)
        {
            if(board[pos_h-1][pos_v] =='.')
                board[pos_h-1][pos_v] = '#';
        }
        if((pos_h + word.size()) <= lines)
        {
            if(board[pos_h+(word.size())][pos_v] == '.')
                board[pos_h+(word.size())][pos_v] = '#';
        }
        for (auto i: word)
        {
            board[pos_h][pos_v] = i;
            pos_h++;
        }
    }
    else
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
void Board::helpWord(string position)
{
    int pos_v = static_cast<int>(position[1]-'a');  //save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2]; 
}

bool Board::wildcardMatch(const char *str, const char *strWild)
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