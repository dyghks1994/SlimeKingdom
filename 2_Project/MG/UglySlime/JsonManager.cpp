#include "stdafx.h"
#include "JsonManager.h"

JsonManager::JsonManager()
	: m_ChildLength(0), m_ChildKeyNumber(0), m_IsAllLoad(false)
{
}

JsonManager::~JsonManager()
{
}

VOID JsonManager::SaveDataToJsonType(string folderFullpath, string fileName, UINT dataSize)
{
#ifdef _DEBUG	
//	cout << "! start [" << static_cast<int>(m_ChildLength) << "] child is insert, in parent datas\n" << endl;	
#endif		
	vector<JsonValue> _childJsonValues;

	multimap<UINT, JsonValue>::const_iterator _citer = m_ChildDatas.begin();
	for (; _citer != m_ChildDatas.end(); _citer++)
	{
#ifdef _DEBUG
	//	cout << "child root key index: " << (*_citer).first << ", value: " << (*_citer).second;
#endif		
		_childJsonValues.push_back((*_citer).second);
	}

	m_ParentDatas.insert(Parent_Pair(m_ChildLength++, _childJsonValues));

	_childJsonValues.clear();
	m_ChildDatas.clear();
	m_ChildKeyNumber = 0;

#ifdef _DEBUG
	//cout << "! complete [" << m_ChildLength - 1 << "] child data insert\n" << endl;
#endif

	if (m_ChildLength >= dataSize)
	{
#ifdef _DEBUG	
	//	_tprintf(_T("! start conversion to json file\n"));
#endif		
		UINT _typeIndex = 0;

		multimap<UINT, vector<JsonValue>>::const_iterator _piter = m_ParentDatas.begin();
		for (; _piter != m_ParentDatas.end(); _piter++)
		{
			for (UINT i = 0; i < (*_piter).second.size(); i++)
			{
				string _typeName = m_SaveDataTypeNames[_typeIndex++];

				m_ChildRoot[i][_typeName] = (*_piter).second[i];
			}

			m_ParentRoot[(*_piter).first] = m_ChildRoot;
		}

		JsonWriter _jswriter;
		string _parentRootStr = _jswriter.write(m_ParentRoot);

		string _saveFolderFullpath = "./" + folderFullpath;
		fs::path _checkpath(_saveFolderFullpath);

		assert(fs::exists(_checkpath));

		string _saveDataFullpath = _saveFolderFullpath + "/" + fileName + ".json";
		ofstream _fileWrite(_saveDataFullpath);
		_fileWrite << _parentRootStr;
		_fileWrite.close();

		m_ChildRoot.clear();
		m_ParentRoot.clear();
		m_ParentDatas.clear();
		m_SaveDataTypeNames.clear();
		m_ChildLength = 0;

#ifdef _DEBUG		
		//_tprintf(_T("! successfully save data to json file, in: \n"));

		//fs::path _jsonPath = _saveDataFullpath;
		//cout << fs::current_path() << "\n> " << _jsonPath.relative_path() << "\n" << endl;
#endif
	}
}

VOID JsonManager::LoadDataFromJsonType(string folderFullpath, string fileName, UINT dataSize)
{
	if (m_IsAllLoad == FALSE)
	{
#ifdef _DEBUG	
	//	_tprintf(_T("! start load data, form json file in: \n"));
#endif	
		string _loadFolderFullpath = "./" + folderFullpath;
		fs::path _checkpath(_loadFolderFullpath);

		assert(fs::exists(_checkpath));
	
		string _loadDataFullpath = _loadFolderFullpath + "/" + fileName + ".json";
		fs::path _jsonPath(_loadDataFullpath);
#ifdef _DEBUG
	//	cout << fs::current_path() << "\n> " << _jsonPath.relative_path() << "\n" << endl;
#endif

		ifstream _readStream;
		_readStream.open(_loadDataFullpath, ifstream::in | ifstream::binary);
		_readStream >> m_ParentRoot;
		_readStream.close();
	
		Json::ValueIterator _jpiter = m_ParentRoot.begin();
		for (; _jpiter != m_ParentRoot.end(); _jpiter++)
		{
			list<JsonValue> _childDatas;
		
			Json::ValueIterator _jciter = (*_jpiter).begin();
			for (; _jciter != (*_jpiter).end(); _jciter++)
			{		
				Json::ValueIterator _data = (*_jciter).begin();
				_childDatas.push_back(*_data);
			}

			_childDatas.reverse();

			list<JsonValue>::const_iterator _cditer = _childDatas.begin();
			for (; _cditer != _childDatas.end(); _cditer++)
			{
				m_JsonFileDatas.push_back(*_cditer);
			}

			_childDatas.clear();
			m_ChildLength++;
		}

		m_JFDiter = m_JsonFileDatas.begin();
		m_ParentRoot.clear();
		m_IsAllLoad = TRUE;

#ifdef _DEBUG
		//_tprintf(_T("! successfully read all data, form json file\n\n"));
#endif
	}
}
