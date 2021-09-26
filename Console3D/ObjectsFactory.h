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
		model
	};

	Object3d* createObject(Type objType, ConsoleRenderer* renderer, int scrnW, int scrnH, char chr = '*')
	{
		Object3d* obj;
		switch (objType)
		{
		case ObjectsFactory::cube:
			obj = new Object3dCube(renderer, scrnW, scrnH, chr);
			break;
		case ObjectsFactory::model:
		default:
			obj = new Object3dModel("model.obj", renderer, scrnW, scrnH, chr);
			break;
		}

		return obj;
	}
};

