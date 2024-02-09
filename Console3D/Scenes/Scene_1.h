#pragma once
#include "Scene.h"
#include "../Components/Banner.h"
#include "../Components/ParticleSystem.h"
#include "../Components/Object3d.h"
#include "../ObjectsFactory.h"

class Scene_1 : public Scene
{
public:
    Scene_1(ConsoleRenderer *renderer)
    {
        m_Renderer = renderer;
    };

    ~Scene_1() {};

    void StartScene() override
    {
        ObjectsFactory objFac;

        Object3d* cube = objFac.CreateObject(
            ObjectsFactory::cube,
            m_Renderer,
            m_Renderer->cols,
            m_Renderer->rows,
            '#');

        ParticleSystem* particleSys = new ParticleSystem(
            m_Renderer, m_Renderer->ScreenW() / 2,
            m_Renderer->ScreenH() / 2);

        Banner* banner = new Banner(m_Renderer, m_Renderer->cols / 2 - 16, 7);

        AddComponent(cube);
        AddComponent(particleSys);
        AddComponent(banner);
    };

    void Update(double deltaTime, double instVol = 0.0) override
    {
        Scene::Update(deltaTime, instVol);
    }
};

