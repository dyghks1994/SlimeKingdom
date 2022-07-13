#include "stdafx.h"

void SpriteManager::LoadAll()
{
	LoadImages();
	LoadSprites();
	LoadAnimations();

	LoadUnitAnimaionInfo();
}

void SpriteManager::LoadImages()
{
	searchingDir(m_ImagePath);

	for (int i = 0; i < m_FDvec.size(); i++)
	{
		ResistImage(m_FDvec[i].first, m_FDvec[i].second);
	}
}

void SpriteManager::LoadSprites()
{
	CreateSpritesFromTextFile(m_ImagePath + "\\object_sprite_info.txt");
	CreateSpritesFromTextFile(m_ImagePath + "\\ui_sprite_info.txt");
	CreateSpritesFromTextFile(m_ImagePath + "\\other_sprite_info.txt");
}

void SpriteManager::LoadAnimations()
{
	CreateAnimationsFromTextFile(m_ImagePath + "\\object_anim_info.txt");
	CreateAnimationsFromTextFile(m_ImagePath + "\\ui_anim_info.txt");
	CreateAnimationsFromTextFile(m_ImagePath + "\\effect_anim_info.txt");
}

void SpriteManager::LoadUnitSpriteInfo(vector<string>& name_vec1)
{
	ifstream readSpriteInfoFile;
	readSpriteInfoFile.open(m_UnitSpriteInfoPath);    //파일 열기
	if (readSpriteInfoFile.is_open())
	{
		while (!readSpriteInfoFile.eof())
		{
			string str_line;
			getline(readSpriteInfoFile, str_line);
			name_vec1.push_back(str_line);
		}

		readSpriteInfoFile.close();    //파일 닫아줍니다.
	}
}

void SpriteManager::LoadUnitAnimaionInfo()
{
	vector<string> spriteNameVec;
	LoadUnitSpriteInfo(spriteNameVec);

	ifstream readAnimInfoFile;

	readAnimInfoFile.open(m_UnitAnimInfoPath);    //파일 열기

	if (readAnimInfoFile.is_open())
	{
		while (!readAnimInfoFile.eof())
		{
			string str_line;
			getline(readAnimInfoFile, str_line);
			istringstream ss(str_line);

			string type;
			int frame;
			float speed;

			ss >> type;
			ss >> frame;
			ss >> speed;

			for (int i = 0; i < type.size(); i++)
			{
				type[i] = tolower(type[i]); //대문자를 소문자로 교환
			}

			for (auto name : spriteNameVec)
			{
				string allName = name + "_" + type;
				CreateUnitSprites(allName, frame);
				CreateUnitAnimation(allName, frame, speed);
			}
		}
		readAnimInfoFile.close();    //파일 닫아줍니다.
	}

	CreatePlayerEndingAnimations();
}

void SpriteManager::CreateSpritesFromTextFile(string txt_path)
{
	ifstream readSpriteInfoFile;
	readSpriteInfoFile.open(txt_path);	// 파일열기
	if (readSpriteInfoFile.is_open())
	{
		while (!readSpriteInfoFile.eof())
		{
			string str_line;
			getline(readSpriteInfoFile, str_line);
			CreateSprite(str_line);
		}
		readSpriteInfoFile.close();		// 파일닫기
	}
}

void SpriteManager::CreateAnimationsFromTextFile(string txt_path)
{
	ifstream readAnimInfoFile;
	readAnimInfoFile.open(txt_path);		//파일 열기

	if (readAnimInfoFile.is_open())
	{
		while (!readAnimInfoFile.eof())
		{
			string str_line;
			getline(readAnimInfoFile, str_line);
			istringstream ss(str_line);

			string name;
			int frame;
			float speed;

			ss >> name;
			ss >> frame;
			ss >> speed;

			CreateSprite(name, frame);
			CreateAnimation(name, frame, speed);
		}
		readAnimInfoFile.close();
	}
}

Sprite* SpriteManager::GetSprite(string name)
{
	return m_Sprites[name];
}

Animation* SpriteManager::GetAnimation(string name)
{
	return m_Animations[name];
}

void SpriteManager::CreateUnitSprites(string sprite_name, int frame)
{
	string direct[] = { "", "_B", "_L", "_R" };

	for (int i = 0; i < 4; i++)
	{
		string tempName = sprite_name + direct[i];
		CreateSprite(tempName, frame);
	}
}

void SpriteManager::CreateSprite(string sprite_name, int frame)
{
	string bitmapName = sprite_name + ".png";
	ID2D1Bitmap* tempBitmap = m_Bitmaps[bitmapName];

	if (tempBitmap == nullptr) return;

	float width = tempBitmap->GetSize().width / frame;
	float height = tempBitmap->GetSize().height;

	D2D1_POINT_2F start = { 0,0 };

	for (int i = 0; i < frame; i++)
	{
		float x = start.x + (width * i);
		string name = sprite_name + "_";
		name += to_string(i);
		ResistSprite(name, new Sprite(tempBitmap, { x, start.y }, width, height));
	}
}

void SpriteManager::CreateSprite(string sprite_name, int row, int col)
{
	string bitmapName = sprite_name + ".png";
	ID2D1Bitmap* tempBitmap = m_Bitmaps[bitmapName];

	if (tempBitmap == nullptr) return;

	float width = tempBitmap->GetSize().width / col;
	float height = tempBitmap->GetSize().height / row;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			float x = width * i;
			float y = height * j;

			string name = sprite_name;
			name += +"_" + to_string(i);
			name += +"_" + to_string(j);
			ResistSprite(name, new Sprite(tempBitmap, { x, y }, width, height));
		}
	}
}

