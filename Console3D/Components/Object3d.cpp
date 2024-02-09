#include "Object3d.h"

Object3d::~Object3d()
{
	delete m_Matrix;
}

void Object3d::Update(double deltaTime, double instVol)
{
	fRotationX_ += 1.0f * 0.04f * deltaTime;
	fRotationY_ += 1.0f * 0.08f * deltaTime;
	fRotationZ_ += 1.0f * 0.12f * deltaTime;
	
	if (instVol > 0 && fReactionAmp <= 2)
	{
		fReactionAmp += instVol/80;
		if (fReactionAmp > 3)
			fReactionAmp = 3;
	}
	else
	{
		fReactionAmp -= 0.2 * deltaTime;
		if (fReactionAmp < 1.0)
			fReactionAmp = 1;
	}
}

void Object3d::Render()
{
	Matrix::Matrix4 const matRotX =
		m_Matrix->getRotationMatrix(fRotationX_, Matrix::Axis::x);
	Matrix::Matrix4 const matRotY =
		m_Matrix->getRotationMatrix(fRotationY_, Matrix::Axis::y);
	Matrix::Matrix4 const matRotZ =
		m_Matrix->getRotationMatrix(fRotationZ_, Matrix::Axis::z);
	Matrix::Matrix4 const scaleMat = 
		m_Matrix->setScaleMatrix(1.0f, 1.0f, 1.0f);
	Matrix::Matrix4 const transMat =
		m_Matrix->setTranslateMatrix(0.0f, 0.0f, 0.0f + fReactionAmp / 1.9);

	int i = 0;
	double cosfRotX2 = cosf(fRotationX_ * 2);
	double cosfRotX1_5 = cosf(fRotationX_ * 1.5);

	for (const auto& triangle : objects_[0]->triangles)
	{
		scale[i] = triangle;
		m_Matrix->mulTriangleByMatrix(triangle, scale[i], scaleMat);
		rotZ[i] = scale[i];
		m_Matrix->mulTriangleByMatrix(scale[i], rotZ[i], matRotZ);
		rotY[i] = rotZ[i];
		m_Matrix->mulTriangleByMatrix(rotZ[i], rotY[i], matRotY);
		rotX[i] = rotY[i];
		m_Matrix->mulTriangleByMatrix(rotY[i], rotX[i], matRotX);
		transX[i] = rotX[i];
		m_Matrix->mulTriangleByMatrix(rotX[i], transX[i], transMat);

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
			m_Matrix->mulTriangleByMatrix(transX[i], projectedTri[i], m_Matrix->projectionMatrix_);
			i++;
		}
	}

	i--;
	
	//set m_Char render character here

	for (; i >= 0; i--)
	{
		projectedTri[i].a.x += 1.0f;
		projectedTri[i].a.y += 1.0f;
		projectedTri[i].b.x += 1.0f;
		projectedTri[i].b.y += 1.0f;
		projectedTri[i].c.x += 1.0f;
		projectedTri[i].c.y += 1.0f;

		projectedTri[i].a.x *= 0.5f * (double)m_ScrnW;
		projectedTri[i].a.y *= 0.5f * (double)m_ScrnH;
		projectedTri[i].b.x *= 0.5f * (double)m_ScrnW;
		projectedTri[i].b.y *= 0.5f * (double)m_ScrnH;
		projectedTri[i].c.x *= 0.5f * (double)m_ScrnW;
		projectedTri[i].c.y *= 0.5f * (double)m_ScrnH;

		FillPolygon(projectedTri[i]);

		m_Renderer->DrawLine(
			projectedTri[i].a.x, projectedTri[i].a.y,
			projectedTri[i].b.x, projectedTri[i].b.y,
			m_Char);

		m_Renderer->DrawLine(
			projectedTri[i].b.x, projectedTri[i].b.y,
			projectedTri[i].c.x, projectedTri[i].c.y,
			m_Char);

		m_Renderer->DrawLine(
			projectedTri[i].c.x, projectedTri[i].c.y,
			projectedTri[i].a.x, projectedTri[i].a.y,
			m_Char);
	}

}