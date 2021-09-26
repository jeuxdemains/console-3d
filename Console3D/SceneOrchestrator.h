#pragma once
#include <vector>
#include "Scenes/Scene_1.h"
#include "ConsoleRenderer.h"

class SceneOrchestrator
{
    std::vector<Scene> m_Scenes;
    ConsoleRenderer* m_Renderer;
    int m_CurSceneId = 0;

public:
    SceneOrchestrator(ConsoleRenderer* renderer) 
    {
        m_Renderer = renderer;
        Scene_1 s1(m_Renderer);
        s1.StartScene();
        m_Scenes.emplace_back(s1);
    };

    ~SceneOrchestrator() {};

    void StartScene()
    {
        m_Scenes[m_CurSceneId].StartScene();
    };

    void EndScene()
    {
        m_Scenes[m_CurSceneId].EndScene();
        m_CurSceneId++;
    };

    void Update()
    {
        m_Scenes[m_CurSceneId].Update();
    };

    void Render() 
    {
        m_Scenes[m_CurSceneId].Render();
    };
};

