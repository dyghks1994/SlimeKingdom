
/// <summary>
/// 사운드 매니져 클래스
/// 
/// 2021.02.24. (수)
/// 
/// 작성자 : 김경재
/// 
/// hsSound를 포장한 사운드 매니져
/// </summary>

class SoundManager
{
public:
	// 초기화
	static void Initialize();

	// 업데이트
	static void Update();
	
	// 사운드 리소스 로드
	static void LoadSoundAll();

	// 볼륨설정(0 ~ 1)
	static void SetVolumeBGM(float vol);
	static void SetVolumeEX(float vol);

	// 플레이
	static void PlayBGM(string key);
	static void PlayEX(string key);

	// 정지
	static void StopBGM();
	static void PauseBGM(bool play);
};
