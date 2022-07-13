#pragma once
#include "CMain.h"

class Player;
class GameSceneManager;

class GameProcess : public CMain
{
public:
	GameProcess(void);
	virtual ~GameProcess(void);

protected:
	virtual void OnCreate(void);
	virtual void OnDestroy(void);

protected:
	virtual void MainProcFrame(void);
};

