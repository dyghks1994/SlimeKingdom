#pragma once
class CircleCollider : public Collision
{
public:
	virtual bool IsHit(Collision* target);
	virtual void Draw();
};

