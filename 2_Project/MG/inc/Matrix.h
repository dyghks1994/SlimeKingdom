#pragma once

struct MG_Rect
{
	D2D_POINT_2F pt[4];
};

D2D_MATRIX_3X2_F GetTranslateMatrix(float dx, float dy);
D2D_MATRIX_3X2_F GetRotateMatrix(float angle);
D2D_MATRIX_3X2_F GetScaleMatrix(float x, float y);
D2D1_POINT_2F GetResultPoint(D2D1_POINT_2F& source, Transform transform);

D2D1_POINT_2F operator*(D2D1_POINT_2F& pt, D2D_MATRIX_3X2_F& matrix);
D2D1_POINT_2F operator+(D2D1_POINT_2F& pt1, D2D1_POINT_2F& pt2);
D2D1_POINT_2F operator/(D2D1_POINT_2F& pt, float value);
D2D1_POINT_2F operator*(D2D1_POINT_2F& pt, float value);

inline D2D_MATRIX_3X2_F GetTranslateMatrix(float dx, float dy)
{
	D2D_MATRIX_3X2_F tempMatrix;
	tempMatrix.m11 = 1;		tempMatrix.m12 = 0;
	tempMatrix.m21 = 0;		tempMatrix.m22 = 1;
	tempMatrix.dx = dx;		tempMatrix.dy = dy;

	return tempMatrix;
}

inline D2D_MATRIX_3X2_F GetRotateMatrix(float angle)
{
	D2D_MATRIX_3X2_F tempMatrix;
	tempMatrix.m11 = cosf(angle);		tempMatrix.m12 = -sinf(angle);
	tempMatrix.m21 = sinf(angle);		tempMatrix.m22 = cosf(angle);
	tempMatrix.dx = 0;					tempMatrix.dy = 0;

	return tempMatrix;
}

inline D2D_MATRIX_3X2_F GetScaleMatrix(float x, float y)
{
	D2D_MATRIX_3X2_F tempMatrix;
	tempMatrix.m11 = x;		tempMatrix.m12 = 0;
	tempMatrix.m21 = 0;		tempMatrix.m22 = y;
	tempMatrix.dx = 0;		tempMatrix.dy = 0;

	return tempMatrix;
}

inline D2D1_POINT_2F GetResultPoint(D2D1_POINT_2F& source, Transform transform)
{
	D2D1_POINT_2F tempPoint = source;

	D2D_MATRIX_3X2_F rotate = GetRotateMatrix(transform.Angle);
	D2D_MATRIX_3X2_F scale = GetScaleMatrix(transform.Scale.x, transform.Scale.y);
	D2D_MATRIX_3X2_F translate = GetTranslateMatrix(transform.Position.x, transform.Position.y);

	tempPoint = tempPoint * rotate;
	tempPoint = tempPoint * scale;
	tempPoint = tempPoint * translate;

	return tempPoint;
}

inline D2D1_POINT_2F operator*(D2D1_POINT_2F& pt, D2D_MATRIX_3X2_F& matrix)
{
	D2D1_POINT_2F tempPoint;
	tempPoint.x = pt.x * matrix.m11 + pt.y * matrix.m21 + matrix.dx;
	tempPoint.y = pt.y * matrix.m12 + pt.y * matrix.m22 + matrix.dy;

	return tempPoint;
}

inline D2D1_POINT_2F operator+(D2D1_POINT_2F& pt1, D2D1_POINT_2F& pt2)
{
	D2D1_POINT_2F tempPoint;
	tempPoint.x = pt1.x + pt2.x;
	tempPoint.y = pt1.y + pt2.y;

	return tempPoint;
}

inline D2D1_POINT_2F operator/(D2D1_POINT_2F& pt, float value)
{
	D2D1_POINT_2F tempPoint;
	tempPoint.x = pt.x / value;
	tempPoint.y = pt.y / value;

	return tempPoint;
}

inline D2D1_POINT_2F operator*(D2D1_POINT_2F& pt, float value)
{
	D2D1_POINT_2F tempPoint;
	tempPoint.x = pt.x * value;
	tempPoint.y = pt.y * value;

	return tempPoint;
}