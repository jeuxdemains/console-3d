#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>

class console
{
    HWND hWin;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hStdout, hNewScreenBuffer, hNewScreenBuffer2;
    static HANDLE curScreenBufferHandle;
    int m_X, m_Y = 0;
    COORD coordBufSize;
    COORD coordBufCoord;
    SMALL_RECT srctWriteRect;
    bool screenBufferFlip = false;

    void GetConsoleDimensions()
    {
        GetConsoleScreenBufferInfo(hStdout, &csbi);
        GetConsoleScreenBufferInfo(hNewScreenBuffer, &csbi);
        GetConsoleScreenBufferInfo(hNewScreenBuffer2, &csbi);
        cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    void ShowLastSystemError();
public:
    console() 
    {
        hWin = GetConsoleWindow();
        hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

        hNewScreenBuffer = CreateConsoleScreenBuffer(
            GENERIC_WRITE,
            0,
            NULL,                    // default security attributes 
            CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
            NULL);                   // reserved; must be NULL 

        hNewScreenBuffer2 = CreateConsoleScreenBuffer(
            GENERIC_WRITE,
            0,
            NULL,                    // default security attributes 
            CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
            NULL);                   // reserved; must be NULL 

        GetConsoleDimensions();

    };

    ~console() {};

    void DrawLine(int x0, int y0, int x1, int y1, char chr = '*');
    void DrawPixel(short x, short y, char pixelChr = '*');
    void Update();
    void Clear();
    void SetFontSize(short w, short h);
    void SetSize(short w, short h);

    int cols, rows;

};

