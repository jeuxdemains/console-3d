#pragma once
#include <time.h>
#include <string>
#include "../Vector3d.h"
#include "../Matrix.h"
#include "Component.h"

static float incRX, incRY, incRZ;

class Object3d : public Component
{
	float fRotationX_ = 0.0f, fRotationY_ = 0.0f, fRotationZ_ = 0.0f;
	std::vector<Vector3d::Mesh> objects_;
	int m_ScrnW = 0, m_ScrnH = 0;
	bool isFirst_ = false;
	Matrix* matrix = nullptr;
	ConsoleRenderer* m_Renderer = nullptr;
	char m_Char = 0;

	static const int vertCount = 7;
	Vector3d::Triangle
		projectedTri[vertCount],
		rotX[vertCount],
		rotY[vertCount],
		rotZ[vertCount],
		transX[vertCount],
		scale[vertCount];

	int numVerticesToClear = 0;

public:
	Object3d() {};
	Object3d(int scrnW, int scrnH) : m_ScrnW(scrnW), m_ScrnH(scrnH) {};

	void Object3dAdd(Vector3d::Mesh obj, ConsoleRenderer *renderer, int sW, int sH, char chr)
	{
		m_ScrnW = sW;
		m_ScrnH = sH;
		matrix = new Matrix((float)m_ScrnW, (float)m_ScrnH);
		m_Renderer = renderer;

		incRX = incRY = incRZ += 0.003f;
		fRotationX_ = incRX;
		fRotationY_ = incRY;
		fRotationZ_ = incRZ;
		m_Char = chr;

		objects_.push_back(obj);
	};

	//back-face culling
	bool IsFrontFace(Vector3d::Triangle& tri)
	{
		//make lines from vertices b->a & c->a
		Vector3d::Vector3 line1, line2;
		line1.x = tri.b.x - tri.a.x;
		line1.y = tri.b.y - tri.a.y;
		line1.z = tri.b.z - tri.a.z;

		line2.x = tri.c.x - tri.a.x;
		line2.y = tri.c.y - tri.a.y;
		line2.z = tri.c.z - tri.a.z;

		Vector3d* v3d = new Vector3d();
		Vector3d::Vector3 cross = v3d->Cross(line1, line2);
		Vector3d::Vector3 normal, cam;

		normal = v3d->Normalize(cross);
		cam.x = tri.a.x - 0.0f;
		cam.y = tri.a.y - 0.0f;
		cam.z = tri.a.z - 0.0f;

		float dot = v3d->Dot(normal, cam);
		delete v3d;

		if (dot < 0.0f)
			return true;

		return false;
	}

	void FillPolygon(Vector3d::Triangle& tri)
	{
		int x, y, dx, dy;
		x = tri.a.x + tri.b.x + tri.c.x;
		x /= 3;
		y = tri.a.y + tri.b.y + tri.c.y;
		y /= 3;

		m_Renderer->DrawPixel(x, y, m_Char);
	}

	int Min(int a, int b)
	{
		return (a > b) ? a : b;
	}

	virtual ~Object3d();
	virtual Vector3d::Mesh LoadModel(std::string fName) = 0;
	virtual void Update();
	virtual void Render();
};

