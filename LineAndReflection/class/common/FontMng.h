#pragma once
#include <string>
#include <unordered_map>
#include <utility>

#define lpFontMng FontMng::GetInstance()

class FontMng
{
public:
	static FontMng& GetInstance(void)
	{
		static FontMng s_Instance;
		return s_Instance;
	}

	int GetID(std::string fontKey);		//�t�H���g�̎擾
	int GetID(std::string fontKey, std::string path, std::string fontName, int size, int thick);					//�t�H���g�̓o�^�Ǝ擾
	int GetID(std::string fontKey, std::string path, std::string fontName, int size, int thick, int fontType);		//�t�H���g�̓o�^�Ǝ擾(�t�H���g�^�C�v�ݒ�t��)

private:
	FontMng() {};
	~FontMng();

	std::unordered_map<std::string, std::pair<std::string, int>> fontMap_;		//�t�H���g�}�b�v
};

