#pragma once
class UIManager : public Manager<UI>
{
public:
	//Manager �ʱ�ȭ(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void InitManager();
	//Manager ����(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void UpdateManager();

	void Draw();

	void SetActive(bool active);
};

