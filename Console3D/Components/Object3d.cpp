#include "Object3d.h"

Object3d::~Object3d()
{
	delete matrix;
}

void Object3d::Update()
{
	fRotationX_ += 1.0f * 0.04f;
	fRotationY_ += 1.0f * 0.08f;
	fRotationZ_ += 1.0f * 0.12f;

	Render();
}

void Object3d::Clear()
{
	for (int i = numVerticesToClear; i >= 0; i--)
	{
		m_Renderer.DrawLine(
			projectedTri[i].a.x, projectedTri[i].a.y,
			projectedTri[i].b.x, projectedTri[i].b.y,
			' ');

		m_Renderer.DrawLine(
			projectedTri[i].b.x, projectedTri[i].b.y,
			projectedTri[i].c.x, projectedTri[i].c.y,
			' ');

		m_Renderer.DrawLine(
			projectedTri[i].c.x, projectedTri[i].c.y,
			projectedTri[i].a.x, projectedTri[i].a.y,
			' ');
	}
	
}

void Object3d::Render()
{
	Matrix::Matrix4 const matRotX =
		matrix->getRotationMatrix(fRotationX_, Matrix::Axis::x);
	Matrix::Matrix4 const matRotY =
		matrix->getRotationMatrix(fRotationY_, Matrix::Axis::y);
	Matrix::Matrix4 const matRotZ =
		matrix->getRotationMatrix(fRotationZ_, Matrix::Axis::z);
	Matrix::Matrix4 const scaleMat = 
		matrix->setScaleMatrix(1.0f, 1.0f, 1.0f);
	Matrix::Matrix4 const transMat =
		matrix->setTranslateMatrix(0.0f, 0.0f, 0.0f);

	int i = 0;
	float cosfRotX2 = cosf(fRotationX_ * 2);
	float cosfRotX1_5 = cosf(fRotationX_ * 1.5);

	for (auto triangle : objects_[0].triangles)
	{
		scale[i] = triangle;
		matrix->mulTriangleByMatrix(triangle, scale[i], scaleMat);
		rotZ[i] = scale[i];
		matrix->mulTriangleByMatrix(scale[i], rotZ[i], matRotZ);
		rotY[i] = rotZ[i];
		matrix->mulTriangleByMatrix(rotZ[i], rotY[i], matRotY);
		rotX[i] = rotY[i];
		matrix->mulTriangleByMatrix(rotY[i], rotX[i], matRotX);
		transX[i] = rotX[i];
		matrix->mulTriangleByMatrix(rotX[i], transX[i], transMat);

		transX[i].a.z += 14.0f;
		transX[i].b.z += 14.0f;
		transX[i].c.z += 14.0f;

		transX[i].a.x += 2.5f * cosfRotX2;
		transX[i].b.x += 2.5f * cosfRotX2;
		transX[i].c.x += 2.5f * cosfRotX2;

		transX[i].a.y += 3.5f * cosfRotX2;
		transX[i].b.y += 3.5f * cosfRotX2;
		transX[i].c.y += 3.5f * cosfRotX2;

		transX[i].a.z -= 6.5f * cosfRotX1_5;
		transX[i].b.z -= 6.5f * cosfRotX1_5;
		transX[i].c.z -= 6.5f * cosfRotX1_5;

		if (IsFrontFace(transX[i]))
		{
			projectedTri[i] = transX[i];
			matrix->mulTriangleByMatrix(transX[i], projectedTri[i], matrix->projectionMatrix_);
			i++;
		}
	}

	i--;
	numVerticesToClear = i;
	
	//set m_Char render character here

	for (; i >= 0; i--)
	{
		projectedTri[i].a.x += 1.0f;
		projectedTri[i].a.y += 1.0f;
		projectedTri[i].b.x += 1.0f;
		projectedTri[i].b.y += 1.0f;
		projectedTri[i].c.x += 1.0f;
		projectedTri[i].c.y += 1.0f;

		projectedTri[i].a.x *= 0.5f * (float)m_ScrnW;
		projectedTri[i].a.y *= 0.5f * (float)m_ScrnH;
		projectedTri[i].b.x *= 0.5f * (float)m_ScrnW;
		projectedTri[i].b.y *= 0.5f * (float)m_ScrnH;
		projectedTri[i].c.x *= 0.5f * (float)m_ScrnW;
		projectedTri[i].c.y *= 0.5f * (float)m_ScrnH;

		FillPolygon(projectedTri[i]);

		m_Renderer.DrawLine(
			projectedTri[i].a.x, projectedTri[i].a.y,
			projectedTri[i].b.x, projectedTri[i].b.y,
			m_Char);

		m_Renderer.DrawLine(
			projectedTri[i].b.x, projectedTri[i].b.y,
			projectedTri[i].c.x, projectedTri[i].c.y,
			m_Char);

		m_Renderer.DrawLine(
			projectedTri[i].c.x, projectedTri[i].c.y,
			projectedTri[i].a.x, projectedTri[i].a.y,
			m_Char);
	}

}