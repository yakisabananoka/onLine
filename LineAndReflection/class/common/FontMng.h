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

	int GetID(std::string fontKey);		//フォントの取得
	int GetID(std::string fontKey, std::string path, std::string fontName, int size, int thick);					//フォントの登録と取得
	int GetID(std::string fontKey, std::string path, std::string fontName, int size, int thick, int fontType);		//フォントの登録と取得(フォントタイプ設定付き)

private:
	FontMng() {};
	~FontMng();

	std::unordered_map<std::string, std::pair<std::string, int>> fontMap_;		//フォントマップ
};

