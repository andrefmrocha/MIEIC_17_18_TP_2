//
// Created by andrefmrocha on 04-05-2018.
//
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
	numHints = 0; //The number of hints is initialized as 0
    prepareBoard();
    game_show(); //The board is shown
    cout << "HORIZONTAL";
    spacing(10);
    cout << "VERTICAL" << endl;
    sepWords(); //The words are separated into two groups: horizontal and vertical
    for(int i = 0; i < vertiWord.size() || i < horiWord.size(); i++)
    {
        if(i < horiWord.size())
        {
            string syn = randomsynDict(horiWord[i].first);
            syn = string(horiWord[i].second) + '-' + syn;
            cout << syn;
            spacing(syn.size());
        }
        else
        {
            spacing(0);
        }
        if(i < vertiWord.size())
        {
            cout << vertiWord[i].second << "-";
            cout << randomsynDict(vertiWord[i].first);
        }
        cout << endl;
    }
//Synonyms from both sides are shown to the user side by side
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
    setcolor(RED); // The color is set to red
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
    } //The board is fully written
    setcolor(WHITE, BLACK_B);
}


bool cwplayer::writePlayerWord(string position, string word)
{
    int pos_v = static_cast<int>(position[1]-'a');  //Save both positions as integers
    int pos_h = static_cast<int>(position[0]-'A');
    char direc = position[2];   // The direction is saved as a char
    for(auto i:wordPos)
    {
        if(i.second == position)
        {
            if(i.first.size() != word.size()) //Checks if the word fits the given space
            {
                cout << "Word is unfitting for the given space." << endl;
                return false;
            }
        }
    }
    if(direc == 'V')
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
                    board[pos_h][pos_v] = i; //Writes the actual word
                }
                pos_h++;
            }

    }
    else    //The same process is repeated for an horizontal word
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
    return true;
}


bool cwplayer::checkBoard()
{
    if(userWordPos.size()!= wordPos.size()) //If their size is not the same, it means it hasn't been properly filled
    {
        cout << "Not all spaces are yet filled" << endl;
        return false;
    }
    sort(userWordPos.begin(), userWordPos.end()); //Both vectors are sorted in order to run through them
    sort(wordPos.begin(), wordPos.end());
    bool flag = true;
    for(int i = 0; i < userWordPos.size();i++)
    {
        if(userWordPos[i].first == wordPos[i].first)
        {
            continue;
        }
        else //If a word is not properly filled, that word is shown to the user
        {
            cout << "The word " << userWordPos[i].first << " is not correct" << endl;
            flag = false;
        }
    }
    return flag;
}


bool cwplayer::removePlayerWord(string position)
{
    for(int i = 0; i < userWordPos.size(); i++)
    {
        if(userWordPos[i].second == position)
        {
            removeWord(userWordPos[i].second, userWordPos[i].first.size());
            userWordPos.erase(userWordPos.begin() + i);
            for(auto i: userWordPos)
            {
                writePlayerWord(i.second, i.first);
            }
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
	NumHintsInc(); // Increases the number os hints used
	bool flag = false;
	for (auto i : wordPos) {
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
	string randsyn = randomsynDict(word); //A random synonym is chosen and shown to the user
	cout << "A clue for this word is: " << randsyn << endl;
	return flag;
}


string cwplayer::findPosition(string word) {
	for (auto i : userWordPos) {
		if (i.first == word) {
			return i.second;
		}
	}
	return "1";
}


int cwplayer::getNumHints() {
	return numHints;
}

void cwplayer::NumHintsInc() {
	numHints += 1;
}

bool cwplayer::addPlayerWord(string position, string word)
{
    if(writePlayerWord(position, word))
    {
        userWordPos.push_back(pair<string, string>(word, position));//The word is added to another vector of pairs
        return true;
    }
    else
    {
        return false;
    }
}
