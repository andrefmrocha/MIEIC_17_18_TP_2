//
// Created by joaom on 02-05-2018.
//

#ifdef __unix__
#include "unix_colors.h"
using namespace std;

// Set text color
void setcolor(string color) {
	cout << color;
}
// Set text color & background
void setcolor(string color, string background_color) {
	cout << color << background_color;
}
#else

#include "windows_colors.h"
using namespace std;

	// Set text color
	void setcolor(unsigned int color) {
		HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hcon, color); 
	}
	// Set text color & background
	void setcolor(unsigned int color, unsigned int background_color) { 
		HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
		if (background_color == BLACK)
			SetConsoleTextAttribute(hCon, color); 
		else 
			SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
				BACKGROUND_RED); 
	}
#endif