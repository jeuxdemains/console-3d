#pragma once
#include "Object3d.h"

class Object3dModel : public Object3d
{
public:
	Object3dModel(std::string fName, console con, int scrnW, int scrnH, char chr)
	{
		Object3dAdd(LoadModel(fName), con, scrnW, scrnH, chr);
	};

	~Object3dModel() {};

	Vector3d::Mesh LoadModel(std::string fileName) override
	{
		Vector3d::Mesh mesh;
		mesh.LoadFromObjFile(fileName);

		return mesh;
	}
};

