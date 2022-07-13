#include "pch.h"
#include "BoxCollider.h"

bool BoxCollider::IsHit(Collision* target)
{
	bool isHit = false;

	//본인과 충돌 대상의 Active가 모두 켜져있으면 체크
	if (m_Active && target->m_Active)
	{
		//충돌 검사 대상이 BoxCollider면
		if (dynamic_cast<BoxCollider*>(target) != nullptr)
		{
			BoxCollider* pTarget = dynamic_cast<BoxCollider*>(target);

			MG_Rect myBB = GetBoundingBox();
			MG_Rect targetBB = pTarget->GetBoundingBox();

			if (myBB.pt[0].x < targetBB.pt[2].x
				&& targetBB.pt[0].x < myBB.pt[2].x)
			{
				if (myBB.pt[0].y < targetBB.pt[2].y
					&& targetBB.pt[0].y < myBB.pt[2].y)
				{
					isHit = true;
				}
			}
		}

		////CircleCollider면
		//if (dynamic_cast<CircleCollider*>(this) != nullptr)
		//{
		//	CircleCollider* pTempCircleCollider = dynamic_cast<CircleCollider*>(this);
		//	pTempCircleCollider->CheckCollision(p_target);
		//}

		return isHit;
	}
}

void BoxCollider::Draw()
{
	if (m_Active && m_Visible)
	{
		MGGraphicEngine->SetTransform(GetTransform().GetSRMatrix());
		D2D1_POINT_2F drawPoint = GetTransform().Position;
		drawPoint.x += m_Transform.Position.x;
		drawPoint.y += m_Transform.Position.y;
		MGGraphicEngine->DrawRectangle(drawPoint, m_Size.width, m_Size.height, CollisionColor);
		MGGraphicEngine->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}
