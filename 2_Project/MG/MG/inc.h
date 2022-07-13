#pragma once

#pragma region 빌드플랫폼 별 라이브러리 추가 부분
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