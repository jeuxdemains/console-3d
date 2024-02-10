#pragma once
#include <vector>
#include "Component.h"

class PrimitiveCircles : public Component
{
    ConsoleRenderer* m_Renderer;
    double m_X, m_Y;
    char C[8][50];
    double tethaLetter = 0.1;
    double tetha = 0;
    double thetay = 0;
public:
    static double lastDeltaTime;
    double m_DelayedStart = 0;

    PrimitiveCircles(ConsoleRenderer* renderer, double x, double y, double delayStart = 0) :
        m_Renderer(renderer), m_X(x), m_Y(y), m_DelayedStart(delayStart)
    {

        //strcpy_s(C[0], "      |     ");
        //strcpy_s(C[1], "#**--   --**#");
        //strcpy_s(C[2], "");
        //strcpy_s(C[3], "");
        //strcpy_s(C[4], "#**--   --**#");
        //strcpy_s(C[5], "      |");
        //strcpy_s(C[6], "");
        //strcpy_s(C[7], "");

        strcpy_s(C[0], "");
        strcpy_s(C[1], " ###########");
        strcpy_s(C[2], "##         ##");
        strcpy_s(C[3], "#           #");
        strcpy_s(C[4], "##         ##");
        strcpy_s(C[5], " ###########");
        strcpy_s(C[6], "");
        strcpy_s(C[7], "");

    }

    void Update(double deltaTime, double instVol = 0.0)
    {
        if (m_DelayedStart > 0)
        {
            m_DelayedStart -= deltaTime;
            return;
        }

        lastDeltaTime = deltaTime;
        m_X += 2 * cos(tetha) * deltaTime;
        m_Y += 0.3 * sin(thetay) * deltaTime;
        tetha += 0.1 * deltaTime;
        thetay += 0.005 * deltaTime;
    }

    void Render()
    {
        double inc = 0.03 * lastDeltaTime;

        DrawLetter(C, 0);
        tethaLetter += inc;
        //DrawLetter(M, strlen(V[0]));
        //tethaLetter += inc;
        //DrawLetter(W, strlen(M[0]) * 2);
        //tethaLetter += inc;
        //DrawLetter(A, strlen(W[0]) * 3);
        //tethaLetter += inc;
        //DrawLetter(R, strlen(A[0]) * 4);
        //tethaLetter += inc;
        //DrawLetter(E, strlen(R[0]) * 5);
    }

    void DrawLetter(char chr[8][50], int xSpace)
    {
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < strlen(chr[row]); col++)
            {
                double x = (double)col + m_X + xSpace;

                double colY = 15 + (10 * sin(m_Y));
                double y = (double)row + colY;
                m_Renderer->DrawPixel(x, y, chr[row][col]);
            }
        }
    }

    ~PrimitiveCircles() {};
};

