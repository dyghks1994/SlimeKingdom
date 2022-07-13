#include "stdafx.h"
#include "IntroScene.h"

IntroScene::IntroScene(string name)
{
	m_SceneName = name;
}

IntroScene::~IntroScene()
{
}

void IntroScene::ResetScene()
{
	m_WaitCheck = 0;
	m_TimeCheck = 0;

	m_NowCutNum = 0;

	m_State = 0;

	m_Intro->m_pRenderer->m_Opacity = 0.0f;
	m_OpacityChange = m_OpacityValue;
	m_Intro->SetSprite(SLDataManager->GetSprite("opening_" + to_string(m_NowCutNum + 1)));

	SoundManager::PlayBGM("Intro");
}

void IntroScene::InitScene()
{
	m_Conditions[(int)SLGameScene::InGame].push_back([this]()->bool { return m_NowCutNum == m_CutNum; });

	m_Intro = new ImageUI("Intro");
	m_Intro->m_Transform.Position.x = 960;
	m_Intro->m_Transform.Position.y = 540;
}

void IntroScene::DoScene()
{
	//스킵
	if (KeyInput->InputKeyDown(VK_ESCAPE))
	{
		m_NowCutNum = m_CutNum;
		return;
	}

	//다음 컷으로 바로 넘어가기
	if (KeyInput->InputKeyDown(VK_SPACE) || KeyInput->InputKeyDown(VK_LBUTTON))
	{
		m_Intro->m_pRenderer->m_Opacity = 1.0f;
		NextCut();
		m_State = 1;
		return;
	}

	switch (m_State)
	{
	case 0:
	{
		if (FadeInOut(true))
		{
			m_State++;
		}
	}
	break;

	case 1:
	{
		if (WaitCut(3.0f))
		{
			m_State++;
		}
	}
	break;

	case 2:
	{
		if (FadeInOut(false))
		{
			m_State++;
		}
	}
	break;

	case 3:
	{
		NextCut();
	}
	break;
	}
}

bool IntroScene::WaitCut(float time)
{
	m_WaitCheck += 1.0f;

	// 대기시간만큼 시간이 지났으면
	if (m_WaitCheck >= 60.0f * time)
	{
		m_WaitCheck = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void IntroScene::NextCut()
{
	m_WaitCheck = 0;
	m_State = 0;
	m_NowCutNum++;
	m_Intro->SetSprite(SLDataManager->GetSprite("opening_" + to_string(m_NowCutNum + 1)));
}

bool IntroScene::FadeInOut(bool fade)
{
	//밝아지기
	if (fade)
	{
		m_Intro->m_pRenderer->m_Opacity += m_OpacityValue;
		if (m_Intro->m_pRenderer->m_Opacity >= 1.0f)
		{
			m_Intro->m_pRenderer->m_Opacity = 1.0f;
			return true;
		}
		else
		{
			return false;
		}
	}

	//어두워지기
	else
	{
		m_Intro->m_pRenderer->m_Opacity -= m_OpacityValue;
		if (m_Intro->m_pRenderer->m_Opacity <= 0.0f)
		{
			m_Intro->m_pRenderer->m_Opacity = 0.0f;
			return true;
		}
		else
		{
			return false;
		}
	}
}
