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
	/// 데이터들을 상대경로내에 .json 형식으로 저장
	/// </summary>
	/// <param name="folderFullpath">	: 생성하고싶은 폴더이름 or 폴더경로</param>
	/// <param name="fileName">			: 파일이름</param>
	/// <param name="dataSize">			: 저장할 데이터 개수 (array[5] = 5입력, 단일이면 1)</param>
	/// <param name="curData">			: 현재 저장중인 데이터(비워두기)</param>
	/// <param name="...remainDatas">	: 저장해야할 데이터들(원하는 만큼 입력)</param>
	template <typename T, typename... Types>
	VOID SaveDataToJsonType(string folderFullpath, string fileName, UINT dataSize, T curData, Types... remainDatas);
	VOID SaveDataToJsonType(string folderFullpath, string fileName, UINT dataSize);
	/// <summary>
	/// 상대경로내에 .json 형식으로 저장된 데이터들을 로드
	/// </summary>
	/// <param name="folderFullpath">	: 불러오고싶은 폴더이름 or 폴더경로</param>
	/// <param name="fileName">			: 파일이름</param>
	/// <param name="dataSize">			: 불러올 데이터 개수 (array[5] = 5입력, 단일이면 1)</param>
	/// <param name="curData">			: 저장해야할 데이터(비워두기)</param>
	/// <param name="...remainDatas">	: 불러와야할 데이터들(원하는 만큼 입력)</param>
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
