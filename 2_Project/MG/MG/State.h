#pragma once

typedef function<bool()> Condition;

class State
{
public:
	State();

protected:
	vector<pair<State*, vector<Condition>>> m_Brenches;

public:
	virtual void AddCondition(State* state, Condition condition);
	virtual State* GetNextState();
	virtual void Do();
};

