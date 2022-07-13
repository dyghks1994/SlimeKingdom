#pragma once
class CameraManager : public Manager<Camera>
{
private:
	Camera* m_NowCamera;

public:
	//Manager 초기화(상속받은 클래스에서 정의 필요)
	virtual void InitManager();
	//Manager 갱신(상속받은 클래스에서 정의 필요)
	virtual void UpdateManager();

	//현재 씬의 카메라 변경
	void ChangeNowCamera(string camera_name);
	void ChangeNowCamera(Camera* camera);

	//현재 씬에 카메라 추가
	void AddCamera(string camera_name);

	//현재 씬의 현재 카메라 가져오기
	Camera* GetNowCamera();
	//카메라 이름으로 카메라 가져오기
	Camera* GetCamera(string camera_name);
};