#pragma once
#include "Object3d.h"

class Object3dCube : public Object3d
{
public:
	Object3dCube(ConsoleRenderer *renderer, int scrnW, int scrnH, uint8_t alpha)
	{
		Object3dAdd(LoadModel("cube"), renderer, scrnW, scrnH, alpha);
	};
	~Object3dCube() {};
	Vector3d::Mesh LoadModel(std::string fName) override;
};

