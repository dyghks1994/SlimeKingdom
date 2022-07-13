#include "stdafx.h"

void SoundManager::Initialize()
{
	/// 사운드 초기화
	SLSoundManager->init();
	SLSoundManager->Set_BGM_Volume(0.5f);

	/// 사운드 로드
	LoadSoundAll();
}

void SoundManager::Update()
{
	SLSoundManager->Updata();
}

void SoundManager::LoadSoundAll()
{
	/// BGM
	SLSoundManager->LoadSound_BGM("../resource/Sound/Title.mp3", "Title");				// 타이틀
	SLSoundManager->LoadSound_BGM("../resource/Sound/Intro.mp3", "Intro");				// 인트로
	SLSoundManager->LoadSound_BGM("../resource/Sound/InGame.mp3", "InGame");			// 인게임
	SLSoundManager->LoadSound_BGM("../resource/Sound/Ending.mp3", "Ending");			// 엔딩

	/// 효과음
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Move.mp3", "Ch_Move");				// 이동
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_fAtk.mp3", "Ch_fAtk");				// 캐릭터 불공격
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_wAtk.mp3", "Ch_wAtk");				// 캐릭터 물공격
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_gAtk.mp3", "Ch_gAtk");				// 캐릭터 풀공격
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Drain.mp3", "Ch_Absorb");			// 캐릭터 흡수
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Heal.mp3", "Ch_Heal");				// 캐릭터 체력회복

	SLSoundManager->LoadSound_EX("../resource/Sound/Slime_Atk.mp3", "Slime_Atk");			// 몬스터 공격
	SLSoundManager->LoadSound_EX("../resource/Sound/Slime_Dead.mp3", "Slime_Dead");			// 몬스터 사망
	
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Hit.mp3", "Ch_Hit");					// 캐릭터 피격
	SLSoundManager->LoadSound_EX("../resource/Sound/Ch_Dead.mp3", "Ch_Dead");				// 캐릭터 사망
			
	SLSoundManager->LoadSound_EX("../resource/Sound/Box_Open.mp3", "Box_Open");				// 상자열기
	SLSoundManager->LoadSound_EX("../resource/Sound/Door_Open.mp3", "Door_Open");			// 문열림
	SLSoundManager->LoadSound_EX("../resource/Sound/Statue_On.mp3", "Statue_On");			// 석상 ON	
	SLSoundManager->LoadSound_EX("../resource/Sound/KingSlime_Change.mp3", "KingSlime");	// 킹 슬라임 변신
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

