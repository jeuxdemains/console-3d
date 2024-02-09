#pragma once
#include <vector>
#include "Scenes/Scene_1.h"
#include "ConsoleRenderer.h"
#include "bassmod.h"


class SceneOrchestrator
{
    std::vector<Scene*> m_Scenes = {};
    ConsoleRenderer* m_Renderer = nullptr;
    int m_CurSceneId = 0;
    void InitMusic();

public:
    static int s_InstrumentVolume;

    SceneOrchestrator(ConsoleRenderer* renderer) 
    {
        m_Renderer = renderer;

        Scene_1* s1 = new Scene_1(m_Renderer);
        s1->StartScene();
        m_Scenes.emplace_back(s1);

        InitMusic();
    };

    ~SceneOrchestrator() {};

    void StartScene()
    {
        m_Scenes[m_CurSceneId]->StartScene();
    };

    void EndScene()
    {
        m_Scenes[m_CurSceneId]->EndScene();
        m_CurSceneId++;
    };

    void Update(double deltaTime)
    {
        m_Scenes[m_CurSceneId]->Update(deltaTime, s_InstrumentVolume);
        s_InstrumentVolume = 0;
    };

    void Render() 
    {
        m_Scenes[m_CurSceneId]->Render();
    };
};

