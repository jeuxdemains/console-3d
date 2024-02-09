#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>
#include <vector>

class ConsoleRenderer
{
    HWND hWin = 0;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout = 0;
    COORD coordBufSize = {};
    COORD coordBufCoord = {};
    SMALL_RECT srctWriteRect = {};
    bool screenBufferFlip = false;
    unsigned char* m_ScreenBufferData;

    void GetConsoleDimensions()
    {
        GetConsoleScreenBufferInfo(hStdout, &csbi);
        cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    void ShowLastSystemError();
public:
    ConsoleRenderer() {};
    ~ConsoleRenderer() {};

    void Init(short screenWCols, short screenHRows);
    void Shutdown();
    void DrawLine(int x0, int y0, int x1, int y1, char chr = '*');
    void DrawPixel(unsigned int x, unsigned int y, char pixelChr = '*');
    void Clear();
    void SetFontSize(short w, short h);
    void SetSize(short w, short h);
    unsigned int ScreenW() { return cols; }
    unsigned int ScreenH() { return rows; }
    unsigned int cols = 0, rows = 0;

};

