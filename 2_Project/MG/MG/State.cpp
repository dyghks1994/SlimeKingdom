#include "pch.h"
#include "State.h"

State::State()
{
	m_Brenches.clear();
}

void State::AddCondition(State* state, Condition condition)
{
	if (state == nullptr)	return;

	for (auto iter = m_Brenches.begin(); iter != m_Brenches.end(); iter++)
	{
		if (iter->first == state)
		{
			iter->second.push_back(condition);
			return;
		}
	}

	vector<Condition> newConditionVec;
	newConditionVec.push_back(condition);
	m_Brenches.push_back(pair<State*, vector<Condition>>(state, newConditionVec));
}

State* State::GetNextState()
{
	for (auto iter = m_Brenches.begin(); iter != m_Brenches.end(); iter++)
	{
		bool isAllTrue = true;
		for (auto conIter = iter->second.begin(); conIter != iter->second.end(); conIter++)
		{
			if ((*conIter)() == false)
			{
				isAllTrue = false;
				break;
			}
		}

		if (isAllTrue)
		{
			return iter->first;
		}
	}

	return this;
}

void State::Do()
{

}