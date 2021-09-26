#pragma once
#include <vector>
#include "../ConsoleRenderer.h"
#include "../Components/Component.h"

class Scene
{
protected:
    std::vector<Component*> m_Components;
    ConsoleRenderer* m_Renderer;

public:
    Scene() {};
    ~Scene() {};

    virtual void StartScene() {};

    virtual void EndScene() 
    {
        for (auto& comp : m_Components)
        {
            delete comp;
            comp = 0;
        }
    };

    void AddComponent(Component* comp)
    {
        m_Components.emplace_back(comp);
    }

    virtual void Update()
    {
        for (auto& comp : m_Components)
            comp->Update();
    };

    virtual void Render()
    {
        m_Renderer->Clear();

        for (auto& comp : m_Components)
            comp->Render();
    };
};

