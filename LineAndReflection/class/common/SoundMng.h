#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <array>
#include <utility>
#include "Vector2.h"

#define lpSoundMng SoundMng::GetInstance()

struct SoundInfo
{
	enum class Type
	{
		BGM,
		SE
	};

	std::unique_ptr<int> handle;
	long long currentPosition;
	Type type;
	int bufferNum;
	std::string path;

	SoundInfo(const long long& curPos, const Type& ty, const int& bufNum, const std::string& pth) :
		currentPosition(curPos), type(ty), bufferNum(bufNum), path(pth)
	{};
};

class SoundMng
{
public:
	static SoundMng& GetInstance(void)
	{
		static SoundMng s_Instance;
		return s_Instance;
	}

	void LoadSoundJSON(std::string path);			//�T�E���h�̐ݒ�t�@�C���̃��[�h

	void PlaySE(const std::string& key);			//SE�Đ�(�m�[�}���Đ����d���Đ���)
	void PlayLoopSE(const std::string& key);		//���[�v�p��SE�Đ�
	void PlayBGM(const std::string& key);			//BGM�Đ�(���[�v�Đ����r���I�Đ�)
	
	void StopSE(const std::string& key);			//SE��~
	void StopBGM(void);								//BGM��~
	
	void DeleteAllSound(void);						//�S�ẴT�E���h�̍폜

	const double& GetVolume(void)const;				//�{�����[���̎擾
	void SetVolume(double volume);					//�{�����[���̐ݒ�

	void LoadSound(const std::string& key);			//�w�肵���T�E���h�̃��[�h
	void LoadSoundAll(void);						//�S�ẴT�E���h�̃��[�h

private:
	SoundMng();
	~SoundMng();

	bool LoadSE(const std::string& key);			//SE�̃��[�h
	bool LoadBGM(const std::string& key);			//BGM�̃��[�h

	void ChangeVolume(void);							//�{�����[���̕ύX
	void ChangeVolume(const std::string& key);			//�{�����[���̕ύX

	bool CheckExistKey(const std::string& key)const;	//�L�[�����݂��邩

	std::unique_ptr<std::string> nowBGM_;				//���݂�BGM

	std::unordered_map<std::string, std::unique_ptr<SoundInfo>> soundMap_;		//�T�E���h�}�b�v

	void operator()(const SoundMng&) = delete;
	void operator=(const SoundMng&) = delete;

	double volume_;		//�{�����[��(0.0�`1.0)
};

