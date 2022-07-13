#pragma once

class BoxCollider : public Collision
{
public:
	virtual bool IsHit(Collision* target);
	virtual void Draw();
};