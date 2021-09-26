#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>
#include <vector>

class ConsoleRenderer
{
    HWND hWin;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout;
    int m_X, m_Y = 0;
    COORD coordBufSize;
    COORD coordBufCoord;
    SMALL_RECT srctWriteRect;
    bool screenBufferFlip = false;
    char* m_ScreenBufferData;

    void GetConsoleDimensions()
    {
        GetConsoleScreenBufferInfo(hStdout, &csbi);
        cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    void ShowLastSystemError();
public:
    ConsoleRenderer() {};
    ~ConsoleRenderer() 
    {
        delete[] m_ScreenBufferData;
    };

    void Init();
    void DrawLine(int x0, int y0, int x1, int y1, char chr = '*');
    void DrawPixel(short x, short y, char pixelChr = '*');
    void Clear();
    void SetFontSize(short w, short h);
    void SetSize(short w, short h);
    int ScreenW() { return cols; }
    int ScreenH() { return rows; }
    int cols, rows;

};

