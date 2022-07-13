#include "pch.h"
#include "Camera.h"

Camera::Camera(string name)
{
	m_TargetPoint = { 0,0 };
	m_MoveSpeed = 100.0f;

	MGScene->ResistCamera(name, this);
}

void Camera::Initialize()
{
}

void Camera::Update()
{
	if (Distance(m_Transform.Position.x, m_Transform.Position.y, m_TargetPoint.x, m_TargetPoint.y) >= m_MoveSpeed)
	{
		D2D1_POINT_2F dir = { m_TargetPoint.x - m_Transform.Position.x, m_TargetPoint.y - m_Transform.Position.y};
		float distance = Distance2(dir.x, dir.y);
		if (distance != 0)
		{
			dir.x = dir.x / distance;
			dir.y = dir.y / distance;
		}
		m_Transform.Position.x += m_MoveSpeed * dir.x * 1.7f;
		m_Transform.Position.y += m_MoveSpeed * dir.y;
	}
	else
	{
		m_Transform.Position = m_TargetPoint;
	}
}

Transform Camera::WorldToScreen(Transform target)
{
	Transform resultTransform;

	resultTransform.Position.x = target.Position.x - m_Transform.Position.x;
	resultTransform.Position.y = target.Position.y - m_Transform.Position.y;

	resultTransform.Angle = target.Angle + m_Transform.Angle;

	resultTransform.Scale.x = target.Scale.x * m_Transform.Scale.x;
	resultTransform.Scale.y = target.Scale.y * m_Transform.Scale.y;

	return resultTransform;
}

void Camera::Move(float x, float y)
{
	m_TargetPoint.x = x;
	m_TargetPoint.y = y;
}
