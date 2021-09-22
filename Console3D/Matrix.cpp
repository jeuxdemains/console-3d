#include "Matrix.h"

void Matrix::mulVectorByMatrix(
	const Vector3d::Vector3& vertices,
	Vector3d::Vector3& rotatedVert,
	const Matrix::Matrix4& multiplicator)
{
	float elements[3];
	for (int i = 0; i < 3; i++)
	{
		elements[i] =
			vertices.x * multiplicator.matrix[0][i] +
			vertices.y * multiplicator.matrix[1][i] +
			vertices.z * multiplicator.matrix[2][i] +
			multiplicator.matrix[3][i];
	}

	rotatedVert.x = elements[0];
	rotatedVert.y = elements[1];
	rotatedVert.z = elements[2];

	float w =
		vertices.x * multiplicator.matrix[0][3] +
		vertices.y * multiplicator.matrix[1][3] +
		vertices.z * multiplicator.matrix[2][3] +
		multiplicator.matrix[3][3];

	if (w != 0.0f)
	{
		rotatedVert.x /= w;
		rotatedVert.y /= w;
		rotatedVert.z /= w;
	}
}

void Matrix::mulTriangleByMatrix(
	const Vector3d::Triangle& triangle,
	Vector3d::Triangle& destTriangle,
	const Matrix::Matrix4& matrix)
{
	mulVectorByMatrix(triangle.a, destTriangle.a, matrix);
	mulVectorByMatrix(triangle.b, destTriangle.b, matrix);
	mulVectorByMatrix(triangle.c, destTriangle.c, matrix);
}

Matrix::Matrix4 Matrix::setScaleMatrix(float x, float y, float z)
{
	Matrix4 transMat =
	{
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return transMat;
}

Matrix::Matrix4 Matrix::setTranslateMatrix(float x, float y, float z)
{
	Matrix4 transMat =
	{
		1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return transMat;
}

Matrix::Matrix4 Matrix::getRotationMatrix(float rotationAngle, int axis) const
{
	Matrix::Matrix4 rotMatrix;

	switch (axis)
	{
	case 0: //x
		rotMatrix =
		{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosf(rotationAngle), sinf(rotationAngle), 0.0f,
			0.0f, -sinf(rotationAngle), cosf(rotationAngle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		break;
	case 1: //y
		rotMatrix =
		{
			cosf(rotationAngle), 0.0f, sinf(rotationAngle), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-sinf(rotationAngle), 0.0f, cosf(rotationAngle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		break;
	default: //z
		rotMatrix =
		{
			cosf(rotationAngle), sinf(rotationAngle), 0.0f, 0.0f,
			-sinf(rotationAngle), cosf(rotationAngle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
		break;
	}

	return rotMatrix;
}