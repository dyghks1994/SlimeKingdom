#include "pch.h"
#include "FSM.h"

FSM::FSM()
	:m_NowState(nullptr), m_StartState(nullptr)
{}

void FSM::Initialize()
{
}

void FSM::SetStartState(State* state)
{
	AddState(state);
	m_StartState = state;
	m_NowState = m_StartState;
}

State* FSM::GetNowState()
{
	return m_NowState;
}

void FSM::AddState(State* state)
{
	for (auto iter = m_States.begin(); iter != m_States.end(); iter++)
	{
		if (*iter == state)
		{
			return;
		}
	}

	m_States.push_back(state);
}

void FSM::AddCondition(State* start, State* end, Condition condition)
{
	if (start == nullptr || end == nullptr) return;

	AddState(start);
	AddState(end);

	start->AddCondition(end, condition);
}

void FSM::Update()
{
	while (m_NowState != m_NowState->GetNextState())
	{
		m_NowState = m_NowState->GetNextState();
	};
}

void FSM::Do()
{
	m_NowState->Do();
}
