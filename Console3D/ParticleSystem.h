#pragma once
#include "console.h"
#include <vector>
#include <time.h>
#include <ctime>
#include <cstdlib>

class Particle
{
    char m_InitialChar = '*';
    char m_Char;
    int m_LifeTime = 0;
    int m_InitLifetime = 0;
    double 
        forceX = 0.0, 
        forceY = 0.0;

    double tetha = 0.0;
    double increment = 0.0;
    double m_InitX, m_InitY;

public:
    Particle(int x, int y, char chr, int lifeTime) : 
        m_InitX(x), m_InitY(y), m_InitialChar(chr), m_InitLifetime(lifeTime)
    {
        Reset();
    }

    void Reset(double x = 0, double y = 0)
    {
        if (x == 0 && y == 0)
        {
            m_X = m_InitX;
            m_Y = m_InitY;
        }
        else
        {
            m_X = x;
            m_Y = y;
        }
        
        tetha = 0.0;
        m_LifeTime = m_InitLifetime;
        m_Char = m_InitialChar;
        isDead = false;

        SetForceX(RandomDbl(-1.0, 1.0));
        SetForceY(RandomDbl(0.5, 1.0));
        SetIncrement(RandomDbl(-0.2, 0.2));
    }

    void Update()
    {
        m_X += forceX * cos(tetha);
        m_Y += forceY * sin(tetha);

        tetha += increment;
        m_LifeTime--;

        if (m_LifeTime < m_InitLifetime / 1.5)
            m_Char = 'X';

        if (m_LifeTime < m_InitLifetime / 3)
            m_Char = '-';

        if (m_LifeTime <= 0)
            isDead = true;
    };

    void SetIncrement(double inc)
    {
        increment = inc;
    }

    void SetForceX(double x)
    {
        forceX = x;
    };

    void SetForceY(double y)
    {
        forceY = y;
    };

    double RandomDbl(double min, double max)
    {
        double f = (double)rand() / RAND_MAX;
        return min + f * (max - min);
    };

    char Chr() { return m_Char; };
    double m_X, m_Y;
    bool isDead = false;


    ~Particle() {};
};

class ParticleSystem
{
    console m_Con;
    const int NUM_PARTICLES = 300;
    const int PARTICLE_LIFETIME = 80;
    std::vector<Particle*> m_Particles = {};
    double m_ScrnX, m_ScrnY;
    double tetha = 0;

public:
    ParticleSystem(console con, double x, double y) : m_Con(con), m_ScrnX(x), m_ScrnY(y)
    {
        for (int i = 0; i < NUM_PARTICLES; i++)
        {
            int lifeTime = (int)RandomDbl(PARTICLE_LIFETIME / 2, PARTICLE_LIFETIME);
            Particle* p = new Particle(m_ScrnX, m_ScrnY, '.', lifeTime);
            m_Particles.emplace_back(p);
        }
    };

    double RandomDbl(double min, double max)
    {
        double f = (double)rand() / RAND_MAX;
        return min + f * (max - min);
    };

    void Update()
    {
        std::vector<Particle*> m_Dead;

        for (auto& particle : m_Particles)
        {
            particle->Update();
            if (particle->isDead)
                particle->Reset(m_ScrnX, m_ScrnY);
        }

        m_ScrnX += 3 * cos(tetha);
        m_ScrnY += 0.5 * sin(tetha);
        tetha += 0.04;
    }

    void Render()
    {
        for (auto& particle : m_Particles)
            m_Con.DrawPixel(particle->m_X, particle->m_Y, particle->Chr());
    }

    ~ParticleSystem() 
    {
        for (auto& p : m_Particles)
            delete p;

        m_Particles.clear();
    };
};

