#pragma once

/// <summary>
/// Door Ŭ����
/// �ڽŰ� ����� ����ġ�� �۵� �Ǿ��� �� ������ ���̴�.
/// �ΰ��� ���� 5�� ������ �����̴�. (����ġ�� ���� �̷�)
/// 
/// �ֿ�ȯ
/// 2021.02.23
/// </summary>

enum class DoorState
{
	Closed,		// ���� ����
	Opening,	// ���� ��
	Opened,		// ���� ����
};


class Door : public Gimmick
{
public:
	Door(float spawnPosX = 300.0f, float spawnPosY = 300.0f, string = "Door");
	~Door();

	// �ִϸ��̼� ���
	Animation* GetAnim();

	// �ִϸ��̼� ����
	void StartAnim(Animation* anim);

	// �ʱ�ȭ
	virtual void Initialize(const float spawnPosX, const float spawnPosY);

	//������Ʈ
	virtual void Update();

	// ���ڰ� �����ִ��� Ȯ��
	bool IsOpened();

	/// ����� ����ġ�� �۵� ���� �� ���� ���� �Լ�
	void OpenDoor();

protected:

private:
	// ��������Ʈ
	Sprite* m_Sprite[2];

	// �ִϸ��̼�
	Animation* m_Anim;

	DoorState m_State;		// �� ����

	float m_DoorOpenTime;	// ���� ������ �ð�(�ӵ�)
	float openTimer;		// Ÿ�̸�
};

