#pragma once

#define DefaultBrushColor	D2D1::ColorF(D2D1::ColorF::White)
#define DefaultBGColor		D2D1::ColorF(D2D1::ColorF::Black)
#define CollisionColor		D2D1::ColorF(D2D1::ColorF::Green)

#define MGGraphicEngine	GraphicEngine::GetInstance()
#define MGSceneManager	SceneManager::GetInstance()
#define KeyInput		KeyInputManager::GetInstance()
//#define MySoundManager	SoundManager::GetInstance()

#define MGScene MGSceneManager->GetNowScene()
#define MGCamera MGScene->GetNowCamera()

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = nullptr;
	}
}

#define PI 3.14159f
#define DegreeToRad(angle)	(angle * PI / 180.0f)

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

#define Distance(x,y,a,b)	sqrtf((x-a)*(x-a) + (y-b)*(y-b))
#define Distance2(x,y)		sqrtf((x-y)*(x-y))
//#define Distance2(x,y)		sqrtf((x*x)+(y*y))