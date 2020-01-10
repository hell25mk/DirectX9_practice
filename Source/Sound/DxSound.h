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
	/// wav�t�@�C����ǂݍ���
	/// </summary>
	/// <param name="fileName">�ǂݍ��ރt�@�C���̊K�w</param>
	/// <returns>�ǂݍ��݂����������ꍇtrue</returns>
	bool Load(LPCTSTR fileName);
	
	/// <summary>
	/// �������Đ�����
	/// </summary>
	/// <param name="isLoop">���[�v�Đ����邩�ǂ���(�w�肪�����ꍇfalse)</param>
	void Play(bool isLoop = false);

	/// <summary>
	/// �������~����
	/// </summary>
	void Stop();

	/// <summary>
	/// ���ʂ�ύX����
	/// </summary>
	/// <param name="volume">����(DSBVOLUME_MIN(-10000)�`DSBVOLUME_MAX(0)�̊�)</param>
	void SetVolume(LONG volume);

	/// <summary>
	/// ���̏o��ʒu��ύX����
	/// </summary>
	/// <param name="pan">�ʒu</param>
	void SetPan(LONG pan);

	void EnableDeleteEnd();

private:
	/// <summary>
	/// �V�K�X���b�h�ɗp����
	/// </summary>
	/// <param name="param"></param>
	/// <returns></returns>
	static DWORD WINAPI NotifyFunction(LPVOID param);

private:
	static LPDIRECTSOUND8 pDxSound;
	LPDIRECTSOUNDBUFFER pDxSoundBuffer;
	LPDIRECTSOUNDNOTIFY pDxSoundNotify;		//�Đ��I�����֒m
	HANDLE hEvent;

};

