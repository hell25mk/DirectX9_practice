#pragma once

#include "../BaseObject/BaseObject.h"
#include <dsound.h>

#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"dxguid.lib")

class DxSound : public BaseObject {

public:
	DxSound();
	DxSound(LPCTSTR fileName);
	DxSound(const DxSound& sound);
	DxSound& operator=(const DxSound& sound);
	~DxSound();

	void CreateDirectSound();
	void ReleaseDirectSound();

	/// <summary>
	/// wavファイルを読み込む
	/// </summary>
	/// <param name="fileName">読み込むファイルの階層</param>
	/// <returns>読み込みが成功した場合true</returns>
	bool Load(LPCTSTR fileName);
	
	/// <summary>
	/// 音声を再生する
	/// </summary>
	/// <param name="isLoop">ループ再生するかどうか(指定が無い場合false)</param>
	void Play(bool isLoop = false);

	/// <summary>
	/// 音声を停止する
	/// </summary>
	void Stop();

	/// <summary>
	/// 音量を変更する
	/// </summary>
	/// <param name="volume">音量(DSBVOLUME_MIN(-10000)～DSBVOLUME_MAX(0)の間)</param>
	void SetVolume(LONG volume);

	/// <summary>
	/// 音の出る位置を変更する
	/// </summary>
	/// <param name="pan">位置</param>
	void SetPan(LONG pan);

	void EnableDeleteEnd();

private:
	/// <summary>
	/// 新規スレッドに用いる
	/// </summary>
	/// <param name="param"></param>
	/// <returns></returns>
	static DWORD WINAPI NotifyFunction(LPVOID param);

private:
	static LPDIRECTSOUND8 pDxSound;
	LPDIRECTSOUNDBUFFER pDxSoundBuffer;
	LPDIRECTSOUNDNOTIFY pDxSoundNotify;		//再生終了を関知
	HANDLE hEvent;

};

