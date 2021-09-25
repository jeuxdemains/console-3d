#include "Object3dCube.h"

Vector3d::Mesh Object3dCube::LoadModel(std::string fName /* not used */)
{
	float fLow = -0.5f;
	float fHigh = 0.5f;

	Vector3d::Triangle tri1 =
	{
		fLow, fLow, fLow,
		fLow, fHigh, fLow,
		fHigh, fHigh, fLow
	};

	Vector3d::Triangle tri2 =
	{
		fLow, fLow, fLow,
		fHigh, fHigh, fLow,
		fHigh, fLow, fLow
	};

	Vector3d::Triangle tri3 =
	{
		fHigh, fLow, fLow,
		fHigh, fHigh, fLow,
		fHigh, fHigh, fHigh
	};

	Vector3d::Triangle tri4 =
	{
		fHigh, fLow, fLow,
		fHigh, fHigh, fHigh,
		fHigh, fLow, fHigh
	};

	Vector3d::Triangle tri5 =
	{
		fHigh, fLow, fHigh,
		fHigh, fHigh, fHigh,
		fLow, fHigh, fHigh
	};

	Vector3d::Triangle tri6 =
	{
		fHigh, fLow, fHigh,
		fLow, fHigh, fHigh,
		fLow, fLow, fHigh
	};

	Vector3d::Triangle tri7 =
	{
		fLow, fLow, fHigh,
		fLow, fHigh, fHigh,
		fLow, fHigh, fLow
	};

	Vector3d::Triangle tri8 =
	{
		fLow, fLow, fHigh,
		fLow, fHigh, fLow,
		fLow, fLow, fLow
	};

	Vector3d::Triangle tri9 =
	{
		fLow, fHigh, fLow,
		fLow, fHigh, fHigh,
		fHigh, fHigh, fHigh
	};

	Vector3d::Triangle tri10 =
	{
		fLow, fHigh, fLow,
		fHigh, fHigh, fHigh,
		fHigh, fHigh, fLow
	};

	Vector3d::Triangle tri11 =
	{
		fHigh, fLow, fHigh,
		fLow, fLow, fHigh,
		fLow, fLow, fLow
	};

	Vector3d::Triangle tri12 =
	{
		fHigh, fLow, fHigh,
		fLow, fLow, fLow,
		fHigh, fLow, fLow
	};

	Vector3d::Mesh obj, obj2;
	obj.triangles.push_back(tri1);
	obj.triangles.push_back(tri2);
	obj.triangles.push_back(tri3);
	obj.triangles.push_back(tri4);
	obj.triangles.push_back(tri5);
	obj.triangles.push_back(tri6);
	obj.triangles.push_back(tri7);
	obj.triangles.push_back(tri8);
	obj.triangles.push_back(tri9);
	obj.triangles.push_back(tri10);
	obj.triangles.push_back(tri11);
	obj.triangles.push_back(tri12);

	return obj;
}