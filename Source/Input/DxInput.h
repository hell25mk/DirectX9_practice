#pragma once

#include "../BaseObject/BaseObject.h"

//利用するDirectInputバージョン宣言
//DirectInput8を使用
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//DirectInputに関係するライブラリのリンク宣言
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

/// <summary>
/// ゲームパッド用
/// </summary>
namespace Gamepad {

	/// <summary>
	/// パッドの方向キー用
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
	/// アナログ入力の範囲
	/// </summary>
	constexpr LONG AnalogInput_Min = -10;
	constexpr LONG AnalogInput_Max = +10;

}

constexpr unsigned int Key_ArraySize = 256;

class EnumData {
public:
	LPDIRECTINPUT8 pInput;					//デバイスを作成するためのインターフェイス
	LPDIRECTINPUTDEVICE8* dpPadDevice;		//使用するデバイスを格納するダブルポインタ
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

