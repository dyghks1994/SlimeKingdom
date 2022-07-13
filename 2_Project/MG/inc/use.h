#pragma once

#include <Windows.h>
#include <tchar.h>

#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

#include <map>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
//
//#include "fmod.hpp"
//using namespace FMOD;
using namespace std;

#include "Singleton.h"
#include "Manager.h"
#include "State.h"
#include "FSM.h"
#include "Transform.h"
#include "Matrix.h"
#include "Object.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Collision.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"
#include "Camera.h"
#include "UI.h"

#include "TextUI.h"
#include "ImageUI.h"
#include "RectUI.h"

#include "GraphicEngine.h"
#include "CameraManager.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "Scene.h"
#include "SceneManager.h"

#include "KeyInputManager.h"
#include "SoundManager.h"

#include "macro.h"

#include "CMain.h"