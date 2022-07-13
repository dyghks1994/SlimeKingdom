#pragma once

class Transform
{
public:
	Transform();

public:
	D2D_POINT_2F Position;
	D2D_POINT_2F Scale;
	float Angle;

public:
	D2D_MATRIX_3X2_F GetSRMatrix();

	Transform operator+(Transform& target);
	Transform operator+=(Transform& target);
};

inline Transform::Transform()
{
	Position.x = 0.0f;
	Position.y = 0.0f;

	Scale.x = 1.0f;
	Scale.y = 1.0f;

	Angle = 0.0f;
}

inline D2D_MATRIX_3X2_F Transform::GetSRMatrix()
{
	D2D_MATRIX_3X2_F resultMatix =
		D2D1::Matrix3x2F::Scale(Scale.x, Scale.y, { Position.x, Position.y })
		* D2D1::Matrix3x2F::Rotation(Angle, { Position.x, Position.y });

	return resultMatix;
}

inline Transform Transform::operator+(Transform& target)
{
	Transform temp;
	temp.Position = { Position.x + target.Position.x, Position.y + target.Position.y };
	temp.Angle = Angle + target.Angle;
	temp.Scale = { Scale.x * target.Scale.x, Scale.y * target.Scale.y };

	return temp;
}

inline Transform Transform::operator+=(Transform& target)
{
	return *this + target;
}