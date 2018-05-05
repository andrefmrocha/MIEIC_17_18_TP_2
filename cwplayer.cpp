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