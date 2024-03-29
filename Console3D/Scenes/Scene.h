#pragma once
#include <vector>
#include "../ConsoleRenderer.h"
#include "../Components/Component.h"
#include "../Components/Object3d.h"

class Scene
{
protected:
    std::vector<Component*> m_Components = {};
    ConsoleRenderer* m_Renderer = nullptr;

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

    void RemoveComponent(std::string name)
    {
        for (int i = 0; i < m_Components.size(); i++)
        {
            if (((Object3d*)m_Components[i])->Name() == name)
            {
                m_Components.erase(m_Components.begin() + i);
                break;
            }
        }
    }

    virtual void Update(double deltaTime, double instVol = 0.0)
    {
        static double timer = 0;

        timer += deltaTime;
        if (timer >= 300)
        {
            timer = 0;

            for (auto& comp : m_Components)
            {
                if (comp->Name() == "cube" || comp->Name() == "model")
                {
                    comp->m_Enabled = !comp->m_Enabled;
                }
            }
        }

        for (auto& comp : m_Components)
        {

            if (!comp->m_Enabled)
                continue;

            comp->Update(deltaTime, instVol);
        }
    };

    virtual void Render()
    {
        m_Renderer->Clear();

        for (auto& comp : m_Components)
        {
            if (comp->m_Enabled != true)
                continue;

            comp->Render();
        }
    };
};

