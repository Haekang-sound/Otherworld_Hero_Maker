#pragma once
#include <d2d1.h>
#include "Vector2.h"

/// <summary>
/// ��ȯ����� ������� Ŭ����
/// </summary>
class MakeMatrix
{
public:

	//functor�� ����� ������
	D2D1_MATRIX_3X2_F operator() (const D2D1_POINT_2F scale, const double rotation, const D2D1_POINT_2F translate)
	{
		D2D1_MATRIX_3X2_F scalematrix = TranslateScale(scale);
		D2D1_MATRIX_3X2_F rotationMatrix = TranslateRotation(rotation);
		D2D1_MATRIX_3X2_F translateMatrix = TranslateMove(translate);

		m_translateMatrix = scalematrix * rotationMatrix * translateMatrix;

		return m_translateMatrix;
	}

	void translate(D2D1_MATRIX_3X2_F matrix, int& x, int& y)
	{
		D2D1_POINT_2F temp = { (float)x,(float)y };
	}

private:
	D2D1_MATRIX_3X2_F m_translateMatrix;
private:
	D2D1_MATRIX_3X2_F TransformMatrix(D2D1_MATRIX_3X2_F& scale, D2D1_MATRIX_3X2_F& rotation, D2D1_MATRIX_3X2_F& translate);

	//��ȯ����� ��ȯ�Ѵ�
	D2D1_MATRIX_3X2_F MakeTransformMatrix(const D2D1_POINT_2F scale, const double rotation, const D2D1_POINT_2F translate);

	//�̵����
	D2D1_MATRIX_3X2_F TranslateMove(const D2D1_POINT_2F translate);
	//ȸ�����
	D2D1_MATRIX_3X2_F TranslateRotation(double angle);
	//ũ�����
	D2D1_MATRIX_3X2_F TranslateScale(const D2D1_POINT_2F scale);
};

