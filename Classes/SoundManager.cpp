#include "SoundManager.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;
using namespace experimental;

SoundManager* SoundManager::instance = nullptr;
Scheduler*  SoundManager::managerSceheduler = nullptr;

SoundManager::SoundManager()
	:bgmID(-1)
	,bgmFileName("")
	,bgmFileExt("")
	,bgmVolume(0.5f)
	,seVolume(0.5f)
	,fadeCondition(FadeType::NONE)
	,fadeVolumeFrom(0.0f)
	,fadeVolumeTo(0.0f)
	,fadeVolumeNow(0.0f)
	,fadeTime(0.0f)
	,stopBGMreleaseFlg(true)
{
	for (int i = 0; i < sizeof(seChunk) / sizeof(seChunk[0]); i++)
	{
		seChunk[i] = AudioEngine::INVALID_AUDIO_ID;
	}
}

SoundManager::~SoundManager()
{
	CC_SAFE_RELEASE_NULL(managerSceheduler);
}

SoundManager* SoundManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SoundManager();

		managerSceheduler = Director::getInstance()->getScheduler();
		managerSceheduler->retain();
		managerSceheduler->scheduleUpdate(instance, 0, false);
	}

	return instance;
}

void SoundManager::DeleteInstance()
{
	if (instance != nullptr)
	{
		delete instance;
	}

	instance = nullptr;
}

void SoundManager::update(float delta)
{
	//fadeするのに使用
	switch (fadeCondition)
	{
	case FadeType::FADE_IN:
	case FadeType::FADE_IN_RESUME:
		if (fadeTime == 0.0f)
		{
			fadeTime = 0.1f;
		}

		fadeVolumeNow += (delta * (fadeVolumeTo - fadeVolumeFrom)) / fadeTime;

		if (fadeVolumeTo <= fadeVolumeNow)
		{
			fadeVolumeNow = fadeVolumeTo;
			fadeVolumeFrom = fadeVolumeTo;
			fadeCondition = FadeType::NONE;
		}

		this->SetBGMVolume(fadeVolumeNow, false);

		break;

	case FadeType::FADE_OUT:
	case FadeType::FADE_OUT_PAUSE:
		if (fadeTime == 0.0f)
		{
			fadeTime = 0.1f;
		}

		fadeVolumeNow += (delta * (fadeVolumeTo - fadeVolumeFrom)) / fadeTime;

		if (fadeVolumeNow <= fadeVolumeTo)
		{
			fadeVolumeNow = fadeVolumeTo;
			fadeVolumeFrom = fadeVolumeTo;

			if (fadeCondition == FadeType::FADE_OUT)
			{
				this->StopBGM(0.0f, stopBGMreleaseFlg);
			}
			else if (fadeCondition == FadeType::FADE_OUT_PAUSE)
			{
				this->PauseBGM(0.0f);
			}
			fadeCondition = FadeType::NONE;
		}

		this->SetBGMVolume(fadeVolumeNow, false);

		break;
	default:
		break;
	}
}

void SoundManager::ReleaseAll()
{
	AudioEngine::uncacheAll();
}

void SoundManager::InitVolume(float bgmVo, float seVo)
{
	bgmVolume = bgmVo;

	seVolume = seVo;
}

void SoundManager::EndAudioEngine()
{
	AudioEngine::end();
}

int SoundManager::PlayBGM(std::string bgmName, float fade, bool loop)
{
	return this->PlayBGM(bgmName, fade, loop, bgmVolume);
}

int SoundManager::PlayBGM(std::string bgmName, float fade, bool loop, float bgmVo)
{
	int soundID = AudioEngine::INVALID_AUDIO_ID;

	std::string fileName = this->GetExtension(AudioType::BGM, bgmName);

	if (fileName == "")
	{
		return soundID;
	}

	//すでに同じのが流れていた場合、なにもしないで返す
	if (bgmFileName == bgmName && AudioEngine::getState(bgmID) == AudioEngine::AudioState::PLAYING)
	{
		return bgmID;
	}

	bgmFileExt = fileName.substr(fileName.size() - 4, 4);

	this->StopBGM();

	if (fade != 0.0f)
	{
		fadeCondition = FadeType::FADE_IN;
		fadeVolumeNow = 0.0f;
		fadeVolumeFrom = 0.0f;
		fadeTime = fade;
	}
	else
	{
		fadeCondition = FadeType::NONE;
		fadeVolumeNow = bgmVo;
	}

	fadeVolumeTo = bgmVo;

	bgmID = AudioEngine::play2d(fileName, loop, bgmVo);

	//ループの設定
	if (loop)
	{
		AudioEngine::setFinishCallback(bgmID,
			[this, loop, bgmVo](int audioId, std::string file) {
			this->StopBGM(0.0f, false);
			bgmID = PlayBGM(bgmFileName, 0.0f, loop, bgmVo);
		});
	}

	bgmFileName = bgmName;

	return bgmID;
}

