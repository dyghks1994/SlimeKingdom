#pragma once
class Sprite
{
public:
	Sprite(ID2D1Bitmap* bitmap, D2D1_RECT_F rect, D2D1_POINT_2F origin);
	Sprite(ID2D1Bitmap* bitmap, D2D1_RECT_F rect);
	Sprite(ID2D1Bitmap* bitmap, D2D1_POINT_2F start, float width, float height);

public:
	D2D1_RECT_F m_SpriteRect;		//��Ʈ���� �߶�� ��ġ(StartPoint(left, top), EndPoint(right, bottom)
	D2D1_POINT_2F m_OriginPos;		//��������Ʈ�� ���� ������

	D2D1_RECT_F m_CollisionRect;	//��� �� �ݶ��̴� ��ġ

	ID2D1Bitmap* m_pBitmap;			//��������Ʈ �̹��� ����
};

