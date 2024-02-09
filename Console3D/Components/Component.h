#pragma once
#include "../ConsoleRenderer.h"

class Component
{
protected:
    std::string m_Name = "";

public:
    virtual void Update(double deltaTime, double instVol = 0.0) = 0;
    virtual void Render() = 0;
};
