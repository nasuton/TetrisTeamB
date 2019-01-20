#ifndef SOUDNMANAGER_h
#define SOUNDMANAGER_h

#include "cocos2d.h"

class SoundManager
{
private:
	enum AudioType
	{
		BGM = 0,
		SE,
	};

	enum FadeType
	{
		NONE = 0,
		FADE_IN,
		FADE_OUT,
		FADE_IN_RESUME,
		FADE_OUT_PAUSE,
	};

	static SoundManager* instance;

	static cocos2d::Scheduler* managerSceheduler;

	//管理音源
	std::map<std::string, std::string> bgmList;
	std::map <std::string, std::string> seList;

	//SEをいくつ使用するか
	int seChunk[4];

	//BGMのID
	int bgmID;

	//現在流しているもと同じかどうか判断するため
	std::string bgmFileName;

	//拡張子判定用
	std::string bgmFileExt;

	//ゲッターとセッターを作る
	CC_SYNTHESIZE(std::string, audioListFile, AudioFile);

	//それぞれの音量
	float bgmVolume;
	float seVolume;

	//フェードで使う
	FadeType fadeCondition;
	float fadeVolumeFrom;
	float fadeVolumeTo;
	float fadeVolumeNow;
	float fadeTime;
	bool stopBGMreleaseFlg;
public:
	~SoundManager();

	static SoundManager* GetInstance();

	static void DeleteInstance();

	virtual void update(float delta);

	//管理ファイル(jsonファイル)を読み込む
//	bool ReadAudioFile(std::string jsonFileName);

	//すべてを解放する
	void ReleaseAll();

	//音量を初期化
	void InitVolume(float bgmVo, float seVo);

	//AudioEngineの解放
	void EndAudioEngine();

//--------------------------------------BGM--------------------------------------//
	//BGM再生
	int PlayBGM(std::string bgmName, float fade = 0.0f, bool loop = true);
	int PlayBGM(std::string bgmName, float fade, bool loop, float bgmVo);

	//BGM一時停止
	void PauseBGM(float fade = 0.0f);

	//BGMの停止
	void StopBGM(float fade = 0.0f, bool release = true);

	//BGMが再生中かどうか
	bool IsPlayingBGM();

	//BGMの音量変更
	void SetBGMVolume(float volume, bool save = true);

	//BGMの音量取得
	float GetBGMVolume();

	//BGMのキャッシュ解放
	void ReleaseBGM();

//--------------------------------------SE--------------------------------------//
	//SEの再生
	int PlaySE(std::string seName, int chunkNumber);
	int PlaySE(std::string seName, int chunkNumber, bool loop, float seVo);
	int PlaySE(std::string seName, bool loop = false);
	int PlaySE(std::string seName, bool loop, float seVo);

	//SEの停止
	void StopSE(int seID);

	//SEの音量変更
	void SetSEVolume(float seVo);

	//SEの音量取得
	float GetSEVolume();

	//SEのキャッシュを解放
	void ReleaseSE(std::string seName);

private:
	SoundManager();

	//拡張子の取得
	std::string GetExtension(AudioType type, std::string audioName);

	//pauseBGMの実行
	void PauseBGMEngine();

	//stopBGMの実行
	void StopBGMEngine(bool release = true);
};

#endif