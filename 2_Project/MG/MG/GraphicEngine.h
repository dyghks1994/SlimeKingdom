#pragma once
class GraphicEngine : public Singleton<GraphicEngine>
{
private:
	HWND m_hWnd;		//���� ������ �ڵ�
	HRESULT m_hResult;	//������� �޾ƿ��� ���� �ӽ� ����

	// Device Independant Resources
	ID2D1Factory* m_pD2DFactory;		//d2d1 ���丮
	IDWriteFactory* m_pDWriteFactory;	//�ؽ�Ʈ ����� ���� ���丮
	IDWriteTextFormat* m_pTextFormat;

	// Device Dependant Resources
	ID2D1HwndRenderTarget* m_pRenderTarget;	// �׸��⸦ �� ����� ���� Ÿ��
	ID2D1SolidColorBrush* m_pBrush;			//��� ���� �ٲٱ� ���� �귯��

	IWICImagingFactory* m_pIWICFactory;		// �̹��� ����� ���� ���丮

	D2D1_SIZE_F m_RenderTargetSize;			//���� Ÿ�� ������

private:
	HRESULT CreateGraphicResoureces();
	void DiscardGraphicResources();

public:
	//�׷��� ���� �ʱ�ȭ(���� ��� �� ������ �ѹ��� �ʱ�ȭ ���־�� ��)
	void Initialize(HWND hwnd);
	//�׷��� ���� �޸� �Ҵ� ����
	void Finalize();

	void BeginRender();
	void EndRender();

	//���ҽ� �������� ���ҽ� Ÿ������ ��Ʈ�� �ε�
	HRESULT LoadResourceBitmap(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR resourceName,
		PCWSTR resourceType,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	//���� ��η� ���ҽ� �������� ��Ʈ�� �ε�
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

	//renderTarget�� SetTransform �Լ��� ����� �� �ְ� ���ִ� �Լ�
	void SetTransform(D2D1_MATRIX_3X2_F matrix);

	void DrawTextFormat(float x, float y, D2D1_COLOR_F color, const WCHAR* str);

	void LoadSpriteSheet(const TCHAR* file_path, ID2D1Bitmap** bitmap);

	//Brush�� ���� color������ �ٲ��ִ� �Լ�
	D2D1_COLOR_F SetBrushColor(D2D1_COLOR_F color);

	void DrawBitmap(Transform transform, D2D1_POINT_2F origin, D2D1_SIZE_F size, D2D1_RECT_F bitmap_rect, ID2D1Bitmap* bitmap, float opacity = 1.0f);


#pragma region ���� �׸���

#pragma region �簢�� �׸���
	//�������� ������ ������ �ִ� rect�� �簢���� �׸��� �Լ�
	void DrawRectangle(D2D1_RECT_F rect, D2D1_COLOR_F color);

	//������(x1, y1)�� ����(x2, y2)���� �簢���� �׸��� �Լ�
	void DrawRectangle(float x1, float y1, float x2, float y2, D2D1_COLOR_F color);

	//�߽����� ���� ���� ���̷� �簢���� �׸��� �Լ�
	void DrawRectangle(D2D1_POINT_2F center, float width, float height, D2D1_COLOR_F color);

	void DrawFillRectangle(float x1, float y1, float x2, float y2, D2D1_COLOR_F color);

	void DrawFillRectangle(D2D1_POINT_2F center, float width, float height, D2D1_COLOR_F color);
#pragma endregion

#pragma region ���� �׸���
	void DrawLine(D2D1_POINT_2F p1, D2D1_POINT_2F p2, D2D1_COLOR_F color);
	void DrawLine(float x1, float y1, float x2, float y2, D2D1_COLOR_F color);
#pragma endregion

#pragma region �� �׸���
	void DrawEllipse(D2D1_ELLIPSE ellipse, D2D1_COLOR_F color);
	void DrawEllipse(float x1, float y1, float x2, float y2, D2D1_COLOR_F color);
	void DrawEllipse(D2D1_POINT_2F center, float radius, D2D1_COLOR_F color);
#pragma endregion

#pragma endregion

};
