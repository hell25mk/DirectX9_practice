#include "DxBGM.h"

DxBGM::DxBGM() :
	pBuilder(), pMediaCtrl(), pMediaSeeking(), pBasicAudio(), 
	isLoop(false), isFading(false), 
	timeSecond(0.0f), timeEnd(0.0f), volSecond(0.0f), deltaTime(0.0f){
}

DxBGM::DxBGM(LPCTSTR fileName) :
	pBuilder(), pMediaCtrl(), pMediaSeeking(), pBasicAudio(), 
	isLoop(false), isFading(false), 
	timeSecond(0.0f), timeEnd(0.0f), volSecond(0.0f), deltaTime(0.0f){

	Load(fileName);

}

DxBGM::~DxBGM(){

	ReleaseObject(pBasicAudio);
	ReleaseObject(pMediaSeeking);
	ReleaseObject(pMediaCtrl);
	ReleaseObject(pBuilder);

}


void DxBGM::Init(){

	pBuilder = nullptr;
	pMediaCtrl = nullptr;
	pMediaSeeking = nullptr;
	pBasicAudio = nullptr;

	isLoop = false;
	isFading = false;

}

void DxBGM::Release(){

	ReleaseObject(pBasicAudio);
	ReleaseObject(pMediaSeeking);
	ReleaseObject(pMediaCtrl);
	ReleaseObject(pBuilder);

}

bool DxBGM::Update(){

	if(!isLoop || !pMediaSeeking){
		return false;
	}

	LONGLONG s, e;

	//�J�n�ʒus,�I���ʒue
	pMediaSeeking->GetPositions(&s, &e);

	if(s >= e){
		s = 0;
		pMediaSeeking->SetPositions(
			&s, AM_SEEKING_AbsolutePositioning,		//�Đ��ʒu�͐�Έʒu�is*100)�i�m�b
			NULL, AM_SEEKING_NoPositioning			//�I���ʒu�͕ύX���Ȃ��̂�NoPositioning���w��
		);
	}

	return true;
}

void DxBGM::Load(LPCTSTR fileName){

	Release();

	HRESULT hr = CoCreateInstance(
		CLSID_FilterGraph,				//COM�̎��ʎq
		NULL,							//���ʂɎ擾������͂Ȃ��̂�NULL
		CLSCTX_INPROC_SERVER,			//���̃v���O�������ł̂ݎg�����Ƃ��w��
		IID_IGraphBuilder,				//�擾����C���^�[�t�F�[�X
		(LPVOID*)& pBuilder				//�i�[��
	);

	if(FAILED(hr)){
		MessageBox(NULL, _T("IGraphBuilder�̍쐬�Ɏ��s���܂���"), _T("�G���["), MB_OK);
		return;
	}

#ifdef _UNICODE
	pBuilder->RenderFile(fileName, NULL);
#else
	wchar_t wfName[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, fileName, -1, wfName, MAX_PATH);
	pBuilder->RenderFile(wfName, NULL);
#endif //  _UNICODE

	pBuilder->QueryInterface(IID_IMediaControl, (LPVOID*)& pMediaCtrl);
	pBuilder->QueryInterface(IID_IMediaSeeking, (LPVOID*)& pMediaSeeking);
	pBuilder->QueryInterface(IID_IBasicAudio, (LPVOID*)& pBasicAudio);

}

void DxBGM::Play(bool loop){

	if(!pMediaCtrl){
		return;
	}

	isLoop = loop;

	if(pMediaSeeking){
		//�Đ��ʒu��擪�Ɉړ�����
		LONGLONG s = 0;

		pMediaSeeking->SetPositions(
			&s, AM_SEEKING_AbsolutePositioning,		//�Đ��ʒu�͐�Έʒu�is*100)�i�m�b
			NULL, AM_SEEKING_NoPositioning			//�I���ʒu�͕ύX���Ȃ��̂�NoPositioning���w��
		);
	}

	pMediaCtrl->Run();

}

void DxBGM::Stop(){

	if(!pMediaCtrl){
		return;
	}

	pMediaCtrl->Stop();

}

#pragma region �t�F�[�h�֌W

void DxBGM::SetVolume(LONG volume){

	if(!isFading){
		return;
	}

	float t = (float)timeGetTime() - timeSecond;

	pBasicAudio->put_Volume((long)(deltaTime * volSecond));

	if(t >= timeEnd){
		isFading = false;
	}

}

void DxBGM::Fade(DWORD endTime, LONG volume){

	if(!pBasicAudio){
		MessageBox(NULL, _T("�{�����[���̐ݒ肪�ł��܂���"), _T("�G���["), MB_OK);
		return;
	}

	isFading = true;

	LONG v;

	pBasicAudio->get_Volume(&v);

	volSecond = (float)v;

	float ve = (float)volume;

	timeSecond = (float)timeGetTime();
	timeEnd = (float)endTime;

	deltaTime = (ve - volSecond) / timeEnd;

}

#pragma endregion