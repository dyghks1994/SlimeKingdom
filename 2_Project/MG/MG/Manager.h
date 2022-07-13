#pragma once

template<class Item>
class Manager
{
public:
	//Manager �Ҹ���
	virtual ~Manager();

public:
	map<string, pair<string, Item*>> m_ItemList;		//�Ŵ����� �����ϴ� ��� ���
	map<string, int> m_NameList;						//�ߺ��� �̸� ����

public:
	//Manager�� Item ���
	virtual void ResistItem(string name, Item* item);
	//Manager�� ItemList �Ѳ����� ���
	virtual void ResistItemList(string* namelist, Item** itemlist, int itemnum);
	//Manager�� ��ϵ� Item(��ϵ�������) ����
	virtual void RemoveItem(string name);
	virtual void RemoveItem(Item* item);

	//Manager�� ��ϵ� ItemList ����
	virtual void ResetItemList();
	//�̹� ��ϵ� �̸����� Ȯ���ϴ� �Լ�
	bool CheckNameList(string& name);

	//Manager �ʱ�ȭ(��ӹ��� Ŭ�������� ���� �ʿ�)
	virtual void InitManager() = 0;
	//Manager ����(��ӹ��� Ŭ�������� ���� �ʿ�)
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
	//������ ����Ʈ Ȯ�� �� �ش� �������� ������ ����
	auto itemIter = m_ItemList.find(name);
	if (itemIter == m_ItemList.end())
	{
		return;
	}

	//�ߺ��̸� ����Ʈ���� ������ �ϳ� ����, ���� ������ 0�̸� �ߺ��̸� ����Ʈ���� ����
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
	//������ ����Ʈ Ȯ�� �� �ش� �������� ������ ���� �� ����
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
	//�ߺ��̸� ����Ʈ Ȯ�� �� ���� �̸��� ������ �������� �߰��ϱ�
	auto nameIter = m_NameList.find(name);
	if (nameIter == m_NameList.end())
	{
		m_NameList.insert(pair<string, int>(name, 1));
		return true;
	}

	//�ߺ��̸� ����Ʈ�� �־��� ��� �ڿ� ���ڸ� �ٿ� �����ϱ�
	int num = nameIter->second;
	nameIter->second++;
	name += "_" + to_string(num);
	return true;
}