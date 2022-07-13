#pragma once
class CameraManager : public Manager<Camera>
{
private:
	Camera* m_NowCamera;

public:
	//Manager �ʱ�ȭ(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void InitManager();
	//Manager ����(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void UpdateManager();

	//���� ���� ī�޶� ����
	void ChangeNowCamera(string camera_name);
	void ChangeNowCamera(Camera* camera);

	//���� ���� ī�޶� �߰�
	void AddCamera(string camera_name);

	//���� ���� ���� ī�޶� ��������
	Camera* GetNowCamera();
	//ī�޶� �̸����� ī�޶� ��������
	Camera* GetCamera(string camera_name);
};