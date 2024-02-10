#include <iostream>
#include <vector>
#include "ConsoleRenderer.h"
#include "SceneOrchestrator.h"

const int SCRN_W = 200;
const int SCRN_H = 120;


void main()
{
    ConsoleRenderer* renderer = new ConsoleRenderer();
    renderer->Init(SCRN_W, SCRN_H);

    renderer->SetFontSize(10, 20);
    std::cout << "      jeux/TRSI\n";
    Sleep(500);
    std::cout << "      PRESENTS\n";
    Sleep(500);
    std::cout << "VMware 3D donsole demo\n";
    Sleep(500);
    std::cout << "    from scratch\n";
    Sleep(2000);

    for (int i = 0; i < 10; i++)
    {
        renderer->SetFontSize(15+i*2, 30+i*2);
        Sleep(100);
    }


    renderer->SetFontSize(6, 7);

    SceneOrchestrator* orchestrator = new SceneOrchestrator(renderer);
    double deltaTime = 0;

    double fps = 30.0f;
    double fpsCap = (1.0 / fps * 1000.0f);

    while (1)
    {
        double startTick = GetTickCount();

        orchestrator->Update(deltaTime);
        orchestrator->Render();

        deltaTime = ((double)GetTickCount() - (double)startTick) / fpsCap;

        //Sleep(1 / 60.0f * 1000.0f);
    }

    renderer->Shutdown();
}