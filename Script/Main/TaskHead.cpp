#include "GameMain.h"

void TaskHead::Init(){

	fps.Init();

}

bool TaskHead::Update(){

	fps.Update();

	//画像のクリア
	pD3Ddevice->Clear(
		0,							//クリアする領域の配列個数
		NULL,						//クリアする領域の配列
		D3DCLEAR_TARGET,			//対象を指定の色でクリアする
		D3DCOLOR_XRGB(0,0,64),	//クリアする色を紺色に設定
		1.0f,						//z方向のクリア
		0							//ステンシルバッファのクリア
	);

	//開始宣言
	pD3Ddevice->BeginScene();

	return true;
}