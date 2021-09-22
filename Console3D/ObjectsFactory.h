#pragma once
#include <memory>
#include "Object3dCube.h"
#include "Object3dModel.h"
#include "console.h"

class ObjectsFactory
{
public:
	enum Type
	{
		cube,
		model
	};

	Object3d* createObject(Type objType, console& con, int scrnW, int scrnH, char chr = '*')
	{
		Object3d* obj;
		switch (objType)
		{
		case ObjectsFactory::cube:
			obj = new Object3dCube(con, scrnW, scrnH, chr);
			break;
		case ObjectsFactory::model:
		default:
			obj = new Object3dModel("model.obj", con, scrnW, scrnH, chr);
			break;
		}

		return obj;
	}
};

