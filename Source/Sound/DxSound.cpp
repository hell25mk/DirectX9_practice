#include "DxSound.h"

LPDIRECTSOUND8 DxSound::pDxSound = NULL;

DxSound::DxSound() : pDxSoundBuffer(NULL),pDxSoundNotify(NULL),hEvent(NULL) {
}

DxSound::DxSound(LPCTSTR fileName) : pDxSoundBuffer(NULL), pDxSoundNotify(NULL), hEvent(NULL) {

	Load(fileName);

}

DxSound::DxSound(const DxSound& sound) : pDxSoundBuffer(NULL), pDxSoundNotify(NULL), hEvent(NULL) {

	ReleaseObject(pDxSoundBuffer);

	if (pDxSound) {
		pDxSound->DuplicateSoundBuffer(sound.pDxSoundBuffer, &pDxSoundBuffer);
	}

}

DxSound& DxSound::operator=(const DxSound& sound) {

	ReleaseObject(pDxSoundBuffer);

	if (pDxSound) {
		pDxSound->DuplicateSoundBuffer(sound.pDxSoundBuffer, &pDxSoundBuffer);
	}

	return *this;
}

DxSound::~DxSound(){

	if(hEvent){
		CloseHandle(hEvent);
	}
	ReleaseObject(pDxSoundNotify);
	ReleaseObject(pDxSoundBuffer);

}

