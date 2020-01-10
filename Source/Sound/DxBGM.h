#pragma once

#include "../BaseObject/BaseObject.h"
#include <strmif.h>
#include <control.h>
#include <uuids.h>

#pragma comment(lib,"strmiids.lib")

class DxFade{

public:
	float timeSecond, timeEnd, volSecond, deltaTime;

};

class DxBGM : public BaseObject{

public:
	DxBGM();
	DxBGM(LPCTSTR fileName);
	~DxBGM();

	virtual void Init() override;
	virtual void Release() override;
	virtual bool Update() override;

	void Load(LPCTSTR fileName);
	void Play(bool loop);
	void Stop();

	void SetVolume(LONG volume);
	void Fade(DWORD endTime, LONG volume);

private:
	IGraphBuilder* pBuilder;
	IMediaControl* pMediaCtrl;
	IMediaSeeking* pMediaSeeking;
	IBasicAudio* pBasicAudio;

	bool isLoop;
	bool isFading;

	float timeSecond, timeEnd, volSecond, deltaTime;

};