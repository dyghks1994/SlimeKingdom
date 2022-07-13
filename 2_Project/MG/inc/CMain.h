#pragma once
#include <Windows.h>

class CMain
{
public:
	CMain(void);
	virtual ~CMain(void);

private:
	static LRESULT CALLBACK	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	BOOL	Create(WNDCLASSEX& wcex, LPCTSTR szTitle, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);
	int		Run(void);
	void	SetFrame(int frame);

protected:
	virtual void MainProcFrame(void) = 0;
	virtual bool FrameCheck();


protected:
	virtual void OnCreate(void) {}
	virtual void OnDestroy(void) {}

protected:
	static	CMain* m_pMain;
	HWND	m_hWnd;
	int		m_FrameLimit;

public:
	__int64 prevDTime;
};