bool DxSound::Load(LPCTSTR fileName) {

	//wav�t�@�C�����J��
	FILE* fp;
	if (_tfopen_s(&fp, fileName, _T("rb"))) {
		MessageBox(NULL, _T("�t�@�C�����J���܂���ł���"), _T("�G���["), MB_OK);
		return false;
	}

	//wav�t�@�C�����ǂ������ׂ�
	char buf[10];
	fread(buf, 4, 1, fp);
	if (memcmp(buf, "RIFF", 4) != 0) {
		MessageBox(NULL, _T("RIFF�t�H�[�}�b�g�ł͂���܂���"), _T("�G���["), MB_OK);
		return false;
	}

	//RIFF�f�[�^�T�C�Y�͏ȗ�
	fseek(fp, 4, SEEK_CUR);

	fread(buf, 8, 1, fp);
	if (memcmp(buf, "WAVEfmt ", 8) != 0) {
		MessageBox(NULL, _T("Wav�t�H�[�}�b�g�ł͂Ȃ����A�t�H�[�}�b�g��`������܂���"), _T("�G���["), MB_OK);
		return false;
	}

	//fmt�f�[�^�T�C�Y�G���A��ǂݔ�΂�
	fseek(fp, 4, SEEK_CUR);

	//�t�H�[�}�b�g�����擾
	WAVEFORMATEX wavFormat;
	fread(&wavFormat, sizeof(WAVEFORMATEX) - 2, 1, fp);

	//���y�f�[�^�̊J�n���Ӗ�����data�̕����񂪂��邩���ׂ�
	ZeroMemory(buf, sizeof(buf));
	while(strncmp("data", buf, sizeof(buf))){

		buf[0] = fgetc(fp);

		if(buf[0] == EOF){
			MessageBox(NULL, _T("�g�`�f�[�^��`��������܂���"), _T("�G���["), MB_OK);
			fclose(fp);
			return false;
		}

		if(buf[0] == 'd'){
			fread(&buf[1], 1, 3, fp);
		}

	}

	//���y�f�[�^�T�C�Y���擾
	int wavSize;
	fread(&wavSize, sizeof(int), 1, fp);

	//CreateSoundBuffer�ɑ��M���邽�߂̉��y�����쐬
	DSBUFFERDESC desc;
	ZeroMemory(&desc, sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_LOCDEFER;			//�n�[�h�E�F�A�ł̍Đ���D��
	desc.dwBufferBytes = wavSize;
	desc.lpwfxFormat = &wavFormat;

	ReleaseObject(pDxSoundBuffer);
	pDxSound->CreateSoundBuffer(&desc, &pDxSoundBuffer, NULL);

	//�A�N�Z�X�\�ȃo�b�t�@�T�C�Y
	DWORD bufferSize;
	//wav�o�b�t�@�A�N�Z�X�|�C���g���i�[���邽�߂̃|�C���^
	LPVOID pAudioAccess;

	//�o�b�t�@���b�N
	pDxSoundBuffer->Lock(
		0, 0,										//�o�b�t�@�S�̂����b�N���邽�ߐ��l�̎w��͕s�v
		&pAudioAccess, &bufferSize,					//�������ރo�b�t�@���擾���邽�߂̃|�C���^
		NULL, NULL,									//2�ɕ����ď������ނ��Ƃ��\(�g�p���Ă��Ȃ�)
		DSBLOCK_ENTIREBUFFER						//�o�b�t�@���ׂĂ����b�N
	);

	//�T�E���h�f�[�^���o�b�t�@�֏�������
	fread(pAudioAccess, bufferSize, 1, fp);

	//���b�N����
	pDxSoundBuffer->Unlock(pAudioAccess, bufferSize, NULL, NULL);

	//�J�����t�@�C�������
	fclose(fp);

	return true;
}

//�ʃX���b�h�ɓn���f�[�^���i�[����\����
class PlayThreadData {

public:
	HANDLE hEvent;
	DxSound* soundObject;

};

void DxSound::Play(bool isLoop) {

	if (pDxSoundBuffer) {
		return;
	}

	DWORD loop = isLoop ? DSBPLAY_LOOPING : 0;

	pDxSoundBuffer->SetCurrentPosition(0);		//�Đ��ʒu��擪�Ɉړ�
	pDxSoundBuffer->Play(
		0,					//�K��0���w��
		0,					//�Đ��̗D��x(0���ł��Ⴍ�A0xFFFFFFFF���ł�����		
		loop				//�Đ��I�v�V����(DSBPLAY_LOOPING�Ȃ烋�[�v�Đ��ɂȂ�)
	);

	if (pDxSoundNotify) {
		//�Đ��I�����Ď�����X���b�h�𗧂��グ��
		PlayThreadData* data = new PlayThreadData;
		data->hEvent = hEvent;
		data->soundObject = this;

		DWORD threadID;
		CreateThread(NULL, 0, DxSound::NotifyFunction, data, 0, &threadID);
	}

}

void DxSound::Stop(){

	if (pDxSoundBuffer) {
		return;
	}

	pDxSoundBuffer->Stop();

}

void DxSound::SetVolume(LONG volume){

	if (pDxSoundBuffer) {
		return;
	}

	pDxSoundBuffer->SetVolume(volume);

}

void DxSound::SetPan(LONG pan){

	if (pDxSoundBuffer) {
		return;
	}

	pDxSoundBuffer->SetPan(pan);

}

void DxSound::EnableDeleteEnd() {

	if (pDxSoundBuffer) {
		return;
	}

	//IDirectSoundNotify�̍쐬
	HRESULT hr = pDxSoundBuffer->QueryInterface(
		IID_IDirectSoundNotify, (LPVOID*)& pDxSoundNotify
	);

	//�ʒm�C�x���g�Ɏg�p����n���h���쐬
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	//�C�x���g�����Ɋւ�����쐬
	DSBPOSITIONNOTIFY pn;
	pn.dwOffset = DSBPN_OFFSETSTOP;		//�I���܂ōĐ�����
	pn.hEventNotify = hEvent;			//�n���h�����֘A�Â���

	//�C�x���g�f�[�^��o�^
	pDxSoundNotify->SetNotificationPositions(1, &pn);

}

void DxSound::CreateDirectSound() {

	DirectSoundCreate8(
		&DSDEVID_DefaultPlayback,
		&pDxSound,
		NULL
	);

	pDxSound->SetCooperativeLevel(
		windowObject.hWnd, DSSCL_PRIORITY
	);

}

void DxSound::ReleaseDirectSound() {

	ReleaseObject(pDxSound);

}

DWORD DxSound::NotifyFunction(LPVOID param) {

	PlayThreadData* data = (PlayThreadData*)param;

	//�Đ��I���ʒm������܂őҋ@
	WaitForMultipleObjects(1, &data->hEvent, FALSE, INFINITE);

	delete data->soundObject;
	delete data;

	return 0L;
}