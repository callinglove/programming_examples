#include <cstdio>
#include <iostream>

using namespace std;

#ifndef _MSC_VER	/************* LINUX下实现 *************/

typedef enum
{
	cRED = 31,
	cBLUE = 34,
	cGREEN = 32,
	cWHITE = 37,
	cYELLOW = 33
} CONSOLE_COLOR;

void SetConsoleTextColor(CONSOLE_COLOR color)
{
	printf("\e[%dm", (int)(color));
}

#else				/************ WINDOWS下实现 ************/

#include <conio.h>
#include <windows.h>

typedef enum
{
	cRED = FOREGROUND_RED,
	cBLUE = FOREGROUND_BLUE,
	cGREEN = FOREGROUND_GREEN,
	cYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	cWHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN
} CONSOLE_COLOR;

void SetConsoleTextColor(CONSOLE_COLOR color)
{
	static HANDLE console = NULL;

	if (console == NULL) console = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(console, color);
}

#endif

int main(int argc, char** argv)
{
	SetConsoleTextColor(cRED);
	puts("hello xungen");

	SetConsoleTextColor(cBLUE);
	puts("hello xungen");

	SetConsoleTextColor(cGREEN);
	puts("hello xungen");

	SetConsoleTextColor(cYELLOW);
	puts("hello xungen");
	
	return 0;
}