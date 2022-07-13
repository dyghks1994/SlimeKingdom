#pragma once
class Camera : public Object
{
public:
	Camera(string name);

public:
	void Initialize();
	void Update();
	Transform WorldToScreen(Transform transform);

	void Move(float x, float y);
private:
	D2D1_POINT_2F m_TargetPoint;
	float m_MoveSpeed;
};

