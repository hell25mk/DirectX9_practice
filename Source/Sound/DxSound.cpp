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

	//wavファイルを開く
	FILE* fp;
	if (_tfopen_s(&fp, fileName, _T("rb"))) {
		MessageBox(NULL, _T("ファイルが開けませんでした"), _T("エラー"), MB_OK);
		return false;
	}

	//wavファイルかどうか調べる
	char buf[10];
	fread(buf, 4, 1, fp);
	if (memcmp(buf, "RIFF", 4) != 0) {
		MessageBox(NULL, _T("RIFFフォーマットではありません"), _T("エラー"), MB_OK);
		return false;
	}

	//RIFFデータサイズは省略
	fseek(fp, 4, SEEK_CUR);

	fread(buf, 8, 1, fp);
	if (memcmp(buf, "WAVEfmt ", 8) != 0) {
		MessageBox(NULL, _T("Wavフォーマットではないか、フォーマット定義がありません"), _T("エラー"), MB_OK);
		return false;
	}

	//fmtデータサイズエリアを読み飛ばす
	fseek(fp, 4, SEEK_CUR);

	//フォーマット情報を取得
	WAVEFORMATEX wavFormat;
	fread(&wavFormat, sizeof(WAVEFORMATEX) - 2, 1, fp);

	//音楽データの開始を意味するdataの文字列があるか調べる
	ZeroMemory(buf, sizeof(buf));
	while(strncmp("data", buf, sizeof(buf))){

		buf[0] = fgetc(fp);

		if(buf[0] == EOF){
			MessageBox(NULL, _T("波形データ定義が見つかりません"), _T("エラー"), MB_OK);
			fclose(fp);
			return false;
		}

		if(buf[0] == 'd'){
			fread(&buf[1], 1, 3, fp);
		}

	}

	//音楽データサイズを取得
	int wavSize;
	fread(&wavSize, sizeof(int), 1, fp);

	//CreateSoundBufferに送信するための音楽情報を作成
	DSBUFFERDESC desc;
	ZeroMemory(&desc, sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_LOCDEFER;			//ハードウェアでの再生を優先
	desc.dwBufferBytes = wavSize;
	desc.lpwfxFormat = &wavFormat;

	ReleaseObject(pDxSoundBuffer);
	pDxSound->CreateSoundBuffer(&desc, &pDxSoundBuffer, NULL);

	//アクセス可能なバッファサイズ
	DWORD bufferSize;
	//wavバッファアクセスポイントを格納するためのポインタ
	LPVOID pAudioAccess;

	//バッファロック
	pDxSoundBuffer->Lock(
		0, 0,										//バッファ全体をロックするため数値の指定は不要
		&pAudioAccess, &bufferSize,					//書き込むバッファを取得するためのポインタ
		NULL, NULL,									//2つに分けて書き込むことも可能(使用していない)
		DSBLOCK_ENTIREBUFFER						//バッファすべてをロック
	);

	//サウンドデータをバッファへ書き込む
	fread(pAudioAccess, bufferSize, 1, fp);

	//ロック解除
	pDxSoundBuffer->Unlock(pAudioAccess, bufferSize, NULL, NULL);

	//開いたファイルを閉じる
	fclose(fp);

	return true;
}

//別スレッドに渡すデータを格納する構造体
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

	pDxSoundBuffer->SetCurrentPosition(0);		//再生位置を先頭に移動
	pDxSoundBuffer->Play(
		0,					//必ず0を指定
		0,					//再生の優先度(0が最も低く、0xFFFFFFFFが最も高い		
		loop				//再生オプション(DSBPLAY_LOOPINGならループ再生になる)
	);

	if (pDxSoundNotify) {
		//再生終了を監視するスレッドを立ち上げる
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

	//IDirectSoundNotifyの作成
	HRESULT hr = pDxSoundBuffer->QueryInterface(
		IID_IDirectSoundNotify, (LPVOID*)& pDxSoundNotify
	);

	//通知イベントに使用するハンドル作成
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	//イベント発生に関する情報作成
	DSBPOSITIONNOTIFY pn;
	pn.dwOffset = DSBPN_OFFSETSTOP;		//終了まで再生する
	pn.hEventNotify = hEvent;			//ハンドラを関連づける

	//イベントデータを登録
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

	//再生終了通知が来るまで待機
	WaitForMultipleObjects(1, &data->hEvent, FALSE, INFINITE);

	delete data->soundObject;
	delete data;

	return 0L;
}