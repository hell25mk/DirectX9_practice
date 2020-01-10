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

	//���łɏ������ς݂Ȃ珈�����I����
	if (pInput != NULL) {
		return;
	}

#pragma region �L�[�{�[�h�̍쐬
	HRESULT hr;

	//�C���^�[�t�F�C�X�̎擾
	hr = DirectInput8Create(
		windowObject.hInstance,		//�\�t�g�̃C���X�^���X�n���h��
		DIRECTINPUT_VERSION,		//DirectInput�̃o�[�W����
		IID_IDirectInput8,			//�擾����C���^�[�t�F�C�X�^�C�v
		(LPVOID*)&pInput,			//�C���^�[�t�F�C�X�̊i�[��
		NULL						//COM�W���̐���I�u�W�F�N�g(�g��Ȃ��̂�NULL)
		);

	if (FAILED(hr)) {
		MessageBox(NULL, _T("DirectInput�̏������Ɏ��s���܂���"), _T("�G���["), MB_OK);

		return;
	}

	hr = pInput->CreateDevice(
		GUID_SysKeyboard,			//�󂯕t������̓f�o�C�X
		&pKeyDevice,				//IDirectInputDevice8�i�[��
		NULL						//COM�W���̐���I�u�W�F�N�g(�g��Ȃ��̂�NULL)
	);

	if (FAILED(hr)) {
		MessageBox(NULL, _T("DirectInputDevice�̏������Ɏ��s���܂���"), _T("�G���["), MB_OK);

		return;
	}

	pKeyDevice->SetDataFormat(&c_dfDIKeyboard);		//�f�[�^�t�H�[�}�b�g�̐ݒ�
	pKeyDevice->SetCooperativeLevel(windowObject.hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);	//�������[�h�̐ݒ�

	ZeroMemory(inputKeyData, Key_ArraySize);				//�L�[�o�b�t�@�̏�����
#pragma endregion

#pragma region �Q�[���p�b�h�̍쐬
	//�R�[���o�b�N�֐��ɓ]���������f�[�^���i�[
	EnumData enumData;
	enumData.pInput = pInput;
	enumData.dpPadDevice = &pPadDevice;

	pInput->EnumDevices(
		DI8DEVCLASS_GAMECTRL,			//�Q�[���R���g���[���[���Ώ�
		EnumJoypad,						//�񋓂���֐�
		&enumData,						//�񋓊֐��ɓn�������f�[�^�͂����ɓ����
		DIEDFL_ATTACHEDONLY				//�C���X�g�[���E�ڑ��ς݂̃f�o�C�X�̂ݎ擾
	);

	if (pPadDevice) {
		//�A�i���O�L�[�̃f�[�^��ݒ�
		/*-------------------------------------------------------------------------------------------------------------
			2�Ԗڂ̈�����pPadDevice���w�肵�Ă�����EnumObject�֐���pvRef�ɁA����pPadDevice���i�[�����悤�ɂȂ邽�߁A
			pPadDevice��static��O���[�o���ɂ��ĂȂ��čς�
		---------------------------------------------------------------------------------------------------------------*/
		pPadDevice->EnumObjects(EnumObject, pPadDevice, DIDFT_AXIS);
		pPadDevice->SetCooperativeLevel(windowObject.hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

		//�Q�[���p�b�h�̓��͏���DIJOYSTATE2�Ɋi�[�����̂Ńf�[�^�t�H�[�}�b�g�Ɏw��
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
		return DIENUM_CONTINUE;		//�f�o�C�X�쐬���ł��Ȃ��̂ŗ񋓂𑱂���
	}

	return DIENUM_STOP;
}

BOOL CALLBACK DxInput::EnumObject(LPCDIDEVICEOBJECTINSTANCE pInstance, LPVOID pvRef) {

	DIPROPRANGE range;

	range.diph.dwSize = sizeof(DIPROPRANGE);
	range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	range.diph.dwObj = pInstance->dwType;					//�{�^����X�e�B�b�N�̃f�[�^
	range.diph.dwHow = DIPH_BYID;							//�^�C�v�Ŏ擾���邱�Ƃ��w��
	range.lMin = AnalogInput_Min;							//�l�̍ŏ��l
	range.lMax = AnalogInput_Max;							//�l�̍ő�l

	LPDIRECTINPUTDEVICE8 pInputDev = (LPDIRECTINPUTDEVICE8)pvRef;
	pInputDev->SetProperty(DIPROP_RANGE, &range.diph);

	return DIENUM_CONTINUE;
}

bool DxInput::Update() {

	if (pKeyDevice) {
		pKeyDevice->Acquire();	//���͂̎�t�J�n
		pKeyDevice->GetDeviceState(Key_ArraySize, inputKeyData);	//�f�[�^���擾
	}

	if (pPadDevice) {
		pPadDevice->Poll();		//�W���C�p�b�h�f�[�^�擾
		pPadDevice->Acquire();

		memcpy(&lastPadData, &inputPadData, sizeof(DIJOYSTATE2));
		pPadDevice->GetDeviceState(sizeof(DIJOYSTATE2), &inputPadData);
	}

	return true;
}

#pragma region �L�[�{�[�h����

/// <summary>
/// ���݂��̃L�[��������Ă��邩��Ԃ�
/// </summary>
/// <param name="key">�L�[�R�[�h</param>
/// <returns>������Ă���ꍇ��true</returns>
bool DxInput::IsKeyDown(int key) {

	if (!pKeyDevice) {
		return false;
	}

	//�ŏ��1�r�b�g�ɉ�����Ă��邩�̃f�[�^���i�[����Ă���
	//�ŉ���1�r�b�g�ɂ̓g�O��(�I���E�I�t)�̏�Ԃ��i�[����Ă���
	return (inputKeyData[key] & 0x80) ? true : false;
}

/// <summary>
/// �����ꂽ�L�[������
/// </summary>
/// <param name="key">�L�[�R�[�h</param>
/// <returns>���݉�����Ă��Ē��O�ɉ�����Ă��Ȃ��ꍇtrue</returns>
bool DxInput::IsKeyPressed(int key) {

	if (!pKeyDevice) {
		return false;
	}

	return ((inputKeyData[key] & 0x80) && !(lastKeyData[key] & 0x800)) ? true : false;
}

/// <summary>
/// ���݉�����Ă��炸���O�ɉ�����Ă���ꍇ
/// </summary>
/// <param name="key">�L�[�R�[�h</param>
/// <returns>���݉�����Ă��炸���O�ɉ�����Ă���ꍇtrue</returns>
bool DxInput::IsKeyReleased(int key) {

	if (!pKeyDevice) {
		return false;
	}
	
	return (!(inputKeyData[key] & 0x80) && (lastKeyData[key] & 0x800)) ? true : false;
}

#pragma endregion

#pragma region �Q�[���p�b�h����

BYTE DxInput::GetPovPosition() {

	//�f�W�^�����͂̔��f
	//rgdwPOV[0]�ɉ����ꂽ�������p�x*100�Ŋi�[����Ă���
	//�^��0�Ŏ��v����36000�͈̔�
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

	//�A�i���O���͂̔��f
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

#pragma region �L�[�{�[�h�ƃQ�[���p�b�h���Ή�(�v�m�F)

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

