//
// Created by joaom on 02-05-2018.
//

#ifndef PROJETO_2_WINDOWS_COLORS_H
#define PROJETO_2_WINDOWS_COLORS_H
#include <iostream> 
#include <ctime> 
#include <cstdlib>
#include <windows.h>
using namespace std;
//COLOR CODES: 
#define BLACK 0
#define BLACK_B 0
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4
#define MAGENTA 5 
#define BROWN 6
#define LIGHTGRAY 7 
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11 
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

void gotoxy(int x, int y);
void setcolor(unsigned int color);
void setcolor(unsigned int color, unsigned int background_color);

#endif //PROJETO_2_WINDOWS_COLORS_H
