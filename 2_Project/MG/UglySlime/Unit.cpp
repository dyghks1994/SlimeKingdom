#include "stdafx.h"

Unit::Unit(string name)
	: GameObject(name)
{
}

Unit::~Unit()
{
}

int Unit::GetLife() const
{
	return m_Life;
}

void Unit::SetLife(const int life)
{
	this->m_Life = life;
}

int Unit::GetCurrentHp() const
{
	return m_CurrentHp;
}

void Unit::SetCurrentHp(const int hp)
{
	this->m_CurrentHp = hp;
}

int Unit::GetMaxHp() const
{
	return m_MaxHp;
}

void Unit::SetMaxHp(const int hp)
{
	m_CurrentHp = hp;
}

D2D1_POINT_2F Unit::GetLookVector()
{
	return m_LookVector;
}

float Unit::GetMoveSpeed() const
{
	return m_MoveSpeed;
}

void Unit::SetMoveSpeed(const float moveSpeed)
{
	this->m_MoveSpeed = moveSpeed;
}

float Unit::GetShootSpeed() const
{
	return m_AttackSpeed;
}

void Unit::SetShootSpeed(const float attackSpeed)
{
	this->m_AttackSpeed = attackSpeed;
}

UnitAttribute Unit::GetAttribute() const
{
	return m_Attribute;
}

