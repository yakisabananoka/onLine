#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "Vector2.h"

#define lpImageMng ImageMng::GetInstance()

using VecInt = std::vector<int>;

class ImageMng
{
public:
	static ImageMng& GetInstance(void)
	{
		static ImageMng s_Instance;
		return s_Instance;
	}

	//通常画像用
	const VecInt& GetID(std::string key);
	const VecInt& GetID(std::string f_name, std::string key);
	const VecInt& GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt);
	const VecInt& GetID(std::string key, int handle);

	//CPUで扱う画像用
	const int& GetSoftID(std::string key);
	const int& GetSoftID(std::string key, int handle);

	//マスク画像用
	const VecInt& GetMaskID(std::string key);
	const VecInt& GetMaskID(std::string f_name, std::string key);
	const VecInt& GetMaskID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt);

	bool ExistID(std::string key);			//画像が存在するか否か
	bool ExistSoftID(std::string key);		//ソフト画像が存在するか否か

	Vector2 GetSize(const std::string& key);

private:
	ImageMng();
	~ImageMng();

	std::unordered_map<std::string, VecInt> imageMap_;			//通常画像マップ
	std::unordered_map<std::string, int> softImageMap_;			//ソフト画像マップ
	std::unordered_map<std::string, VecInt> maskImageMap_;		//マスク画像マップ

	void operator()(const ImageMng&) = delete;
	void operator=(const ImageMng&) = delete;
};

 