//
// Created by joaom on 02-05-2018.
//

#include "unix_colors.h"
// Position the cursor at column 'x', line 'y'
// The coodinates of upper left corner of the screen are (x,y)=(0,0)
void gotoxy(int x, int y) {
    ostringstream oss;
    oss << "\033[" << y << ";" << x << "H";
    cout << oss.str(); }
// Clear the screen
void clrscr(void) {
    cout << "\033[2J";
    gotoxy(0, 0);
}
// Set text color
void setcolor(string color) {
    cout << color;
}
// Set text color & background
void setcolor(string color, string background_color) {
    cout << color << background_color;
}