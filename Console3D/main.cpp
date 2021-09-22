#include <iostream>
#include <vector>
#include "Object3d.h"
#include "ObjectsFactory.h"
#include "console.h"
#include "ParticleSystem.h"
#include "Banner.h"

void main()
{
    console* con = new console();
    con->SetSize(200, 120);
    con->SetFontSize(5, 7);

   /* std::vector<Object3d*> objects = {};
    ObjectsFactory objFactory;
    
    objects.emplace_back(
        objFactory.createObject(ObjectsFactory::model, *con, con->cols, con->rows, '#')
    );*/
        
    ObjectsFactory objFac;
    Object3d &obj = *objFac.createObject(ObjectsFactory::cube, *con, con->cols, con->rows, '#');
    ParticleSystem particleSys(*con, 100, 60);
    Banner banner(*con, con->cols/2 - 16, 7);

    while (1)
    {
        con->Clear();

        obj.Update();
        obj.Render();

        particleSys.Update();
        particleSys.Render();

        banner.Update();
        banner.Render();

        Sleep(1 / 60.0f * 1000.0f);
    }

    delete con;
}