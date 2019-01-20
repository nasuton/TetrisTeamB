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

	//�Ǘ�����
	std::map<std::string, std::string> bgmList;
	std::map <std::string, std::string> seList;

	//SE�������g�p���邩
	int seChunk[4];

	//BGM��ID
	int bgmID;

	//���ݗ����Ă�����Ɠ������ǂ������f���邽��
	std::string bgmFileName;

	//�g���q����p
	std::string bgmFileExt;

	//�Q�b�^�[�ƃZ�b�^�[�����
	CC_SYNTHESIZE(std::string, audioListFile, AudioFile);

	//���ꂼ��̉���
	float bgmVolume;
	float seVolume;

	//�t�F�[�h�Ŏg��
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

	//�Ǘ��t�@�C��(json�t�@�C��)��ǂݍ���
//	bool ReadAudioFile(std::string jsonFileName);

	//���ׂĂ��������
	void ReleaseAll();

	//���ʂ�������
	void InitVolume(float bgmVo, float seVo);

	//AudioEngine�̉��
	void EndAudioEngine();

//--------------------------------------BGM--------------------------------------//
	//BGM�Đ�
	int PlayBGM(std::string bgmName, float fade = 0.0f, bool loop = true);
	int PlayBGM(std::string bgmName, float fade, bool loop, float bgmVo);

	//BGM�ꎞ��~
	void PauseBGM(float fade = 0.0f);

	//BGM�̒�~
	void StopBGM(float fade = 0.0f, bool release = true);

	//BGM���Đ������ǂ���
	bool IsPlayingBGM();

	//BGM�̉��ʕύX
	void SetBGMVolume(float volume, bool save = true);

	//BGM�̉��ʎ擾
	float GetBGMVolume();

	//BGM�̃L���b�V�����
	void ReleaseBGM();

//--------------------------------------SE--------------------------------------//
	//SE�̍Đ�
	int PlaySE(std::string seName, int chunkNumber);
	int PlaySE(std::string seName, int chunkNumber, bool loop, float seVo);
	int PlaySE(std::string seName, bool loop = false);
	int PlaySE(std::string seName, bool loop, float seVo);

	//SE�̒�~
	void StopSE(int seID);

	//SE�̉��ʕύX
	void SetSEVolume(float seVo);

	//SE�̉��ʎ擾
	float GetSEVolume();

	//SE�̃L���b�V�������
	void ReleaseSE(std::string seName);

private:
	SoundManager();

	//�g���q�̎擾
	std::string GetExtension(AudioType type, std::string audioName);

	//pauseBGM�̎��s
	void PauseBGMEngine();

	//stopBGM�̎��s
	void StopBGMEngine(bool release = true);
};

#endif