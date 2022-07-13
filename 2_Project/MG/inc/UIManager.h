#pragma once
class UIManager : public Manager<UI>
{
public:
	//Manager 초기화(상속받은 클래스에서 정의 필요)
	virtual void InitManager();
	//Manager 갱신(상속받은 클래스에서 정의 필요)
	virtual void UpdateManager();

	void Draw();

	void SetActive(bool active);
};

