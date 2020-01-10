#include "DxInput.h"

using namespace Gamepad;

DxInput::DxInput() :
	pInput(NULL),pKeyDevice(NULL),inputKeyData(),lastKeyData(),
	pPadDevice(),inputPadData(),lastPadData(){
}

DxInput::~DxInput() {

	ReleaseObject(pKeyDevice);
	ReleaseObject(pInput);

}

void DxInput::Init() {

	//すでに初期化済みなら処理を終える
	if (pInput != NULL) {
		return;
	}

#pragma region キーボードの作成
	HRESULT hr;

	//インターフェイスの取得
	hr = DirectInput8Create(
		windowObject.hInstance,		//ソフトのインスタンスハンドル
		DIRECTINPUT_VERSION,		//DirectInputのバージョン
		IID_IDirectInput8,			//取得するインターフェイスタイプ
		(LPVOID*)&pInput,			//インターフェイスの格納先
		NULL						//COM集成の制御オブジェクト(使わないのでNULL)
		);

	if (FAILED(hr)) {
		MessageBox(NULL, _T("DirectInputの初期化に失敗しました"), _T("エラー"), MB_OK);

		return;
	}

	hr = pInput->CreateDevice(
		GUID_SysKeyboard,			//受け付ける入力デバイス
		&pKeyDevice,				//IDirectInputDevice8格納先
		NULL						//COM集成の制御オブジェクト(使わないのでNULL)
	);

	if (FAILED(hr)) {
		MessageBox(NULL, _T("DirectInputDeviceの初期化に失敗しました"), _T("エラー"), MB_OK);

		return;
	}

	pKeyDevice->SetDataFormat(&c_dfDIKeyboard);		//データフォーマットの設定
	pKeyDevice->SetCooperativeLevel(windowObject.hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);	//協調モードの設定

	ZeroMemory(inputKeyData, Key_ArraySize);				//キーバッファの初期化
#pragma endregion

#pragma region ゲームパッドの作成
	//コールバック関数に転送したいデータを格納
	EnumData enumData;
	enumData.pInput = pInput;
	enumData.dpPadDevice = &pPadDevice;

	pInput->EnumDevices(
		DI8DEVCLASS_GAMECTRL,			//ゲームコントローラーが対象
		EnumJoypad,						//列挙する関数
		&enumData,						//列挙関数に渡したいデータはここに入れる
		DIEDFL_ATTACHEDONLY				//インストール・接続済みのデバイスのみ取得
	);

	if (pPadDevice) {
		//アナログキーのデータを設定
		/*-------------------------------------------------------------------------------------------------------------
			2番目の引数にpPadDeviceを指定しておくとEnumObject関数のpvRefに、このpPadDeviceが格納されるようになるため、
			pPadDeviceをstaticやグローバルにしてなくて済む
		---------------------------------------------------------------------------------------------------------------*/
		pPadDevice->EnumObjects(EnumObject, pPadDevice, DIDFT_AXIS);
		pPadDevice->SetCooperativeLevel(windowObject.hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		//ゲームパッドの入力情報はDIJOYSTATE2に格納されるのでデータフォーマットに指定
		hr = pPadDevice->SetDataFormat(&c_dfDIJoystick2);

		if (FAILED(hr)) {
			ReleaseObject(pPadDevice);
		}
	}
#pragma endregion


}

BOOL CALLBACK DxInput::EnumJoypad(const DIDEVICEINSTANCE* pInstance, LPVOID pContext) {

	EnumData* enumData = (EnumData*)pContext;

	HRESULT hr;

	hr = enumData->pInput->CreateDevice(pInstance->guidInstance, enumData->dpPadDevice, NULL);

	if (FAILED(hr)) {
		return DIENUM_CONTINUE;		//デバイス作成ができないので列挙を続ける
	}

	return DIENUM_STOP;
}

BOOL CALLBACK DxInput::EnumObject(LPCDIDEVICEOBJECTINSTANCE pInstance, LPVOID pvRef) {

	DIPROPRANGE range;

	range.diph.dwSize = sizeof(DIPROPRANGE);
	range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	range.diph.dwObj = pInstance->dwType;					//ボタンやスティックのデータ
	range.diph.dwHow = DIPH_BYID;							//タイプで取得することを指定
	range.lMin = AnalogInput_Min;							//値の最小値
	range.lMax = AnalogInput_Max;							//値の最大値

	LPDIRECTINPUTDEVICE8 pInputDev = (LPDIRECTINPUTDEVICE8)pvRef;
	pInputDev->SetProperty(DIPROP_RANGE, &range.diph);

	return DIENUM_CONTINUE;
}

bool DxInput::Update() {

	if (pKeyDevice) {
		pKeyDevice->Acquire();	//入力の受付開始
		pKeyDevice->GetDeviceState(Key_ArraySize, inputKeyData);	//データを取得
	}

	if (pPadDevice) {
		pPadDevice->Poll();		//ジョイパッドデータ取得
		pPadDevice->Acquire();

		memcpy(&lastPadData, &inputPadData, sizeof(DIJOYSTATE2));
		pPadDevice->GetDeviceState(sizeof(DIJOYSTATE2), &inputPadData);
	}

	return true;
}

#pragma region キーボード入力

/// <summary>
/// 現在そのキーが押されているかを返す
/// </summary>
/// <param name="key">キーコード</param>
/// <returns>押されている場合はtrue</returns>
bool DxInput::IsKeyDown(int key) {

	if (!pKeyDevice) {
		return false;
	}

	//最上位1ビットに押されているかのデータが格納されている
	//最下位1ビットにはトグル(オン・オフ)の状態が格納されている
	return (inputKeyData[key] & 0x80) ? true : false;
}

/// <summary>
/// 押されたキーが一回目
/// </summary>
/// <param name="key">キーコード</param>
/// <returns>現在押されていて直前に押されていない場合true</returns>
bool DxInput::IsKeyPressed(int key) {

	if (!pKeyDevice) {
		return false;
	}

	return ((inputKeyData[key] & 0x80) && !(lastKeyData[key] & 0x800)) ? true : false;
}

/// <summary>
/// 現在押されておらず直前に押されている場合
/// </summary>
/// <param name="key">キーコード</param>
/// <returns>現在押されておらず直前に押されている場合true</returns>
bool DxInput::IsKeyReleased(int key) {

	if (!pKeyDevice) {
		return false;
	}
	
	return (!(inputKeyData[key] & 0x80) && (lastKeyData[key] & 0x800)) ? true : false;
}

#pragma endregion

#pragma region ゲームパッド入力

BYTE DxInput::GetPovPosition() {

	//デジタル入力の判断
	//rgdwPOV[0]に押された方向が角度*100で格納されている
	//真上0で時計回りに36000の範囲
	switch (inputPadData.rgdwPOV[0]) {
	case 0 * 100:
		return Pad_Up;
	case 45 * 100:
		return Pad_Up | Pad_Right;
	case 90 * 100:
		return Pad_Right;
	case 135 * 100:
		return Pad_Right | Pad_Down;
	case 180 * 100:
		return Pad_Down;
	case 225 * 100:
		return Pad_Down | Pad_Left;
	case 270 * 100:
		return Pad_Left;
	case 315 * 100:
		return Pad_Left | Pad_Up;
	}

	//アナログ入力の判断
	BYTE result = 0x0;

	if (inputPadData.lX > (AnalogInput_Max / 2)) {
		result |= Pad_Right;
	} else if (inputPadData.lX < (AnalogInput_Min / 2)) {
		result |= Pad_Left;
	}
	if (inputPadData.lY > (AnalogInput_Max / 2)) {
		result |= Pad_Down;
	} else if (inputPadData.lY < (AnalogInput_Min / 2)) {
		result |= Pad_Up;
	}

	return result;
}

bool DxInput::IsButtonDown(int pos) {

	if (!pPadDevice) {
		return false;
	}

	return inputPadData.rgbButtons[pos];
}

bool DxInput::IsButtonPressed(int pos) {

	if (!pPadDevice) {
		return false;
	}

	return (inputPadData.rgbButtons[pos] && lastPadData.rgbButtons[pos]) ? true : false;
}

bool DxInput::IsButtonReleased(int pos) {

	if (!pPadDevice) {
		return false;
	}

	return (!inputPadData.rgbButtons[pos] && lastPadData.rgbButtons[pos]) ? true : false;
}

#pragma endregion

#pragma region キーボードとゲームパッド両対応(要確認)

bool DxInput::IsInputDown(int key, int pos) {

	return IsKeyDown(key) || (GetPovPosition() & pos);
}

bool DxInput::IsInputPressed(int key, int pos) {

	return IsKeyPressed(key) || IsButtonPressed(pos);
}

bool DxInput::IsInputReleased(int key, int pos) {

	return IsKeyReleased(key) || IsButtonReleased(pos);
}

#pragma endregion

