#pragma once

#include "../BaseObject/BaseObject.h"

//���p����DirectInput�o�[�W�����錾
//DirectInput8���g�p
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//DirectInput�Ɋ֌W���郉�C�u�����̃����N�錾
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/// <summary>
/// �Q�[���p�b�h�p
/// </summary>
namespace Gamepad {

	/// <summary>
	/// �p�b�h�̕����L�[�p
	/// </summary>
	constexpr int Pad_Up = 0x1;
	constexpr int Pad_Right = 0x2;
	constexpr int Pad_Down = 0x4;
	constexpr int Pad_Left = 0x8;

	constexpr int Pad_Stick[] = {
		Pad_Up,
		Pad_Up | Pad_Right,
		Pad_Right,
		Pad_Right | Pad_Down,
		Pad_Down,
		Pad_Down | Pad_Left,
		Pad_Left,
		Pad_Left | Pad_Up
	};

	/// <summary>
	/// �A�i���O���͈͂̔�
	/// </summary>
	constexpr LONG AnalogInput_Min = -10;
	constexpr LONG AnalogInput_Max = +10;

}

constexpr unsigned int Key_ArraySize = 256;

class EnumData {
public:
	LPDIRECTINPUT8 pInput;					//�f�o�C�X���쐬���邽�߂̃C���^�[�t�F�C�X
	LPDIRECTINPUTDEVICE8* dpPadDevice;		//�g�p����f�o�C�X���i�[����_�u���|�C���^
};

class DxInput : public BaseObject{

public:
	DxInput();
	~DxInput();
	virtual void Init() override;
	virtual bool Update() override;

	bool IsKeyDown(int key);
	bool IsKeyPressed(int key);
	bool IsKeyReleased(int key);

	BYTE GetPovPosition();
	bool IsButtonDown(int pos);
	bool IsButtonPressed(int pos);
	bool IsButtonReleased(int pos);

	bool IsInputDown(int key, int pos);
	bool IsInputPressed(int key, int pos);
	bool IsInputReleased(int key, int pos);

private:
	static BOOL CALLBACK EnumJoypad(const DIDEVICEINSTANCE* pInstance, LPVOID pContext);
	static BOOL CALLBACK EnumObject(LPCDIDEVICEOBJECTINSTANCE pInstance, LPVOID pvRef);

private:
	LPDIRECTINPUT8 pInput;
	LPDIRECTINPUTDEVICE8 pKeyDevice;
	BYTE inputKeyData[Key_ArraySize];
	BYTE lastKeyData[Key_ArraySize];

	LPDIRECTINPUTDEVICE8 pPadDevice;
	DIJOYSTATE2 inputPadData, lastPadData;

};

