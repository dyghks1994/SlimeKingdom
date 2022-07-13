#include "pch.h"
#include "GameObjectManager.h"

void GameObjectManager::InitManager()
{

}

void GameObjectManager::UpdateManager()
{
	GameObject* tempGameObject;
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		tempGameObject = iter->second.second;
		tempGameObject->MGUpdate();
	}
	CheckCollision();
}

void GameObjectManager::Draw()
{
	vector<GameObject*> sortList, ycheckList;
	GameObject* tempGameObject;
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		tempGameObject = iter->second.second;
		Renderer* tempRenderer = tempGameObject->m_pRenderer;

		sortList.push_back(tempGameObject);
	}

	//Depth순으로 1차 정렬
	sort(sortList.begin(), sortList.end(),
		[](GameObject* A, GameObject* B)->int {
			int ret = 0;
			//Depth 우선 비교
			if (A->m_pRenderer->m_Depth < B->m_pRenderer->m_Depth)
			{
				ret = -1;
			}
			else if (A->m_pRenderer->m_Depth == B->m_pRenderer->m_Depth)
			{
				if (A->GetTransform().Position.y < B->GetTransform().Position.y)
				{
					ret = -1;
				}
			}

			return ret;
		});

	for (auto iter = sortList.begin(); iter != sortList.end(); iter++)
	{
		(*iter)->Draw();
	}
}

void GameObjectManager::CheckCollision()
{
	for (auto obj : m_ItemList)
	{
		obj.second.second->m_pCollider->ResetHits();
	}


	for (auto obj : m_ItemList)
	{
		GameObject* source = obj.second.second;
		Collision* sourceCollider = source->m_pCollider;

		//안움직인 물체이면 continue
		if (source->GetDirect().x == 0 && source->GetDirect().y == 0) continue;
		
		//본인이 꺼져있으면 다음 오브젝트 체크
		if (sourceCollider == nullptr) continue;
		if (!source->m_Active || !sourceCollider->m_Active) continue;

		for (auto obj2 : m_ItemList)
		{
			GameObject* target = obj2.second.second;
			Collision* targetCollider = target->m_pCollider;

			//체크 대상이 본인이면 continue
			if (source == target) continue;
			//체크 대상이 꺼져있으면 continue
			if (targetCollider == nullptr) continue;
			if (!target->m_Active || !targetCollider->m_Active) continue;
			//상호 충돌 여부 확인 후 충돌하지 않으면 continue;
			if (!MGSceneManager->CheckLayerCollisionTabele(source->m_Layer, target->m_Layer)) continue;
			//체크 대상의 Hit Objects에 이미 본인이 들어가있으면 continue
			bool IsAlreadyIn = false;
			for (auto in : sourceCollider->m_Hits)
			{
				if (in == target)
				{
					IsAlreadyIn = true;
					break;
				}
			}
			if (IsAlreadyIn)	continue;

			if (sourceCollider->IsHit(targetCollider))
			{
				sourceCollider->ResistHits(targetCollider);

				if (!sourceCollider->m_IsTrigger && !targetCollider->m_IsTrigger)
				{
					source->CalculateReflectionVector(target);
				}
			}
		}
	}
}

bool GameObjectManager::FindGameObject(GameObject* gameobj)
{
	GameObject* tempObj = nullptr;

	for (auto obj : m_ItemList)
	{
		if (obj.second.second == gameobj)
		{
			tempObj = obj.second.second;
			break;
		}
	}

	return tempObj != nullptr;
}

GameObject* GameObjectManager::FindGameObject(const string tag)
{
	GameObject* tempObj = nullptr;

	for (auto obj : m_ItemList)
	{
		if (obj.second.second->m_Tag == tag)
		{
			tempObj = obj.second.second;
			return tempObj;
		}
	}

	return nullptr;
}

void GameObjectManager::prevUpdate()
{
	GameObject* tempGameObject;
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		tempGameObject = iter->second.second;
		tempGameObject->prevUpdate();
	}
}

void GameObjectManager::SetActive(bool active)
{
	GameObject* tempGameObject;
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		tempGameObject = iter->second.second;
		tempGameObject->m_Active = active;
	}
}