void SoundManager::PauseBGM(float fade)
{
	fadeVolumeTo = 0.0f;

	if (fade != 0.0f)
	{
		fadeCondition = FadeType::FADE_OUT_PAUSE;
		fadeVolumeNow = bgmVolume;
		fadeVolumeFrom = bgmVolume;
		fadeTime = fade;
	}
	else
	{
		fadeCondition = FadeType::NONE;
		fadeVolumeNow = 0.0f;

		this->PauseBGMEngine();
	}
}

void SoundManager::StopBGM(float fade, bool release)
{
	fadeVolumeTo = 0.0f;

	if (fade != 0.0f)
	{
		fadeCondition = FadeType::FADE_OUT;
		fadeVolumeNow = bgmVolume;
		fadeVolumeFrom = bgmVolume;
		fadeTime = fade;
		stopBGMreleaseFlg = release;
	}
	else
	{
		fadeCondition = FadeType::NONE;
		fadeVolumeNow = 0.0f;
		this->StopBGMEngine(release);
	}
}

bool SoundManager::IsPlayingBGM()
{
	if (bgmFileName == "")
	{
		return false;
	}

	std::string fileName = bgmFileName + bgmFileExt;

	AudioEngine::AudioState state = AudioEngine::getState(bgmID);
	if (state == AudioEngine::AudioState::PLAYING)
	{
		return true;
	}

	return false;
}

void SoundManager::SetBGMVolume(float volume, bool save)
{
	if (save)
	{
		bgmVolume = volume;
	}

	AudioEngine::setVolume(bgmID, volume);
}

float SoundManager::GetBGMVolume()
{
	return bgmVolume;
}

void SoundManager::ReleaseBGM()
{
	auto fileName = bgmFileName + bgmFileExt;
	AudioEngine::uncache(fileName);
}

int SoundManager::PlaySE(std::string seName, int chunkNumber)
{
	return this->PlaySE(seName, chunkNumber, false, seVolume);
}

int SoundManager::PlaySE(std::string seName, int chunkNumber, bool loop, float seVo)
{
	int soundID = AudioEngine::INVALID_AUDIO_ID;

	bool chunkFlag = false;

	std::string fileName = GetExtension(AudioType::SE, seName);

	if (fileName == "")
	{
		return soundID;
	}

	if (0 <= chunkNumber && chunkNumber < (sizeof(seChunk) / sizeof(seChunk[0])))
	{
		chunkFlag = true;

		this->StopSE(seChunk[chunkNumber]);
	}

	soundID = AudioEngine::play2d(seName, loop, seVo);

	if (chunkFlag)
	{
		seChunk[chunkNumber] = soundID;
	}

	return soundID;
}

int SoundManager::PlaySE(std::string seName, bool loop)
{
	return this->PlaySE(seName, loop, seVolume);
}

int SoundManager::PlaySE(std::string seName, bool loop, float seVo)
{
	return this->PlaySE(seName, -1, loop, seVo);
}

void SoundManager::StopSE(int seID)
{
	AudioEngine::stop(seID);
}

void SoundManager::SetSEVolume(float seVo)
{
	seVolume = seVo;
}

float SoundManager::GetSEVolume()
{
	return seVolume;
}

void SoundManager::ReleaseSE(std::string seName)
{
	std::string fileName = GetExtension(AudioType::SE, seName);

	if (fileName == "")
	{
		return;
	}

	AudioEngine::uncache(fileName);
}

std::string SoundManager::GetExtension(AudioType type, std::string audioName)
{
	std::string extension = ".m4a";

	if (audioListFile != "")
	{
		if (type == AudioType::BGM)
		{
			if (bgmList.count(audioName) != 0)
			{
				audioName = bgmList[audioName];
			}
		}
		else if (type == AudioType::SE)
		{
			if (seList.count(audioName) != 0)
			{
				audioName = seList[audioName];
			}
		}
	}

	if (audioName.find_last_of(".") != std::string::npos)
	{
		if (FileUtils::getInstance()->isFileExist(audioName))
		{
			return audioName;
		}
		else
		{
			return "";
		}
	}

	if (FileUtils::getInstance()->isFileExist(audioName + extension))
	{
		return audioName + extension;
	}

	log("file not found %s.", audioName.c_str());
	return audioName;
}

void SoundManager::PauseBGMEngine()
{
	AudioEngine::pause(bgmID);
}

void SoundManager::StopBGMEngine(bool release)
{
	AudioEngine::stop(bgmID);

	if (release)
	{
		this->ReleaseBGM();
	}

	bgmID = AudioEngine::INVALID_AUDIO_ID;
	bgmFileName = "";
	bgmFileExt = "";
}