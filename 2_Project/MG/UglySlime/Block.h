#pragma once

/// <summary>
/// Wall Ŭ����
/// Wall ���(������Ʈ)�� ���� ���� �� ������ ����)
/// �Ѵ� �׳� ���̸� �������̳� ��ȣ�ۿ��� ���� ���� �ʴ´�.
/// �ܼ��� ���� ���� ���� ���̴�.
/// 
/// ������ �ݶ��̴��� �°� ������ ����.
/// </summary>

enum class BlockType
{
	Wall_1,		// ��1 ������Ʈ
	Wall_2,		// ��2 ������Ʈ
	Tree_1,		// ����1 ������Ʈ
	Tree_2,		// ����2 ������Ʈ
	Rock_1,		// ���� 1
	Rock_2,		// ���� 2
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

