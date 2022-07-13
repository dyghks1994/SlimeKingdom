#pragma once
/// <summary>
/// ���� Ŭ����
/// ��, ��, Ǯ, ŷ�����Ӽ��� 4�� ����
/// 
/// �÷��̾ ������ ȹ���ؼ� �� �Ӽ� ����� ��ȣ�ۿ��ϸ� �̹����� �ٲ��� �Ѵ�.
/// 
/// ��, ��, Ǯ ������ ��� Ȱ��ȭ �Ǹ� ���� Ŭ����
/// 
/// �ֿ�ȯ
/// 2021.02.24
/// </summary>

enum class StatueType
{
	Water,
	Fire,
	Grass,
	King,
};

class Statue : public Gimmick
{
public:
	Statue(float spawnPosX = 300.0f, float spawnPosY = 300.0f, StatueType type = StatueType::Water, string str= "Statue");
	~Statue();

	// �ʱ�ȭ
	virtual void Initialize(const float spawnPosX, const float spawnPosY) override;

	// ������Ʈ
	virtual void Update() override;

	// �浹ó��
	virtual void Collision() override;

	// ���� ����
	void AttachJewelry(uint bag);

	// ������ ���� ���� ���� �Ǻ�
	bool IsAttachedJewelry();

protected:

private:
	StatueType m_Type;			//	������ �� ������ ������ Ÿ��
	bool m_AttachedJewelry;		// ������ ������ ������ �ֳ� �Ǻ��ϴ� ����
};

