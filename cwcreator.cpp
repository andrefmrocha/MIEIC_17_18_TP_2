//
// Created by andrefmrocha on 02-05-2018.
//

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
    string wildcardWord;
    vector<string> possibleWords;
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
        cout << "Lista de palavras possíveis: " << endl;
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
    for(auto i: synonymDic)
    {
        if(wildcardMatch(i.first.c_str(), word.c_str()))
        {
            possiblewords.push_back(i.first);
        }
    }
}