#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(string name)
	:m_Tag("Default"), m_Layer(0)
{
	m_pRenderer = new Renderer();
	m_pCollider = new BoxCollider();
	m_pAnimation = nullptr;
	m_pAnimator = nullptr;

	m_pRenderer->SetParent(this);
	m_pCollider->SetParent(this);

	MGScene->ResistGameObject(name, this);
}

GameObject::~GameObject()
{
	MGSceneManager->RemoveGameObject(this);
}

void GameObject::MGUpdate()
{
	if (m_Active)
	{
		if (m_pAnimator != nullptr)
		{
			m_pAnimator->Update();
			SetAnimation(reinterpret_cast<Animation*>(m_pAnimator->GetNowState()));
		}

		if (m_pAnimation != nullptr)
		{
			m_pAnimation->Update();
			if (m_pAnimation->GetNowSprite() != nullptr)
			{
				m_pRenderer->SetSprite(m_pAnimation->GetNowSprite());
			}
		}

		Update();
	}
}

void GameObject::Draw()
{
	if (m_Active && m_Visible)
	{
		Transform originTransform = GetTransform();

		m_Transform = MGCamera->WorldToScreen(originTransform);
		m_pRenderer->Draw();
		if (MGSceneManager->DrawCollider)
		{
			m_pCollider->Draw();
		}

		m_Transform = originTransform;
	}
}

void GameObject::SetSprite(Sprite* sprite)
{
	if (m_pRenderer == nullptr)
	{
		m_pRenderer = new Renderer();
	}

	m_pRenderer->SetSprite(sprite);
}

void GameObject::SetAnimation(Animation* animation)
{
	if (m_pAnimation == nullptr)
	{
		m_pAnimation = new Animation();
	}
	m_pAnimation = animation;
}

void GameObject::SetAnimator(Animator* animator)
{
	if (m_pAnimator == nullptr)
	{
		m_pAnimator = new Animator();
	}
	m_pAnimator = animator;
}

void GameObject::SetBoxCollider()
{
	if (m_pCollider != nullptr)
	{
		D2D1_SIZE_F size = m_pCollider->m_Size;
		delete m_pCollider;

		m_pCollider = new BoxCollider();
		m_pCollider->SetParent(this);
		m_pCollider->m_Size = size;
	}
}

void GameObject::SetCircleCollider()
{

	if (m_pCollider != nullptr)
	{
		D2D1_SIZE_F size = m_pCollider->m_Size;
		delete m_pCollider;

		m_pCollider = new CircleCollider();
		m_pCollider->SetParent(this);
		m_pCollider->m_Size = size;
	}
}

void GameObject::CalculateReflectionVector(GameObject* target)
{
	MG_Rect sourceRect = m_pCollider->GetBoundingBox();
	MG_Rect targetRect = target->m_pCollider->GetBoundingBox();

	D2D1_POINT_2F reflectionVector = { 0, 0 };

	/*if ((target->GetTransform().Position.x - GetTransform().Position.x) != 0)
	{
		reflectionVector.x = (target->GetTransform().Position.x - GetTransform().Position.x)
			/ Distance(GetTransform().Position.x, target->GetTransform().Position.x);
	}

	if ((target->GetTransform().Position.y - GetTransform().Position.y) != 0)
	{
		reflectionVector.y = (target->GetTransform().Position.y - GetTransform().Position.y)
			/ Distance(GetTransform().Position.y, target->GetTransform().Position.y);
	}*/

	reflectionVector = GetDirect();
	if (reflectionVector.x == 0 && reflectionVector.y == 0) return;

	float sourceminX = min(min(sourceRect.pt[0].x, sourceRect.pt[1].x), min(sourceRect.pt[2].x, sourceRect.pt[3].x));
	float targetminX = min(min(targetRect.pt[0].x, targetRect.pt[1].x), min(targetRect.pt[2].x, targetRect.pt[3].x));
	float minX = min(sourceminX, targetminX);
	float sourcemaxX = max(max(sourceRect.pt[0].x, sourceRect.pt[1].x), max(sourceRect.pt[2].x, sourceRect.pt[3].x));
	float targetmaxX = max(max(targetRect.pt[0].x, targetRect.pt[1].x), max(targetRect.pt[2].x, targetRect.pt[3].x));
	float maxX = max(sourcemaxX, targetmaxX);

	float sourceminY = min(min(sourceRect.pt[0].y, sourceRect.pt[1].y), min(sourceRect.pt[2].y, sourceRect.pt[3].y));
	float targetminY = min(min(targetRect.pt[0].y, targetRect.pt[1].y), min(targetRect.pt[2].y, targetRect.pt[3].y));
	float minY = min(sourceminY, targetminY);
	float sourcemaxY = max(max(sourceRect.pt[0].y, sourceRect.pt[1].y), max(sourceRect.pt[2].y, sourceRect.pt[3].y));
	float targetmaxY = max(max(targetRect.pt[0].y, targetRect.pt[1].y), max(targetRect.pt[2].y, targetRect.pt[3].y));
	float maxY = max(sourcemaxY, targetmaxY);

	float x = m_pCollider->m_Size.width + target->m_pCollider->m_Size.width - Distance2(minX, maxX);
	float y = m_pCollider->m_Size.height + target->m_pCollider->m_Size.height - Distance2(minY, maxY);

	reflectionVector.x *= x * -1;
	reflectionVector.y *= y * -1;

	m_Transform.Position = m_Transform.Position + reflectionVector;
}

D2D1_POINT_2F GameObject::GetDirect()
{
	D2D1_POINT_2F result = GetTransform().Position;
	result.x -= m_PrevObjState.GetTransform().Position.x;
	result.y -= m_PrevObjState.GetTransform().Position.y;
	result = Normalized(result);
	return result;
}

void GameObject::prevUpdate()
{
	m_PrevObjState = *this;
}

void GameObject::SetLayer(int layer)
{
	if (layer >= 0 && layer < 16)
	{
		m_Layer = layer;
	}
}

D2D1_POINT_2F GameObject::Normalized(D2D1_POINT_2F pos)
{
	D2D1_POINT_2F tempPT = pos;
	float distance = Distance(pos.x, pos.y, 0.0f, 0.0f);

	if (distance != 0)
	{
		tempPT.x = tempPT.x / distance;
		tempPT.y = tempPT.y / distance;
	}

	return tempPT;
}
