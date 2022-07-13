// UglySlime.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "framework.h"
#include "inc.h"
#include "UglySlime.h"
#include "GameProcess.h"

//#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

#endif

int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     LPWSTR    lpCmdLine,
    _In_     int       nCmdShow)
{
    WNDCLASSEX wcex;
    ZeroMemory(&wcex, sizeof(wcex));
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_UGLYSLIME));
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wcex.hInstance = hInstance;
    wcex.lpszClassName = _T("MyGame");

    GameProcess MyGame;
    MyGame.Create(wcex, _T("Slime Kingdom"), hPrevInstance, lpCmdLine, nCmdShow);
    return MyGame.Run();
}