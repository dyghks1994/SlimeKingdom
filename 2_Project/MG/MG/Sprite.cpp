#include "pch.h"
#include "Sprite.h"

Sprite::Sprite(ID2D1Bitmap* bitmap, D2D1_RECT_F rect, D2D1_POINT_2F origin)
	:m_pBitmap(bitmap), m_SpriteRect(rect), m_OriginPos(origin)
{
}

Sprite::Sprite(ID2D1Bitmap* bitmap, D2D1_RECT_F rect)
	: m_pBitmap(bitmap), m_SpriteRect(rect)
{
	m_OriginPos.x = (m_SpriteRect.right - m_SpriteRect.left) * 0.5f;
	m_OriginPos.y = (m_SpriteRect.bottom - m_SpriteRect.top) * 0.5f;
}

Sprite::Sprite(ID2D1Bitmap* bitmap, D2D1_POINT_2F start, float width, float height)
	: m_pBitmap(bitmap), m_OriginPos({ width * 0.5f , height * 0.5f })
{
	m_SpriteRect = { start.x, start.y, start.x + width, start.y + height };
}
