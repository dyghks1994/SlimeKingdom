#pragma once
class FSM
{
public:
	FSM();

protected:
	vector<State*> m_States;
	State* m_NowState;
	State* m_StartState;

public:
	virtual void Initialize();

	void SetStartState(State* state);
	State* GetNowState();
	void AddState(State* state);
	void AddCondition(State* start, State* end, Condition condition);
	virtual void Update();
	void Do();
};

