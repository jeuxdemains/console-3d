#include <iostream>
#include <vector>

#include "ConsoleRenderer.h"
#include "SceneOrchestrator.h"

const int SCRN_W = 200;
const int SCRN_H = 120;

void main()
{
    ConsoleRenderer* renderer = new ConsoleRenderer();
    renderer->Init();
    /*renderer.SetFontSize(15, 30);
    std::cout << "   jeux/TRSI\n";
    Sleep(1000);
    std::cout << "   PRESENTS\n";
    Sleep(1000);
    std::cout << "3D donsole demo\n";
    Sleep(1000);
    std::cout << " from scratch\n";
    Sleep(3000);

    for (int i = 0; i < 20; i++)
    {
        renderer.SetFontSize(15+i*2, 30+i*2);
        Sleep(100);
    }*/


    renderer->SetSize(SCRN_W, SCRN_H);
    renderer->SetFontSize(7, 8);

    SceneOrchestrator orchestrator(renderer);

    while (1)
    {
        orchestrator.Update();
        orchestrator.Render();

        Sleep(1 / 60.0f * 1000.0f);
    }
}