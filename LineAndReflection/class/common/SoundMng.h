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

	void LoadSoundJSON(std::string path);			//サウンドの設定ファイルのロード

	void PlaySE(const std::string& key);			//SE再生(ノーマル再生かつ重複再生可)
	void PlayLoopSE(const std::string& key);		//ループ用のSE再生
	void PlayBGM(const std::string& key);			//BGM再生(ループ再生かつ排他的再生)
	
	void StopSE(const std::string& key);			//SE停止
	void StopBGM(void);								//BGM停止
	
	void DeleteAllSound(void);						//全てのサウンドの削除

	const double& GetVolume(void)const;				//ボリュームの取得
	void SetVolume(double volume);					//ボリュームの設定

	void LoadSound(const std::string& key);			//指定したサウンドのロード
	void LoadSoundAll(void);						//全てのサウンドのロード

private:
	SoundMng();
	~SoundMng();

	bool LoadSE(const std::string& key);			//SEのロード
	bool LoadBGM(const std::string& key);			//BGMのロード

	void ChangeVolume(void);							//ボリュームの変更
	void ChangeVolume(const std::string& key);			//ボリュームの変更

	bool CheckExistKey(const std::string& key)const;	//キーが存在するか

	std::unique_ptr<std::string> nowBGM_;				//現在のBGM

	std::unordered_map<std::string, std::unique_ptr<SoundInfo>> soundMap_;		//サウンドマップ

	void operator()(const SoundMng&) = delete;
	void operator=(const SoundMng&) = delete;

	double volume_;		//ボリューム(0.0～1.0)
};