void SpriteManager::CreateSprite(string sprite_name, D2D1_POINT_2F start, int row, int col, int frame)
{
	string bitmapName = sprite_name + ".png";
	ID2D1Bitmap* tempBitmap = m_Bitmaps[bitmapName];

	if (tempBitmap == nullptr) return;

	float width = tempBitmap->GetSize().width / col;
	float height = tempBitmap->GetSize().height / row;

	for (int i = 0; i < frame; i++)
	{
		float x = start.x + (width * i);
		string name = sprite_name + "_";
		name += to_string(i);
		ResistSprite(name, new Sprite(tempBitmap, { x, start.y }, width, height));
	}
}

void SpriteManager::CreateSprite(string sprite_name, D2D1_POINT_2F start)
{
	string bitmapName = sprite_name + ".png";
	Sprite* tempSprite = nullptr;
	ID2D1Bitmap* tempBitmap = m_Bitmaps[bitmapName];

	if (tempBitmap == nullptr)		return;

	float width = tempBitmap->GetSize().width;
	float height = tempBitmap->GetSize().height;

	tempSprite = new Sprite(tempBitmap, start, width, height);

	ResistSprite(sprite_name, tempSprite);
}

void SpriteManager::CreatePlayerEndingAnimations()
{
	for (int i = 0; i < 79; i++)
	{
		string tempName = "00";
		if (i < 10)
		{
			tempName += "0";
		}
		tempName += to_string(i);
		CreateSprite(tempName);
	}

	CreateEngingAnimtion("playerEnding", 30.0f);
}

void SpriteManager::CreateEngingAnimtion(string name, float speed)
{
	vector<Sprite*> tempAnimSprites;

	for (int i = 0; i < 79; i++)
	{
		string tempName = "00";
		if (i < 10)
		{
			tempName += "0";
		}
		tempName += to_string(i);
		Sprite* tempSprite = GetSprite(tempName);
		if (tempSprite == nullptr)
		{
			return;
		}

		tempAnimSprites.push_back(tempSprite);
	}

	Animation* tempAnimation = new Animation(tempAnimSprites);
	tempAnimation->m_Speed = speed;

	ResistAnimation(name, tempAnimation);
}

void SpriteManager::CreateUnitAnimation(string name, int frame, float speed)
{
	string direct[] = { "", "_B", "_L", "_R" };

	for (int i = 0; i < 4; i++)
	{
		string tempName = name + direct[i];
		CreateAnimation(tempName, frame, speed);
	}
}

void SpriteManager::CreateAnimation(string name, int frame, float speed)
{
	vector<Sprite*> tempAnimSprites;

	for (int i = 0; i < frame; i++)
	{
		string indexName = name + "_" + to_string(i);
		Sprite* tempSprite = GetSprite(indexName);
		if (tempSprite == nullptr) return;

		tempAnimSprites.push_back(tempSprite);
	}

	Animation* tempAnimation = new Animation(tempAnimSprites);
	tempAnimation->m_Speed = speed;

	ResistAnimation(name, tempAnimation);
}

void SpriteManager::ResistImage(const TCHAR* filepath, string fd)
{
	ID2D1Bitmap* tempBitmap;
	MGGraphicEngine->LoadSpriteSheet(filepath, &tempBitmap);
	m_Bitmaps.insert(pair<string, ID2D1Bitmap*>(fd, tempBitmap));
}

void SpriteManager::ResistSprite(string sprite_name, Sprite* sprite)
{
	m_Sprites.insert(pair<string, Sprite*>(sprite_name, sprite));
}

void SpriteManager::ResistAnimation(string anim_name, Animation* anim)
{
	m_Animations.insert(pair<string, Animation*>(anim_name, anim));
}

void SpriteManager::searchingDir(string path)
{
	int checkDirFile = 0;
	string dirPath = path + "\\*.*";
	struct _finddata_t fd;//디렉토리 내 파일 및 폴더 정보 저장 객체
	intptr_t handle;

	if ((handle = _findfirst(dirPath.c_str(), &fd)) == -1L) //fd 구조체 초기화.
	{
		//파일이나 디렉토리가 없을 경우 종료
		return;
	}

	do //폴더 탐색 반복 시작
	{
		//현재 객체 종류 확인(파일 or 디렉토리)
		checkDirFile = isFileOrDir(fd);

		if (checkDirFile == 0 && fd.name[0] != '.') {
			//디렉토리일 때의 로직
			searchingDir(path + "\\" + fd.name);//재귀적 호출
		}
		else if (checkDirFile == 1 && fd.name[0] != '.') {
			//파일일 때의 로직
			string temp = path + "\\" + fd.name;

			size_t origsize = 0, convertedChars = 0; // 원래 문자열 길이, 변환된 문자열 길이

			origsize = strlen(temp.c_str()) + 1;  // 변환시킬 문자열의 길이를 구함
			//mbstowcs_s(&convertedChars, strChange, origsize, temp.c_str(), _TRUNCATE); // 변환

			basic_string<TCHAR> tstr;
			const char* all = temp.c_str();
			int len = 1 + strlen(all);
			wchar_t* t = new wchar_t[len];
			if (NULL == t) throw std::bad_alloc();
			mbstowcs_s(&convertedChars, t, len, all, _TRUNCATE);

			m_FDvec.push_back(pair<const TCHAR*, string>(t, fd.name));
		}

	} while (_findnext(handle, &fd) == 0);
	_findclose(handle);
}

int SpriteManager::isFileOrDir(_finddata_t fd)
//파일인지 디렉토리인지 판별
{
	if (fd.attrib & _A_SUBDIR)
		return 0; // 디렉토리면 0 반환
	else
		return 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환

}