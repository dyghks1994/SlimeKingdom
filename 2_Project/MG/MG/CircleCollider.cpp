#include "pch.h"
#include "CircleCollider.h"

bool CircleCollider::IsHit(Collision* target)
{
	bool isHit = false;

	if (m_Active && target->m_Active)
	{
		////충돌 검사 대상이 BoxCollider면
		if (dynamic_cast<BoxCollider*>(target) != nullptr)
		{
			BoxCollider* pTarget = dynamic_cast<BoxCollider*>(target);

			MG_Rect myBB = GetBoundingBox();
			MG_Rect targetBB = pTarget->GetBoundingBox();

			/*float radius = sqrtf((myBB.pt[2].x - myBB.pt[0].x) * (myBB.pt[2].x - myBB.pt[0].x)
				+ (myBB.pt[2].y - myBB.pt[0].y) * (myBB.pt[2].y - myBB.pt[0].y)) * 0.5f;*/
			float radius = Distance(myBB.pt[0].x, myBB.pt[0].y, myBB.pt[1].x, myBB.pt[1].y) * 0.5f;
			D2D_POINT_2F myCenter = { (myBB.pt[0].x + myBB.pt[2].x) * 0.5f , (myBB.pt[0].y + myBB.pt[2].y) * 0.5f };

			if (((targetBB.pt[0].x - radius <= myCenter.x) && (targetBB.pt[1].x + radius >= myCenter.x))
				&& ((targetBB.pt[0].y <= myCenter.y) && (targetBB.pt[3].y >= myCenter.y))
				|| ((targetBB.pt[0].x <= myCenter.x) && (targetBB.pt[1].x >= myCenter.x))
				&& ((targetBB.pt[0].y - radius <= myCenter.y) && (targetBB.pt[3].y + radius >= myCenter.y))
				)
			{
				isHit = true;
			}
			else if ((Distance(targetBB.pt[0].x, targetBB.pt[0].y, myCenter.x, myCenter.y) <= radius)
				|| (Distance(targetBB.pt[1].x, targetBB.pt[1].y, myCenter.x, myCenter.y) <= radius)
				|| (Distance(targetBB.pt[2].x, targetBB.pt[2].y, myCenter.x, myCenter.y) <= radius)
				|| (Distance(targetBB.pt[3].x, targetBB.pt[3].y, myCenter.x, myCenter.y) <= radius))
			{
				isHit = true;
			}
		}

		//CircleCollider면
		if (dynamic_cast<CircleCollider*>(target) != nullptr)
		{
			CircleCollider* pTarget = dynamic_cast<CircleCollider*>(target);

			MG_Rect myBB = GetBoundingBox();
			MG_Rect targetBB = pTarget->GetBoundingBox();

			D2D_POINT_2F myCenter = (myBB.pt[0] + myBB.pt[2]);
			D2D_POINT_2F targetCenter = (targetBB.pt[0] + targetBB.pt[2]);

			myCenter = myCenter * 0.5f;
			targetCenter = targetCenter * 0.5f;

			float x = myCenter.x - targetCenter.x;
			float y = myCenter.y - targetCenter.y;

			float distance = sqrtf(x * x + y * y);
			float r1 = (myBB.pt[2].x - myBB.pt[0].x) / 2;
			float r2 = (targetBB.pt[2].x - targetBB.pt[0].x) / 2;

			if (distance <= r1 + r2)
			{
				isHit = true;
			}
		}

		return isHit;
	}
}

void CircleCollider::Draw()
{
	if (m_Active && m_Visible)
	{
		MGGraphicEngine->SetTransform(GetTransform().GetSRMatrix());
		D2D1_POINT_2F drawPoint = m_Transform.Position;
		MGGraphicEngine->DrawEllipse(drawPoint, m_Size.width * 0.5f, CollisionColor);
		MGGraphicEngine->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}
