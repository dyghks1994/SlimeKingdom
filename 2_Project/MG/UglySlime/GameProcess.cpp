#include "stdafx.h"

GameProcess::GameProcess(void)
{
}

GameProcess::~GameProcess(void)
{
}

void GameProcess::OnCreate(void)
{
	SLGameManager->Initialize();
}

void GameProcess::OnDestroy(void)
{
	//SLGameManager->Finalize();
}

void GameProcess::MainProcFrame(void)
{
	SLGameManager->Update();
}
