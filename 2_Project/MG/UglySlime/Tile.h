#pragma once
class Tile : public GameObject
{
public:
	Tile(float size = 120);
	~Tile();

public:
	void SetValue(int attribute, int x, int y, bool typecheck = false);
};

