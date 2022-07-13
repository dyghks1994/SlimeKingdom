#include "pch.h"
#include "Animator.h"

void Animator::Initialize()
{
	
}

void Animator::Update()
{
	while (m_NowState != m_NowState->GetNextState())
	{
		m_NowState = m_NowState->GetNextState();
		reinterpret_cast<Animation*>(m_NowState)->Reset();
	};
}
