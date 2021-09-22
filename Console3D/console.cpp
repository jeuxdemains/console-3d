#include "console.h"

HANDLE console::curScreenBufferHandle;

void console::Update()
{
    DrawLine(5, 5, m_X, m_Y, '+');

    if (m_X < cols)
        m_X++;
    if (m_Y < rows)
        m_Y++;
}

void console::Clear()
{
    if (screenBufferFlip)
       console::curScreenBufferHandle = hNewScreenBuffer;
    else
        console::curScreenBufferHandle = hNewScreenBuffer2;

    screenBufferFlip = !screenBufferFlip;

    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdout, &csbi);

    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(
        console::curScreenBufferHandle, (TCHAR)' ', dwConSize, { 0,0 }, &cCharsWritten);

    SetConsoleActiveScreenBuffer(console::curScreenBufferHandle);
}

void console::DrawPixel(short x, short y, char pixelChr)
{
    DWORD cCharsWritten;
    FillConsoleOutputCharacter(
        console::curScreenBufferHandle, (TCHAR)pixelChr, 1, { x, y }, &cCharsWritten);
}

void console::SetFontSize(short w, short h)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = w;                  // Width of each character in the font
    cfi.dwFontSize.Y = h;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    lstrcpyW(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hStdout, FALSE, &cfi);
    SetCurrentConsoleFontEx(hNewScreenBuffer, FALSE, &cfi);
    SetCurrentConsoleFontEx(hNewScreenBuffer2, FALSE, &cfi);
    GetConsoleDimensions();
}

void console::SetSize(short w, short h)
{
    COORD coord;
    coord.X = w;
    coord.Y = h;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = w - 1;
    Rect.Right = h - 1;

    SetConsoleWindowInfo(hStdout, TRUE, &Rect);

    if (!SetConsoleScreenBufferSize(hStdout, coord))
        ShowLastSystemError();

    SetConsoleWindowInfo(hNewScreenBuffer, TRUE, &Rect);
    if (!SetConsoleScreenBufferSize(hNewScreenBuffer, coord))
        ShowLastSystemError();

    SetConsoleWindowInfo(hNewScreenBuffer2, TRUE, &Rect);
    if (!SetConsoleScreenBufferSize(hNewScreenBuffer2, coord))
        ShowLastSystemError();

    GetConsoleDimensions();
}

void console::ShowLastSystemError()
{
    LPSTR messageBuffer;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        0,          // source
        GetLastError(),
        0,          // lang
        (LPSTR)&messageBuffer, 0, NULL);

    std::cout << messageBuffer << '\n';
    LocalFree(messageBuffer);
    exit(-1);
}

//a besenham line algo implementation
void console::DrawLine(int x1, int y1, int x2, int y2, char chr)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
    dx = x2 - x1;
    dy = y2 - y1;
    dx1 = fabs(dx);
    dy1 = fabs(dy);
    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;

    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1;
            y = y1;
            xe = x2;
        }
        else
        {
            x = x2;
            y = y2;
            xe = x1;
        }

        DrawPixel(x, y, chr);

        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
            {
                px = px + 2 * dy1;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    y = y + 1;
                }
                else
                {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }

            DrawPixel(x, y, chr);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1;
            y = y1;
            ye = y2;
        }
        else
        {
            x = x2;
            y = y2;
            ye = y1;
        }

        DrawPixel(x, y, chr);

        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
            {
                py = py + 2 * dx1;
            }
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
                {
                    x = x + 1;
                }
                else
                {
                    x = x - 1;
                }
                py = py + 2 * (dx1 - dy1);
            }

            DrawPixel(x, y, chr);
        }
    }
}