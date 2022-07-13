#pragma once
class Sprite
{
public:
	Sprite(ID2D1Bitmap* bitmap, D2D1_RECT_F rect, D2D1_POINT_2F origin);
	Sprite(ID2D1Bitmap* bitmap, D2D1_RECT_F rect);
	Sprite(ID2D1Bitmap* bitmap, D2D1_POINT_2F start, float width, float height);

public:
	D2D1_RECT_F m_SpriteRect;		//시트에서 잘라올 위치(StartPoint(left, top), EndPoint(right, bottom)
	D2D1_POINT_2F m_OriginPos;		//스프라이트를 찍을 기준점

	D2D1_RECT_F m_CollisionRect;	//모션 별 콜라이더 위치

	ID2D1Bitmap* m_pBitmap;			//스프라이트 이미지 파일
};

