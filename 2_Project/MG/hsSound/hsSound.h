#pragma once


/// <summary>
/// �⺻���� �̱��� Ŭ���� 
/// </summary>
class hsSound
{

public:

	/// <summary>
	/// �̱��� Ŭ������ �������� �Լ�
	/// </summary>
	/// <returns></returns>
	static hsSound* GM();

	/// <summary>
	/// ���� �⺻ �ʱ�ȭ
	/// </summary>
	void init();

	/// <summary>
	/// BGM ���� �ε�
	/// </summary>
	/// <param name="path">���� ���ϰ��</param>
	/// <param name="_Key">���� ã���� ����� Ű</param>
	void LoadSound_BGM(string path, string _Key);


	/// <summary> 
	/// ����Ʈ ���� �ε�
	/// </summary>
	/// <param name="path">���� ���� ���</param>
	/// <param name="_Key">���� Ű</param>
	void LoadSound_EX(string path, string _Key,bool _loop= false);



	/// <summary>
	/// ���� �⺻���
	/// </summary>
	/// <param name="_key">���� Ű��</param>
	///  <param name="_loop">������� ����</param>
	void Play_BGMSound(string _key);

	void Play_EXSound(string _key);

	/// <summary>
	/// BGMä�� ���� ����
	/// </summary>
	/// <param name="_volume">0~1 ������ ������</param>
	void Set_BGM_Volume(float _volume);

	/// <summary>
	/// BGMä�� ���带 ���� ���忡�� 0.1f ����
	/// </summary>
	void Set_BGM_VolumeUP();

	/// <summary>
	///  BGMä�� ���带 ���� ���忡�� 0.1f ����
	/// </summary>
	void Set_BGM_VolumeDown();


	/// <summary>
	/// EXä�� ���� ����
	/// </summary>
	/// <param name="_volume">0~1 ������ ������</param>
	void Set_EX_Volume(float _volume);

	/// <summary>
	/// EXä�� ���带 ���� ���忡�� 0.1f ����
	/// </summary>
	void Set_EX_VolumeUP();


	/// <summary>
	/// EXä�� ���带 ���� ���忡�� 0.1f ����
	/// </summary>
	void Set_EX_VolumeDown();


	/// <summary>
	/// ��� ������ ������ 
	/// </summary>
	/// <param name="_volume">0~1 ������ ����</param>
	void Set_MASTER_Volume(float _volume);

	/// <summary>
	/// ������ ������ ���带 0.1f ����
	/// </summary>
	void Set_MASTER_VolumeUP();

	/// <summary>
	/// ������ ������ ���带 0.1f ����
	/// </summary>
	void Set_MASTER_VolumeDOWN();



	/// <summary>
	/// BGM ä�� ����
	/// </summary>
	void Stop_BGM();

	/// <summary>
	/// �Ͻ�����
	/// </summary>
	void Paused_BGM(bool _play);


	/// <summary>
	/// EX ä�� ���� ���� ����� ó������
	/// </summary>
	void Stop_EX();

	/// <summary>
	/// EX ä�� �Ͻ�����
	/// </summary>
	/// <param name="_play">�Ͻ����� ����</param>
	void Paused_EX(bool _play);



	/// <summary>
	/// ��� ä�� ���� ���� ����� ó������
	/// </summary>
	void Stop_ALL();


	/// <summary>
	/// ������� ������Ʈ
	/// </summary>
	void Updata();


	void Sound2D_Update(float _x, float _y);
	void Play_Sound2D(string _key, float _x,float _y);
	void Sound2D_Max_Dis(float _dis);
private:
	/// <summary>
	/// ���� ������� �ƴ� ä���� ã�´�
	/// </summary>
	/// <returns></returns>
	Channel* FindChannel();


	static hsSound* instance;

	//���� �ý���
	System* g_System;

	//���� ����Ʈ 
	map<string, Sound*>	SoundList;

	//ä�ε�
	Channel* BGM_CH;
	Channel* EX_CH[7];


	//BGM ä�� ����Ʈ
	ChannelGroup* BGM_CH_Group;

	//ȿ���� ä�� ����Ʈ
	ChannelGroup* EX_CH_Group;

	//������ ä�� �׷�
	ChannelGroup* Master;



	//BGM ���� ����
	float BGM_VOLUME;

	//ȿ���� ���� ����
	float EX_VOLUME;

	//������ ���庼��
	float MASTER_VOLUME;

	//�÷��̾��� ������ġ
	float POS_X;
	float POS_Y;

	//�ִ� �����Ÿ�
	float Max_Range;

	hsSound();
	~hsSound();
};