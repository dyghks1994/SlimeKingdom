#include "pch.h"
#include "Animation.h"

Animation::Animation(vector<Sprite*> sprites)
	:m_Speed(1.0f), m_NowIndex(0), m_TotalDelay(0), m_IsLoop(true)
{
	m_pSprites = sprites;
}

Animation::Animation()
	: m_Speed(1.0f), m_NowIndex(0), m_TotalDelay(0), m_IsLoop(true)
{
}

Animation::Animation(Animation& anim)
{
	m_Speed = anim.m_Speed;
	m_IsLoop = anim.m_IsLoop;
	m_Brenches = anim.m_Brenches;
	m_pSprites = anim.m_pSprites;

	m_NowIndex = 0;
	m_TotalDelay = 0;
}

void Animation::Reset()
{
	m_TotalDelay = 0;
	m_NowIndex = 0;
}

void Animation::Update()
{
	m_TotalDelay += m_Speed;// / GetNowSprite()->m_Delay;
	if (m_TotalDelay >= 10.0f)
	{
		++m_NowIndex;
		m_NowIndex %= m_pSprites.size();

		if (m_IsLoop)
		{
			m_TotalDelay = 0.0f;
		}
		else
		{
			m_NowIndex = m_pSprites.size() - 1;
			m_TotalDelay = m_Speed * m_pSprites.size();
		}
	}
}

Sprite* Animation::GetNowSprite()
{
	return m_pSprites.at(m_NowIndex);
}

float Animation::GetProgress()
{
	return m_TotalDelay / (m_Speed * m_pSprites.size());
}
