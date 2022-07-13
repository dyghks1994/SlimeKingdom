#pragma once

enum class SLGameScene
{
	Title = 0,
	Intro,
	InGame,
	GameEnding,
	GameOver,

	SLGameSceneNum
};

enum class SLLayer
{
	Player,
	Monster,
	Monster_Atk,
	Player_Atk,
	Object,
	Water,
	Wall,

	CollisionLayerNum
};

enum class SLMapTile
{
	Wall,
	Ground,
	Water,

	TileNum
};

enum class SLAttribute
{
	Fire,
	Grass,
	Water,
	
	AttributeNum
};

enum class SLDepth
{
	Tile,
	Object,

	DepthNum
};

enum class SLObject
{
	Mon_Water = 1,
	Mon_Fire,
	Mon_Grass,

	Box_Water = 4,
	Box_Fire,
	Box_Grass,
	Bush,
	Bush_Life,
	Rock_Broken,
	Tree_1,
	Tree_2,
	Rock_1,
	Rock_2,
	Wall_1,
	Wall_2,
	Sign_1,
	Sign_2,
	Sign_3,
	Sign_4,
	Sign_5,
	Statue_Water,
	Statue_Fire,
	Statue_Grass,
	Statue_King,
	Switch_A_1,
	Switch_B_1,
	Switch_A_2,
	Switch_B_2,
	Switch_A_3,
	Switch_B_3,
	Switch_A_4,
	Switch_B_4,
	Switch_A_5,
	Switch_B_5,
	Goal,

	ObjectNum
};