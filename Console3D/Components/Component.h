#pragma once
#include "../ConsoleRenderer.h"

class Component
{
protected:
    std::string m_Name = "";

public:
    bool m_Enabled = true;

    virtual void Update(double deltaTime, double instVol = 0.0) = 0;
    virtual void Render() = 0;
    virtual std::string Name() { return m_Name; }
};
