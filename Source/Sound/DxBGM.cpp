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

	//開始位置s,終了位置e
	pMediaSeeking->GetPositions(&s, &e);

	if(s >= e){
		s = 0;
		pMediaSeeking->SetPositions(
			&s, AM_SEEKING_AbsolutePositioning,		//再生位置は絶対位置（s*100)ナノ秒
			NULL, AM_SEEKING_NoPositioning			//終了位置は変更しないのでNoPositioningを指定
		);
	}

	return true;
}

void DxBGM::Load(LPCTSTR fileName){

	Release();

	HRESULT hr = CoCreateInstance(
		CLSID_FilterGraph,				//COMの識別子
		NULL,							//特別に取得する情報はないのでNULL
		CLSCTX_INPROC_SERVER,			//このプログラム内でのみ使うことを指定
		IID_IGraphBuilder,				//取得するインターフェース
		(LPVOID*)& pBuilder				//格納先
	);

	if(FAILED(hr)){
		MessageBox(NULL, _T("IGraphBuilderの作成に失敗しました"), _T("エラー"), MB_OK);
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
		//再生位置を先頭に移動する
		LONGLONG s = 0;

		pMediaSeeking->SetPositions(
			&s, AM_SEEKING_AbsolutePositioning,		//再生位置は絶対位置（s*100)ナノ秒
			NULL, AM_SEEKING_NoPositioning			//終了位置は変更しないのでNoPositioningを指定
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

#pragma region フェード関係

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
		MessageBox(NULL, _T("ボリュームの設定ができません"), _T("エラー"), MB_OK);
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