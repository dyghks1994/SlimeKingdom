#pragma once

#pragma region �����÷��� �� ���̺귯�� �߰� �κ�
#ifdef _DEBUG
#ifdef _WIN64
#pragma comment(lib, "MG32d.lib")
#else
#pragma comment(lib, "MGd.lib")
#endif
#else
#ifdef _WIN64
#pragma comment(lib, "MG32.lib")
#else
#pragma comment(lib, "MG.lib")
#endif
#endif // DEBUG
#pragma endregion

#include "use.h"