#pragma once
#include "Scene.h"
#include "../Components/Banner.h"
#include "../Components/ParticleSystem.h"
#include "../Components/Object3dCube.h"
#include "../ObjectsFactory.h"

class Scene_1 : public Scene
{
    
public:
    Scene_1(ConsoleRenderer *renderer)
    {
        m_Renderer = renderer;
    };

    ~Scene_1() {};

    void StartScene()
    {
        ObjectsFactory objFac;
        Object3d* obj = objFac.createObject(
            ObjectsFactory::cube, 
            m_Renderer, 
            m_Renderer->cols, 
            m_Renderer->rows, 
            '#');

        ParticleSystem* particleSys = new ParticleSystem(
            m_Renderer, m_Renderer->ScreenW() / 2,
            m_Renderer->ScreenH() / 2);

        Banner* banner = new Banner(m_Renderer, m_Renderer->cols / 2 - 16, 7);

        AddComponent(obj);
        AddComponent(particleSys);
        AddComponent(banner);
    };
};

