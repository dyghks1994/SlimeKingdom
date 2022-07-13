
/// <summary>
/// ���� �Ŵ��� Ŭ����
/// 
/// 2021.02.24. (��)
/// 
/// �ۼ��� : �����
/// 
/// hsSound�� ������ ���� �Ŵ���
/// </summary>

class SoundManager
{
public:
	// �ʱ�ȭ
	static void Initialize();

	// ������Ʈ
	static void Update();
	
	// ���� ���ҽ� �ε�
	static void LoadSoundAll();

	// ��������(0 ~ 1)
	static void SetVolumeBGM(float vol);
	static void SetVolumeEX(float vol);

	// �÷���
	static void PlayBGM(string key);
	static void PlayEX(string key);

	// ����
	static void StopBGM();
	static void PauseBGM(bool play);
};
