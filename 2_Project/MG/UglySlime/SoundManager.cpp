#include "stdafx.h"

void SoundManager::Initialize()
{
	/// ���� �ʱ�ȭ
	SLSoundManager->init();
	SLSoundManager->Set_BGM_Volume(0.5f);

	/// ���� �ε�
	LoadSoundAll();
}

void SoundManager::Update()
{
	SLSoundManager->Updata();
}

void SoundManager::LoadSoundAll()
{
	/// BGM
	SLSoundManager->LoadSound_BGM("../resource/Sound/Title.mp3", "Title");				// Ÿ��Ʋ
	SLSoundManager->LoadSound_BGM("../resource/Sound/Intro.mp3", "Intro");				// ��Ʈ��
	SLSoundManager->LoadSound_BGM("../resource/Sound/InGame.mp3", "InGame");			// �ΰ���
	SLSoundManager->LoadSound_BGM("../resource/Sound/Ending.mp3", "Ending");			// ����

	/// ȿ����
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Move.mp3", "Ch_Move");				// �̵�
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_fAtk.mp3", "Ch_fAtk");				// ĳ���� �Ұ���
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_wAtk.mp3", "Ch_wAtk");				// ĳ���� ������
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_gAtk.mp3", "Ch_gAtk");				// ĳ���� Ǯ����
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Drain.mp3", "Ch_Absorb");			// ĳ���� ���
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Heal.mp3", "Ch_Heal");				// ĳ���� ü��ȸ��

	SLSoundManager->LoadSound_EX("../resource/Sound/Slime_Atk.mp3", "Slime_Atk");			// ���� ����
	SLSoundManager->LoadSound_EX("../resource/Sound/Slime_Dead.mp3", "Slime_Dead");			// ���� ���
	
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Hit.mp3", "Ch_Hit");					// ĳ���� �ǰ�
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Dead.mp3", "Ch_Dead");				// ĳ���� ���
			
	SLSoundManager->LoadSound_EX("../resource/Sound/Box_Open.mp3", "Box_Open");				// ���ڿ���
	SLSoundManager->LoadSound_EX("../resource/Sound/Door_Open.mp3", "Door_Open");			// ������
	SLSoundManager->LoadSound_EX("../resource/Sound/Statue_On.mp3", "Statue_On");			// ���� ON	
	SLSoundManager->LoadSound_EX("../resource/Sound/KingSlime_Change.mp3", "KingSlime");	// ŷ ������ ����
}

void SoundManager::SetVolumeBGM(float vol)
{
	SLSoundManager->Set_BGM_Volume(vol);
}

void SoundManager::SetVolumeEX(float vol)
{
	SLSoundManager->Set_EX_Volume(vol);
}

void SoundManager::PlayBGM(string key)
{
	SLSoundManager->Play_BGMSound(key);
}

void SoundManager::PlayEX(string key)
{
	SLSoundManager->Play_EXSound(key);
}

void SoundManager::StopBGM()
{
	SLSoundManager->Stop_BGM();
}

void SoundManager::PauseBGM(bool play)
{
	SLSoundManager->Paused_BGM(play);
}

