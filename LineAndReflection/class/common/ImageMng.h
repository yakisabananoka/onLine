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

	//�ʏ�摜�p
	const VecInt& GetID(std::string key);
	const VecInt& GetID(std::string f_name, std::string key);
	const VecInt& GetID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt);
	const VecInt& GetID(std::string key, int handle);

	//CPU�ň����摜�p
	const int& GetSoftID(std::string key);
	const int& GetSoftID(std::string key, int handle);

	//�}�X�N�摜�p
	const VecInt& GetMaskID(std::string key);
	const VecInt& GetMaskID(std::string f_name, std::string key);
	const VecInt& GetMaskID(std::string f_name, std::string key, Vector2 divSize, Vector2 divCnt);

	bool ExistID(std::string key);			//�摜�����݂��邩�ۂ�
	bool ExistSoftID(std::string key);		//�\�t�g�摜�����݂��邩�ۂ�

	Vector2 GetSize(const std::string& key);

private:
	ImageMng();
	~ImageMng();

	std::unordered_map<std::string, VecInt> imageMap_;			//�ʏ�摜�}�b�v
	std::unordered_map<std::string, int> softImageMap_;			//�\�t�g�摜�}�b�v
	std::unordered_map<std::string, VecInt> maskImageMap_;		//�}�X�N�摜�}�b�v

	void operator()(const ImageMng&) = delete;
	void operator=(const ImageMng&) = delete;
};

 