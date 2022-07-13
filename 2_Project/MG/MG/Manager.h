#pragma once

template<class Item>
class Manager
{
public:
	//Manager 소멸자
	virtual ~Manager();

public:
	map<string, pair<string, Item*>> m_ItemList;		//매니저가 관리하는 대상 목록
	map<string, int> m_NameList;						//중복된 이름 관리

public:
	//Manager에 Item 등록
	virtual void ResistItem(string name, Item* item);
	//Manager에 ItemList 한꺼번에 등록
	virtual void ResistItemList(string* namelist, Item** itemlist, int itemnum);
	//Manager에 등록된 Item(등록되있으면) 삭제
	virtual void RemoveItem(string name);
	virtual void RemoveItem(Item* item);

	//Manager에 등록된 ItemList 리셋
	virtual void ResetItemList();
	//이미 등록된 이름인지 확인하는 함수
	bool CheckNameList(string& name);

	//Manager 초기화(상속받은 클래스에서 정의 필요)
	virtual void InitManager() = 0;
	//Manager 갱신(상속받은 클래스에서 정의 필요)
	virtual void UpdateManager() = 0;
};

template<class Item>
inline Manager<Item>::~Manager()
{
	ResetItemList();
}

template<class Item>
inline void Manager<Item>::ResistItem(string name, Item* item)
{
	string temp = name;
	if (CheckNameList(temp))
	{
		m_ItemList.insert(pair<string, pair<string, Item*>>(temp, pair<string, Item*>(name, item)));
	}
}

template<class Item>
inline void Manager<Item>::ResistItemList(string* namelist, Item** itemlist, int itemnum)
{
	for (int i = 0; i < itemnum; i++)
	{
		ResistItem(namelist[i], itemlist[i]);
	}
}

template<class Item>
inline void Manager<Item>::RemoveItem(string name)
{
	//아이템 리스트 확인 후 해당 아이템이 없으면 리턴
	auto itemIter = m_ItemList.find(name);
	if (itemIter == m_ItemList.end())
	{
		return;
	}

	//중복이름 리스트에서 개수를 하나 빼고, 만약 개수가 0이면 중복이름 리스트에서 삭제
	auto nameIter = m_NameList.find(name);
	nameIter->second--;
	if (nameIter->second <= 0)
	{
		m_NameList.erase(name);
		return;
	}
}

template<class Item>
inline void Manager<Item>::RemoveItem(Item* item)
{
	//아이템 리스트 확인 후 해당 아이템이 있으면 삭제 후 리턴
	for (auto iter : m_ItemList)
	{
		if (iter.second.second == item)
		{
			RemoveItem(iter.first);
			return;
		}
	}

}

template<class Item>
inline void Manager<Item>::ResetItemList()
{
	for (auto iter = m_ItemList.begin(); iter != m_ItemList.end(); iter++)
	{
		delete iter->second.second;
	}
	m_ItemList.clear();
	m_NameList.clear();
}

template<class Item>
inline bool Manager<Item>::CheckNameList(string& name)
{
	//중복이름 리스트 확인 후 같은 이름이 이전에 없었으면 추가하기
	auto nameIter = m_NameList.find(name);
	if (nameIter == m_NameList.end())
	{
		m_NameList.insert(pair<string, int>(name, 1));
		return true;
	}

	//중복이름 리스트에 있었을 경우 뒤에 숫자를 붙여 변형하기
	int num = nameIter->second;
	nameIter->second++;
	name += "_" + to_string(num);
	return true;
}