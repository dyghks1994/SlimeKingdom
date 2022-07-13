#pragma once
class GraphicEngine : public Singleton<GraphicEngine>
{
private:
	HWND m_hWnd;		//메인 윈도우 핸들
	HRESULT m_hResult;	//결과값을 받아오기 위한 임시 변수

	// Device Independant Resources
	ID2D1Factory* m_pD2DFactory;		//d2d1 팩토리
	IDWriteFactory* m_pDWriteFactory;	//텍스트 출력을 위한 팩토리
	IDWriteTextFormat* m_pTextFormat;

	// Device Dependant Resources
	ID2D1HwndRenderTarget* m_pRenderTarget;	// 그리기를 할 대상인 렌더 타겟
	ID2D1SolidColorBrush* m_pBrush;			//출력 색을 바꾸기 위한 브러쉬

	IWICImagingFactory* m_pIWICFactory;		// 이미지 사용을 위한 팩토리

	D2D1_SIZE_F m_RenderTargetSize;			//렌더 타겟 사이즈

private:
	HRESULT CreateGraphicResoureces();
	void DiscardGraphicResources();

public:
	//그래픽 엔진 초기화(엔진 사용 전 무조건 한번은 초기화 해주어야 함)
	void Initialize(HWND hwnd);
	//그래픽 엔진 메모리 할당 해제
	void Finalize();

	void BeginRender();
	void EndRender();

	//리소스 폴더에서 리소스 타입으로 비트맵 로드
	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	//파일 경로로 리소스 폴더에서 비트맵 로드
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	//renderTarget의 SetTransform 함수를 사용할 수 있게 해주는 함수
	void SetTransform(D2D1_MATRIX_3X2_F matrix);

	void DrawTextFormat(float x, float y, D2D1_COLOR_F color, const WCHAR* str);

	void LoadSpriteSheet(const TCHAR* file_path, ID2D1Bitmap** bitmap);

	//Brush의 색을 color값으로 바꿔주는 함수
	D2D1_COLOR_F SetBrushColor(D2D1_COLOR_F color);

	void DrawBitmap(Transform transform, D2D1_POINT_2F origin, D2D1_SIZE_F size, D2D1_RECT_F bitmap_rect, ID2D1Bitmap* bitmap, float opacity = 1.0f);


#pragma region 도형 그리기

#pragma region 사각형 그리기
	//시작점과 끝점의 정보가 있는 rect로 사각형을 그리는 함수
	void DrawRectangle(D2D1_RECT_F rect, D2D1_COLOR_F color);

	//시작점(x1, y1)과 끝점(x2, y2)으로 사각형을 그리는 함수
	void DrawRectangle(float x1, float y1, float x2, float y2, D2D1_COLOR_F color);

	//중심점과 가로 세로 길이로 사각형을 그리는 함수
	void DrawRectangle(D2D1_POINT_2F center, float width, float height, D2D1_COLOR_F color);

	void DrawFillRectangle(float x1, float y1, float x2, float y2, D2D1_COLOR_F color);

	void DrawFillRectangle(D2D1_POINT_2F center, float width, float height, D2D1_COLOR_F color);
#pragma endregion

#pragma region 직선 그리기
	void DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, D2D1_COLOR_F color);
	void DrawLine(float x1, float y1, float x2, float y2, D2D1_COLOR_F color);
#pragma endregion

#pragma region 원 그리기
	void DrawEllipse(D2D1_ELLIPSE ellipse, D2D1_COLOR_F color);
	void DrawEllipse(float x1, float y1, float x2, float y2, D2D1_COLOR_F color);
	void DrawEllipse(D2D1_POINT_2F center, float radius, D2D1_COLOR_F color);
#pragma endregion

#pragma endregion

};
