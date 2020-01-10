#include "GameManager.h"
#include "../Font/FontManager.h"
#include "../Object/Runner/Runner.h"
#include "../Object/SoccerBall/SoccerBall.h"
#include "../Input/DxInput.h"

void GameManager::Init(){

	fps.Init();
	dxSound.CreateDirectSound();

	AppendObject(new FontManager(), 1, true, "FontManager");
	AppendObject(new DxInput(), -1, true, "DxInput");
	AppendObject(new Runner(), 10, true, "Runner");
	AppendObject(new SoccerBall(), 10, true, "SoccerBall");

}

void GameManager::Release(){

	dxSound.ReleaseDirectSound();

}

bool GameManager::Update(){

	BeginTask();
	BaseObject::Update();
	EndTask();

	return true;
}

void GameManager::BeginTask() {

	fps.Update();

	//画像のクリア
	d3dObject.pD3Ddevice->Clear(
		0,							//クリアする領域の配列個数
		NULL,						//クリアする領域の配列
		D3DCLEAR_TARGET,			//対象を指定の色でクリアする
		D3DCOLOR_XRGB(0, 0, 64),	//クリアする色を紺色に設定
		1.0f,						//z方向のクリア
		0							//ステンシルバッファのクリア
	);

	//開始宣言
	d3dObject.pD3Ddevice->BeginScene();

}

void GameManager::EndTask() {

	//表示
	d3dObject.pD3Ddevice->EndScene();
	d3dObject.pD3Ddevice->Present(
		NULL,				//転送元の領域（NULLで全域） 
		NULL,				//転送先の領域
		NULL,				//転送先のウィンドウを示すハンドル（NULLで標準ウィンドウ）
		NULL				//現バージョンでは常にNULLを指定
	);

}