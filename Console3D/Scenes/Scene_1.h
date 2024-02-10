#pragma once
#include "Scene.h"
#include "../Components/Banner.h"
#include "../Components/ParticleSystem.h"
#include "../Components/Object3d.h"
#include "../ObjectsFactory.h"
#include "../Components/PrimitiveCircles.h"

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


        Object3d* model = objFac.CreateObject(
            ObjectsFactory::model,
            m_Renderer,
            m_Renderer->cols,
            m_Renderer->rows,
            '%');

        model->m_Enabled = false;

        ParticleSystem* particleSys = new ParticleSystem(
            m_Renderer, m_Renderer->ScreenW() / 2,
            m_Renderer->ScreenH() / 2);


        std::vector<PrimitiveCircles> circles = {};
        for (int i = 0; i < 20; i++)
        {
            double x = 55 - (i * 5);
            double delayedStart = 2 * i;
            PrimitiveCircles* pc = new PrimitiveCircles(m_Renderer, m_Renderer->cols / 2 - x, 20, delayedStart);
            AddComponent(pc);
        }

        Banner* banner = new Banner(m_Renderer, m_Renderer->cols / 2 - 16, 7);

        AddComponent(model);
        AddComponent(cube);
        AddComponent(particleSys);
        AddComponent(banner);
    };

    void Update(double deltaTime, double instVol = 0.0) override
    {
        Scene::Update(deltaTime, instVol);
    }
};

