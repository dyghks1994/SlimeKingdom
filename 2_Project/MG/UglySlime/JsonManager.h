#pragma once
#include "Singleton.h"
#include "./Json/json.h"

typedef Json::Value			JsonValue;
typedef Json::ValueIterator	JsonValueIter;
typedef Json::Reader		JsonReader;
typedef Json::StyledWriter	JsonWriter;

typedef pair<UINT, vector<JsonValue>> Parent_Pair;
typedef pair<UINT, JsonValue> Child_Pair;

class JsonManager : public Singleton<JsonManager>
{
private:
	multimap<UINT, vector<JsonValue>>	m_ParentDatas;
	multimap<UINT, JsonValue>			m_ChildDatas;
	vector<string>						m_SaveDataTypeNames;

private:
	JsonValue	m_ParentRoot;
	JsonValue	m_ChildRoot;
	UINT		m_ChildLength;
	UINT		m_ChildKeyNumber;

private:
	list<JsonValue> m_JsonFileDatas;
	list<JsonValue>::const_iterator m_JFDiter;
	BOOL m_IsAllLoad;

public:
	JsonManager();
	~JsonManager();

	/// <summary>
	/// �����͵��� ����γ��� .json �������� ����
	/// </summary>
	/// <param name="folderFullpath">	: �����ϰ���� �����̸� or �������</param>
	/// <param name="fileName">			: �����̸�</param>
	/// <param name="dataSize">			: ������ ������ ���� (array[5] = 5�Է�, �����̸� 1)</param>
	/// <param name="curData">			: ���� �������� ������(����α�)</param>
	/// <param name="...remainDatas">	: �����ؾ��� �����͵�(���ϴ� ��ŭ �Է�)</param>
	template <typename T, typename... Types>
	VOID SaveDataToJsonType(string folderFullpath, string fileName, UINT dataSize, T curData, Types... remainDatas);
	VOID SaveDataToJsonType(string folderFullpath, string fileName, UINT dataSize);
	/// <summary>
	/// ����γ��� .json �������� ����� �����͵��� �ε�
	/// </summary>
	/// <param name="folderFullpath">	: �ҷ�������� �����̸� or �������</param>
	/// <param name="fileName">			: �����̸�</param>
	/// <param name="dataSize">			: �ҷ��� ������ ���� (array[5] = 5�Է�, �����̸� 1)</param>
	/// <param name="curData">			: �����ؾ��� ������(����α�)</param>
	/// <param name="...remainDatas">	: �ҷ��;��� �����͵�(���ϴ� ��ŭ �Է�)</param>
	template <typename T, typename... Types>
	VOID LoadDataFromJsonType(string folderFullpath, string fileName, UINT dataSize, T& curData, Types&... remainDatas);
	VOID LoadDataFromJsonType(string folderFullpath, string fileName, UINT dataSize);
};

template<typename T, typename ...Types>
VOID JsonManager::SaveDataToJsonType(string folderFullpath, string fileName, UINT dataSize, T curData, Types ...remainDatas)
{
#ifdef _DEBUG
	//if (m_ChildLength == 0 && m_ChildKeyNumber == 0)
	//	_tprintf(_T("! start save data, to json file\n\n"));
	//
	//size_t _remainDataCount = sizeof...(remainDatas);
	//cout << "! remaining data of child to insert count: " << _remainDataCount << endl;	
#endif
	m_ChildDatas.insert(Child_Pair(m_ChildKeyNumber++, curData));	

	m_SaveDataTypeNames.push_back(typeid(T).name());

	SaveDataToJsonType(folderFullpath, fileName, dataSize, remainDatas...);
}

template<typename T, typename ...Types>
VOID JsonManager::LoadDataFromJsonType(string folderFullpath, string fileName, UINT dataSize, T& curData, Types & ...remainDatas)
{
	m_ChildKeyNumber++;

	LoadDataFromJsonType(folderFullpath, fileName, dataSize, remainDatas...);

	JsonValue _targetData = *m_JFDiter;

	switch (_targetData.type())
	{
	case Json::intValue:	
		curData = _targetData.asInt();
		break;
	case Json::realValue:
		curData = _targetData.asDouble();
		break;
	case Json::stringValue:
		curData = reinterpret_cast<T&>(_targetData.asString());
		break;
	case Json::booleanValue:
		curData = _targetData.asBool();
		break;
	}	

	m_JFDiter++;

#ifdef _DEBUG
	//cout << "! [" << --m_ChildKeyNumber << "] child data type is: " << typeid(T).name() << ", value: " << curData << endl;

	//if (m_ChildKeyNumber == 0)
	//	cout << "! remaining data of child to load count: " << --m_ChildLength << "\n" << endl;
#endif 

	if (m_JFDiter == m_JsonFileDatas.end())
	{
		m_JsonFileDatas.clear();		
		m_IsAllLoad = FALSE;

#ifdef _DEBUG
		//_tprintf(_T("! successfully load data\n"));
#endif
	}
}
