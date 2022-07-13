#pragma once
class SpriteManager
{
public:
	map<string, ID2D1Bitmap*> m_Bitmaps;
	map<string, Sprite*> m_Sprites;
	map<string, Animation*> m_Animations;

	vector<pair<const TCHAR*, string>> m_FDvec;

private:
	string m_ImagePath = "..\\resource\\Art";
	string m_UnitAnimInfoPath		= m_ImagePath + "\\unit_anim_info.txt";
	string m_UnitSpriteInfoPath		= m_ImagePath + "\\unit_name_info.txt";

public:
	void LoadAll();

	Sprite* GetSprite(string name);
	Animation* GetAnimation(string name);

private:
	void LoadImages();
	void LoadSprites();
	void LoadAnimations();

	void LoadUnitSpriteInfo(vector<string>& name_vec1);
	void LoadUnitAnimaionInfo();

	void CreateSpritesFromTextFile(string txt_path);
	void CreateAnimationsFromTextFile(string txt_path);

	void CreateUnitSprites(string sprite_name, int frame);
	void CreateSprite(string sprite_name, int frame);
	void CreateSprite(string sprite_name, int row, int col);
	void CreateSprite(string sprite_name, D2D1_POINT_2F start, int row, int col, int frame);
	void CreateSprite(string sprite_name, D2D1_POINT_2F start = { 0,0 });

	void CreatePlayerEndingAnimations();
	void CreateEngingAnimtion(string name, float speed);
	void CreateUnitAnimation(string name, int frame, float speed);
	void CreateAnimation(string name, int frame, float speed);

	void ResistImage(const TCHAR* filepath, string fd);
	void ResistSprite(string sprite_name, Sprite* sprite);
	void ResistAnimation(string anim_name, Animation* anim);

	void searchingDir(string path);
	int isFileOrDir(_finddata_t fd);
};

