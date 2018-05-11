//
// Created by andrefmrocha on 04-05-2018.
//
#include "stdafx.h"
#include "cwplayer.h"
void cwplayer::prepareBoard()
{
    fillBoard();
    for(auto& i: board)
    {
        for(auto& j: i)
        {
            if(j >= 'A' && j <= 'Z')
            {
                j = '.';
            }
        }
    }
}

void cwplayer::startGame()
{
    prepareBoard();
    game_show();
    cout << "HORIZONTAL";
    spacing(10);
    cout << "VERTICAL" << endl;
    sepWords();
    for(int i = 0; i < vertiWord.size() || i < horiWord.size(); i++)
    {
        if(i < horiWord.size())
        {
            string syn = randomsynDict(horiWord[i].first);
            cout << syn;
            spacing(syn.size());
        }
        else
        {
            spacing(0);
        }
        if(i < vertiWord.size())
        {
            cout << randomsynDict(vertiWord[i].first);
        }
        cout << endl;
    }

}

void cwplayer::spacing(int word)
{
    for(int i = 0; i < (50 - word); i++)
    {
        cout << " ";
    }
}

void cwplayer::sepWords()
{
    for(auto i: wordPos)
    {
        if(i.second[2] == 'V')
        {
            vertiWord.push_back(i);
        }
        else
        {
            horiWord.push_back(i);
        }
    }
}

void cwplayer::game_show()
{
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
}

bool cwplayer::addPlayerWord(string position, string word)
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
                else
                {
                    board[pos_h][pos_v] = i;
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
                else
                {
                    board[pos_h][pos_v] = i;
                }
                pos_v++;
            }
        }
    }
    userWordPos.push_back(pair<string, string>(word, position));
}

bool cwplayer::checkBoard()
{
    sort(userWordPos.begin(), userWordPos.end());
    sort(wordPos.begin(), wordPos.end());
    return userWordPos==wordPos;
}

bool cwplayer::removePlayerWord(string word)
{
    for(int i = 0; i < userWordPos.size(); i++)
    {
        if(userWordPos[i].first == word)
        {
            removeWord(userWordPos[i].second, word.size());
            userWordPos.erase(userWordPos.begin() + i);
            return true;
        }
    }
    return false;
}

void cwplayer::removeWord(string position, int size)
{
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   //Saves the direction as a char
    if(direc == 'V')
    {
        for(int i = 0; i < size; i ++)
        {
            board[pos_h + i][pos_v] = '.';
        }
    }
    else
    {
        for(int i = 0; i < size; i ++)
        {
            board[pos_h][pos_v+i] = '.';
        }
    }
}

bool cwplayer::helpPlayerword(string position) {
	string word;
	bool flag = false;
	for (auto i : userWordPos) {
		if (i.second == position) {
			word = i.first;
			flag = true;
			break;
		}
	}
	if (!flag) {
		cout << "The word was not found." << endl;
		return flag;
	}
	string randsyn = randomsynDict(word);
	cout << "A clue for this word is: " << randsyn; // falta lidar com casos onde nao ha sinonimo
	return flag;
}