#pragma once
#include <math.h>
#include "Vector3d.h"

class Matrix
{
	const float fNear_ = 0.1f;
	const float fFar_ = 1000.f;
	const float fFov_ = 60.0f;
	const float fFovRad_ = 1.0f / (tanf(fFov_ * 0.5f / 180.0f * 3.14169f));
	float width_, height_, fAspect_;

public:
	Matrix(const float width, const float height) :
		width_(width),
		height_(height),
		fAspect_((float)width / (float)height)
	{
		projectionMatrix_ =
		{
			fAspect_ * fFovRad_,0.0f,0.0f,0.0f,
			0.0f,fFovRad_,0.0f,0.0f,
			0.0f,0.0f,fFar_ / (fFar_ - fNear_),1.0f,
			0.0f,0.0f,(-fFar_ * fNear_) / (fFar_ - fNear_),0.0f
		};
	};

	struct Matrix4
	{
		float matrix[4][4];
	};

	struct Axis
	{
		enum Element { x, y, z };
	};

	Matrix4 projectionMatrix_;

	void mulVectorByMatrix(
		const Vector3d::Vector3& vertices,
		Vector3d::Vector3& rotatedVert,
		const Matrix::Matrix4& multiplicator);

	void mulTriangleByMatrix(
		const Vector3d::Triangle& triangle,
		Vector3d::Triangle& destTriangle,
		const Matrix::Matrix4& matrix);

	Matrix4 getRotationMatrix(float rotationAngle, int axis) const;
	Matrix4 setScaleMatrix(float x, float y, float z);
	Matrix4 setTranslateMatrix(float x, float y, float z);
};