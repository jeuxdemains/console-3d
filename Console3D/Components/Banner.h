#pragma once
#include <vector>
#include "Component.h"

class Banner : public Component
{
    ConsoleRenderer* m_Renderer;
    double m_X, m_Y;
    char V[8][50], M[8][50], W[8][50], A[8][50], R[8][50], E[8][50];
    double tethaLetter = 0;
    double tetha = 0;

public:
    Banner(ConsoleRenderer* renderer, double x, double y) :
        m_Renderer(renderer), m_X(x), m_Y(y)
    {

        strcpy_s(V[0], "+   + ");
        strcpy_s(V[1], "      ");
        strcpy_s(V[2], "#   # ");
        strcpy_s(V[3], "#   # ");
        strcpy_s(V[4], "# . # ");
        strcpy_s(V[5], " '#'  ");
        strcpy_s(V[6], "      ");
        strcpy_s(V[7], "      ");

        strcpy_s(M[0], "      ");
        strcpy_s(M[1], "      ");
        strcpy_s(M[2], ".#.#. ");
        strcpy_s(M[3], "# # # ");
        strcpy_s(M[4], "# # # ");
        strcpy_s(M[5], "# # # ");
        strcpy_s(M[6], "      ");
        strcpy_s(M[7], "+   + ");

        strcpy_s(W[0], "+   + ");
        strcpy_s(W[1], "      ");
        strcpy_s(W[2], "#   # ");
        strcpy_s(W[3], "# . # ");
        strcpy_s(W[4], "# # # ");
        strcpy_s(W[5], "## ## ");
        strcpy_s(W[6], "      ");
        strcpy_s(W[7], "      ");

        strcpy_s(A[0], "      ");
        strcpy_s(A[1], "      ");
        strcpy_s(A[2], ".#*#. ");
        strcpy_s(A[3], "#   # ");
        strcpy_s(A[4], "##### ");
        strcpy_s(A[5], "#   # ");
        strcpy_s(A[6], "      ");
        strcpy_s(A[7], "+   + ");

        strcpy_s(R[0], "      ");
        strcpy_s(R[1], "      ");
        strcpy_s(R[2], "##*#. ");
        strcpy_s(R[3], "#  .# ");
        strcpy_s(R[4], "###.  ");
        strcpy_s(R[5], "#   # ");
        strcpy_s(R[6], "      ");
        strcpy_s(R[7], "+   + ");

        strcpy_s(E[0], "      ");
        strcpy_s(E[1], "      ");
        strcpy_s(E[2], "#####  +");
        strcpy_s(E[3], "#     ");
        strcpy_s(E[4], "###   ");
        strcpy_s(E[5], "#####  +");
        strcpy_s(E[6], "      ");
        strcpy_s(E[7], "      ");
    }

    void Update()
    {
        m_X += cos(tetha);
       // m_Y += 1 * sin(tetha/4);
        tetha += 0.1;
    }

    void Render()
    {
        DrawLetter(V, 0);
        tethaLetter += 0.1;
        DrawLetter(M, strlen(V[0]));
        tethaLetter += 0.1;
        DrawLetter(W, strlen(M[0]) * 2);
        tethaLetter += 0.1;
        DrawLetter(A, strlen(W[0]) * 3);
        tethaLetter += 0.1;
        DrawLetter(R, strlen(A[0]) * 4);
        tethaLetter += 0.1;
        DrawLetter(E, strlen(R[0]) * 5);
    }

    void DrawLetter(char chr[8][50], int xSpace)
    {
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < strlen(chr[row]); col++)
            {
                double colY = m_Y;
                colY += 5 * sin(12 * tethaLetter);
                m_Renderer->DrawPixel((double)col + m_X + xSpace, (double)row + colY, chr[row][col]);
            }
        }
    }

    ~Banner() {};
};

