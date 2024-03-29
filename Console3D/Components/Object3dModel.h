#pragma once
#include "Object3d.h"

class Object3dModel : public Object3d
{
public:
	Object3dModel() {};
	Object3dModel(std::string fName, ConsoleRenderer* renderer, int scrnW, int scrnH, char chr)
	{
		Object3dAdd(LoadModel(fName), renderer, scrnW, scrnH, chr);
	};

	~Object3dModel() {};

	Vector3d::Mesh* LoadModel(std::string fileName) override
	{
		Vector3d::Mesh* mesh = new Vector3d::Mesh();
		mesh->LoadFromObjFile(fileName);

		return mesh;
	}
};

