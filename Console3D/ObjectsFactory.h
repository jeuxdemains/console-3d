#pragma once
#include <memory>
#include "Components/Object3dCube.h"
#include "Components/Object3dModel.h"
#include "ConsoleRenderer.h"

class ObjectsFactory
{
public:
	enum Type
	{
		cube,
		tetrahedron,
		globe,
		model
	};

	Object3d* CreateObject(Type objType, ConsoleRenderer* renderer, int scrnW, int scrnH, char chr = '*')
	{
		Object3d* obj;

		switch (objType)
		{
		case ObjectsFactory::cube:
			obj = new Object3dCube(renderer, scrnW, scrnH, chr);
			obj->SetName("cube");
			break;
		case ObjectsFactory::tetrahedron:
			obj = new Object3dModel("tetrahedron.obj", renderer, scrnW, scrnH, chr);
			obj->SetName("tetrahedron");
			break;
		case ObjectsFactory::globe:
			obj = new Object3dModel("globe.obj", renderer, scrnW, scrnH, chr);
			obj->SetName("globe");
			break;
		case ObjectsFactory::model:
		default:
			obj = new Object3dModel("globe.obj", renderer, scrnW, scrnH, chr);
			obj->SetName("model");
			break;
		}

		return obj;
	}
};

