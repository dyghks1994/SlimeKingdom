#pragma once

/// <summary>
/// Wall 클래스
/// Wall 기믹(오브젝트)는 벽과 나무 두 종류로 구분)
/// 둘다 그냥 벽이며 움직임이나 상호작용을 전혀 하지 않는다.
/// 단순히 길을 막기 위한 벽이다.
/// 
/// 각각의 콜라이더를 맞게 설정해 주자.
/// </summary>

enum class BlockType
{
	Wall_1,		// 벽1 오브젝트
	Wall_2,		// 벽2 오브젝트
	Tree_1,		// 나무1 오브젝트
	Tree_2,		// 나무2 오브젝트
	Rock_1,		// 바위 1
	Rock_2,		// 바위 2
	Goal,
};

class Block : public Gimmick
{
public:
	Block(float spawnPosX = 300.0f, float spawnPosY = 300.0f, BlockType type = BlockType::Wall_1, string = "Wall");
	~Block();

protected:

private:
	BlockType m_Type;
};

