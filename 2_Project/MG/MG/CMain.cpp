#include "pch.h"
#include "CMain.h"

CMain* CMain::m_pMain = nullptr;

CMain::CMain(void)
{
	m_FrameLimit = 60;
	prevDTime = GetTickCount64();
}

CMain::~CMain(void)
{
}

LRESULT CALLBACK CMain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		MGGraphicEngine->Initialize(hWnd);
		MGSceneManager->InitManager();
		//MySoundManager->Initialize();

		m_pMain->OnCreate();
	}
	break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);

		MGGraphicEngine->Finalize();
		MGSceneManager->Finalize();
		//MySoundManager->Finalize();

		MGGraphicEngine->ReleaseInstance();
		MGSceneManager->ReleaseInstance();
		// MySoundManager->ReleaseInstance();

		m_pMain->OnDestroy();
	}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

BOOL CMain::Create(WNDCLASSEX& wcex, LPCTSTR szTitle, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	wcex.lpfnWndProc = WndProc;
	RegisterClassEx(&wcex);

	m_pMain = this;
	m_hWnd = CreateWindow(wcex.lpszClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		nullptr,
		nullptr,
		wcex.hInstance,
		nullptr);

	if (!m_hWnd)
	{
		return FALSE;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return TRUE;
}

int CMain::Run(void)
{
	MSG msg;

	while (TRUE)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (WM_QUIT == msg.message)
			{
				break;
			}
		}
		else
		{
			if (FrameCheck())
			{
				MGScene->prevUpdate();
				KeyInput->KeyUpdate();
				MainProcFrame();
				MGScene->Update();
				MGScene->Draw();
			}
		}
	}

	return static_cast<int>(msg.wParam);
}

void CMain::SetFrame(int frame)
{
	m_FrameLimit = frame;
}

bool CMain::FrameCheck()
{
	__int64 currDTime = GetTickCount64();
	if (currDTime - prevDTime < (1.0f / (float)m_FrameLimit) * 1000)
	{
		return false;
	}
	prevDTime = currDTime;
	return true;
}