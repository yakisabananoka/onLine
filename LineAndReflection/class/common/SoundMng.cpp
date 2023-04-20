#include <algorithm>
#include <fstream>
#include <DxLib.h>
#include "SoundMng.h"
#include "../../parser/rapidjson/document.h"
#include "../../parser/rapidjson/istreamwrapper.h"
#include "../../_debug/_DebugConOut.h"

namespace soundMng_const
{
	constexpr double defVolume = 0.1;
}

using namespace soundMng_const;

void SoundMng::LoadSoundJSON(std::string path)
{
	std::ifstream ifs(path);

	//ÉpÅ[ÉX
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document soundDoc;

	soundDoc.ParseStream(isw);

	const auto& soundList = soundDoc["soundList"];

	for (auto itr = soundList.Begin(); itr != soundList.End(); ++itr)
	{
		const auto& soundObj = itr->GetObj();

		long long currentPosition = soundObj["currentPosition"].GetInt();
		SoundInfo::Type type = std::string(soundObj["type"].GetString()) == "bgm" ? SoundInfo::Type::BGM : SoundInfo::Type::SE;
		int bufferNum = soundObj["bufferNum"].GetInt();
		std::string pth = soundObj["path"].GetString();

		auto ptr = std::make_unique<SoundInfo>(currentPosition, type, bufferNum, pth);
		soundMap_.emplace(soundObj["key"].GetString(), std::move(ptr));
	}
}

void SoundMng::PlaySE(const std::string& key)
{
	if (!CheckExistKey(key))
	{
		return;
	}

	const auto& handle = *(soundMap_[key]->handle);

	SetCurrentPositionSoundMem(soundMap_[key]->currentPosition, handle);
	ChangeVolume(key);
	PlaySoundMem(handle, DX_PLAYTYPE_BACK, false);
}

void SoundMng::PlayLoopSE(const std::string& key)
{
	if (!CheckExistKey(key))
	{
		return;
	}

	const auto& handle = *(soundMap_[key]->handle);

	SetCurrentPositionSoundMem(soundMap_[key]->currentPosition, handle);
	ChangeVolume(key);
	PlaySoundMem(handle, DX_PLAYTYPE_LOOP, false);
}

void SoundMng::PlayBGM(const std::string& key)
{
	if (nowBGM_ != nullptr)
	{
		if (*nowBGM_ == key)
		{
			return;
		}
	}

	if (!CheckExistKey(key))
	{
		return;
	}

	const auto& handle = *(soundMap_[key]->handle);

	StopBGM();
	SetCurrentPositionSoundMem(soundMap_[key]->currentPosition, handle);
	ChangeVolume(key);
	PlaySoundMem(handle, DX_PLAYTYPE_LOOP, false);
	nowBGM_ = std::make_unique<std::string>(key);
}

void SoundMng::StopSE(const std::string& key)
{
	if (!CheckExistKey(key))
	{
		return;
	}

	const auto& handle = *(soundMap_[key]->handle);

	if (CheckSoundMem(handle) != 1)
	{
		return;
	}

	StopSoundMem(handle);
}

void SoundMng::StopBGM(void)
{
	if (nowBGM_ == nullptr)
	{
		return;
	}
	StopSoundMem(*(soundMap_[*nowBGM_]->handle));
	nowBGM_ = nullptr;
}

void SoundMng::DeleteAllSound(void)
{
	for (auto& handle : soundMap_)
	{
		DeleteSoundMem(*(handle.second->handle));
	}
}

const double& SoundMng::GetVolume(void) const
{
	return volume_;
}

void SoundMng::SetVolume(double volume)
{
	volume_ = std::clamp(volume, 0.0, 1.0);
	ChangeVolume();
}

void SoundMng::LoadSound(const std::string& key)
{
	if (!soundMap_.count(key))
	{
		return;
	}

	if (soundMap_.at(key)->handle != nullptr)
	{
		return;
	}

	soundMap_[key]->type == SoundInfo::Type::BGM ? LoadBGM(key) : LoadSE(key);
}

void SoundMng::LoadSoundAll(void)
{
	for (const auto& sound : soundMap_)
	{
		LoadSound(sound.first);
	}

	ChangeVolume();
}

SoundMng::SoundMng()
{
	volume_ = defVolume;
}

SoundMng::~SoundMng()
{
}

bool SoundMng::LoadSE(const std::string& key)
{
	TRACE("SEÇÃì«Ç›çûÇ›\n");
	
	auto& info = *(soundMap_[key]);
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
	info.handle = std::make_unique<int>(LoadSoundMem(info.path.c_str(), info.bufferNum));
	//ChangeVolumeSoundMem(64, soundMap_[key]);

	if (*(soundMap_[key]->handle) == -1)
	{
		TRACE("ì«Ç›çûÇ›é∏îs\n");
		return false;
	}

	return true;
}

bool SoundMng::LoadBGM(const std::string& key)
{
	TRACE("BGMÇÃì«Ç›çûÇ›\n");
	
	auto& info = *(soundMap_[key]);
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	info.handle = std::make_unique<int>(LoadSoundMem(info.path.c_str()));
	//ChangeVolumeSoundMem(64, soundMap_[key]);

	if (*(soundMap_[key]->handle) == -1)
	{
		TRACE("ì«Ç›çûÇ›é∏îs\n");
		return false;
	}

	return true;
}

void SoundMng::ChangeVolume(void)
{
	for (const auto& sound : soundMap_)
	{
		ChangeVolume(sound.first);
	}
}

void SoundMng::ChangeVolume(const std::string& key)
{
	if (!CheckExistKey(key))
	{
		return;
	}

	int vol = std::clamp(static_cast<int>(255.0 * volume_), 0, 255);
	ChangeVolumeSoundMem(vol, *(soundMap_[key]->handle));
}

bool SoundMng::CheckExistKey(const std::string& key) const
{
	if (!soundMap_.count(key))
	{
		return false;
	}

	if (soundMap_.at(key)->handle == nullptr)
	{
		return false;
	}

	return true;
}
