#include "pch.h"
#include "UIManager.h"

void UIManager::InitManager()
{
}

void UIManager::UpdateManager()
{
	UI* tempUI;
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		tempUI = iter->second.second;
		tempUI->Update();
	}
}

void UIManager::Draw()
{
	vector<UI*> sortUIList;

	for (auto item : m_ItemList)
	{
		sortUIList.push_back(item.second.second);
	}

	sort(sortUIList.begin(), sortUIList.end(), [](UI* A, UI* B)->bool 
		{
			return A->m_Depth < B->m_Depth;
		});

	for (auto iter = sortUIList.begin(); iter != sortUIList.end(); iter++)
	{
		(*iter)->Draw();
	}
}

void UIManager::SetActive(bool active)
{
	UI* tempUI;
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		tempUI = iter->second.second;
		tempUI->m_Active = active;
	}
}
