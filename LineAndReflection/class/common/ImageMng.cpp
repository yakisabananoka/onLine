#include <DxLib.h>
#include "ImageMng.h"
#include "../../_debug/_DebugConOut.h"

ImageMng::ImageMng()
{
}

ImageMng::~ImageMng()
{
	InitSoftImage();
}

const VecInt& ImageMng::GetID(std::string key)
{
	if (!imageMap_.count(key))
	{
		TRACE("通常画像読み込み\n");
		imageMap_[key].resize(1);
		imageMap_[key][0]= LoadGraph(key.c_str());

		if (imageMap_[key][0] == -1)
		{
			TRACE("通常画像読み込み失敗\n");
		}
	}

	return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key)
{
	if (!imageMap_.count(key))
	{
		TRACE("通常画像読み込み\n");
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(f_name.c_str());

		if (imageMap_[key][0] == -1)
		{
			TRACE("通常画像読み込み失敗\n");
		}
	}

	return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt)
{
	if (!imageMap_.count(key))
	{
		TRACE("通常画像読み込み\n");
		imageMap_[key].resize(divCnt.Area());

		//画像未ロードの場合ロード
		if (LoadDivGraph(f_name.c_str(), divCnt.Area(), divCnt.x, divCnt.y, divSize.x, divSize.y, &imageMap_[key][0], true) == -1)
		{
			TRACE("通常画像読み込み失敗\n");
		}
	}

	return imageMap_[key];
}

const VecInt& ImageMng::GetID(std::string key, int handle)
{
	if (!imageMap_.count(key))
	{
		imageMap_[key].resize(1);
		imageMap_[key][0] = handle;

		if (imageMap_[key][0] == -1)
		{
			TRACE("読み込み失敗画像登録\n");
		}
	}

	return imageMap_[key];
}

const int& ImageMng::GetSoftID(std::string key)
{
	if (!softImageMap_.count(key))
	{
		TRACE("CPU画像読み込み\n");
		softImageMap_[key] = LoadARGB8ColorSoftImage(key.c_str());

		if (softImageMap_[key] == -1)
		{
			TRACE("CPU画像読み込み失敗\n");
		}
	}

	return softImageMap_[key];
}

const int& ImageMng::GetSoftID(std::string key, int handle)
{
	if (!softImageMap_.count(key))
	{
		softImageMap_[key] = handle;

		if (softImageMap_[key] == -1)
		{
			TRACE("読み込み失敗画像登録\n");
		}
	}

	return softImageMap_[key];
}

const VecInt& ImageMng::GetMaskID(std::string key)
{
	if (!maskImageMap_.count(key))
	{
		TRACE("マスク画像読み込み\n");
		maskImageMap_[key].resize(1);
		maskImageMap_[key][0] = LoadMask(key.c_str());

		if (maskImageMap_[key][0] == -1)
		{
			TRACE("マスク画像読み込み失敗\n");
		}
	}

	return maskImageMap_[key];
}

const VecInt& ImageMng::GetMaskID(std::string f_name, std::string key)
{
	if (!maskImageMap_.count(key))
	{
		TRACE("マスク画像読み込み\n");
		maskImageMap_[key].resize(1);
		maskImageMap_[key][0] = LoadMask(f_name.c_str());

		if (maskImageMap_[key][0] == -1)
		{
			TRACE("マスク画像読み込み失敗\n");
		}
	}

	return maskImageMap_[key];
}

const VecInt& ImageMng::GetMaskID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt)
{
	if (!maskImageMap_.count(key))
	{
		TRACE("マスク画像読み込み\n");
		maskImageMap_[key].resize(divCnt.Area());

		//画像未ロードの場合ロード
		if (LoadDivMask(f_name.c_str(), divCnt.Area(), divCnt.x, divCnt.y, divSize.x, divSize.y, &maskImageMap_[key][0]) == -1)
		{
			TRACE("マスク画像読み込み失敗\n");
		}
	}

	return maskImageMap_[key];
}

bool ImageMng::ExistID(std::string key)
{
	return imageMap_.count(key);
}

bool ImageMng::ExistSoftID(std::string key)
{
	return softImageMap_.count(key);
}

Vector2 ImageMng::GetSize(const std::string& key)
{
	Vector2 ret;
	GetGraphSize(GetID(key)[0], &ret.x, &ret.y);

	return ret;
}
