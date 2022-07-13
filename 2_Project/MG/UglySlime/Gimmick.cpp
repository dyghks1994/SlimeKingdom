#include "stdafx.h"
#include "Gimmick.h"

Gimmick::Gimmick(string name)
	: GameObject(name)
{
}

Gimmick::~Gimmick()
{
}

bool Gimmick::IsDestroyed()
{
	return m_IsDestroyed;
}
