#include "MakeMatrix.h"

#define _USE_MATH_DEFINES
#include <cmath>

/// <summary>
/// �̵����
/// </summary>
/// <param name="speedX">X�̵���</param>
/// <param name="speedY">Y�̵���</param>
/// <returns></returns>
D2D1_MATRIX_3X2_F MakeMatrix::TranslateMove(const D2D1_POINT_2F translate)
{
	D2D1_MATRIX_3X2_F move;

	move.m11 = 1;		move.m12 = 0;
	move.m21 = 0;		move.m22 = 1;
	move.dx = (float)translate.x;	move.dy = (float)translate.y;

	return move;
}

/// <summary>
/// ȸ�����
/// </summary>
/// <param name="angle">ȸ������</param>
/// <returns></returns>
D2D1_MATRIX_3X2_F MakeMatrix::TranslateRotation(double angle)
{
	D2D1_MATRIX_3X2_F rotationMatrix;
	rotationMatrix.m11 = (float)cos(angle * M_PI / 180);	rotationMatrix.m12 = (float)sin(angle * M_PI / 180);
	rotationMatrix.m21 = (float)-sin(angle * M_PI / 180);	rotationMatrix.m22 = (float)cos(angle * M_PI / 180);
	rotationMatrix.dx = 0; rotationMatrix.dy = 0;

	return rotationMatrix;
}

/// <summary>
/// ũ�⺯ȯ���
/// </summary>
/// <param name="scaleX">X�� ����</param>
/// <param name="scaleY">Y�� ����</param>
/// <returns></returns>
D2D1_MATRIX_3X2_F MakeMatrix::TranslateScale(const D2D1_POINT_2F scale)
{
	D2D1_MATRIX_3X2_F scalematrix;

	scalematrix.m11 = (float)scale.x;  scalematrix.m12 = 0;
	scalematrix.m21 = 0;	scalematrix.m22 = (float)scale.y;
	scalematrix.dx = 0;		scalematrix.dy = 0;

	return scalematrix;
}

/// <summary>
/// ��ȯ��� S R T
/// </summary>
/// <param name="scale">ũ�� ��ȯ���</param>
/// <param name="rotation">ȸ�����</param>
/// <param name="translate">�̵����</param>
/// <returns></returns>
D2D1_MATRIX_3X2_F MakeMatrix::TransformMatrix(D2D1_MATRIX_3X2_F& scale, D2D1_MATRIX_3X2_F& rotation, D2D1_MATRIX_3X2_F& translate)
{
	D2D1_MATRIX_3X2_F translatematrix;

	//����� ���� ��Ģ�� �����Ѵ�
	//d2d�� �຤�� ����
	// S R T ������ �ؾ� ��ü ��ȯ�� ������

	translatematrix = scale * rotation * translate;

	return translatematrix;
}

/// <summary>
/// ��ȯ ��� �����
/// </summary>
/// <param name="scale">ũ�� ��ȯ</param>
/// <param name="rotation">ȸ�� ��ȯ</param>
/// <param name="translate">�̵� ��ȯ</param>
/// <returns></returns>
D2D1_MATRIX_3X2_F MakeMatrix::MakeTransformMatrix(const D2D1_POINT_2F scale, const double rotation, const D2D1_POINT_2F translate)
{
	D2D1_MATRIX_3X2_F scalematrix = TranslateMove(scale);
	D2D1_MATRIX_3X2_F rotationMatrix = TranslateRotation(rotation);
	D2D1_MATRIX_3X2_F translateMatrix = TranslateScale(translate);

	m_translateMatrix = scalematrix * rotationMatrix * translateMatrix;

	return m_translateMatrix;
}

