#include "DirectX.h"

/// <summary>
/// @brief DirectXの初期化を行う
/// </summary>
/// <returns>
/// @return true　初期化成功
/// @return false　初期化失敗
/// </returns>
bool DirectX::DxInit(){
	
	//Direct3Dオブジェクトを生成
	d3dObject.pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(!d3dObject.pD3D){
		MessageBox(NULL, _T("DirectXDeviceの初期化に失敗しました"), _T("エラー"), MB_OK);
		//DXTRACE_MSG(_T("DirectXDeviceの初期化に失敗しました"));	//エラー出る

		return false;
	}

	D3DDISPLAYMODE d3ddm;
	if(FAILED(d3dObject.pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		MessageBox(NULL, _T("DirectX3DDeviceの初期化に失敗しました"), _T("エラー"), MB_OK);

		return false;
	}

#pragma region 細かい画面モードの設定
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//構造体の中身を0で初期化
	d3dpp.Windowed = true;										//ウィンドウモードの設定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//ディスプレイドライバに最も効率的な方法を選択させる
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					//バックグラウンド描画の方法をシステムに任せる
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//描画更新の指示があり次第待たずにすぐ更新

	//D3Dデバイスオブジェクトの作成
	if(FAILED(d3dObject.pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,							//プライマリディスプレイに描画
		D3DDEVTYPE_HAL,								//グラフィックボードの利用を優先して処理
		hWnd,										//表示するウィンドウ（CreateWindowで取得したハンドル）
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,		//グラフィックボードの利用を優先して頂点処理を行う
		&d3dpp,										//画面モードの状態を格納した構造体
		&d3dObject.pD3Ddevice						//格納するDirect3DDevice9へのポインタ
		))){
		MessageBox(NULL, _T("3DDeviceObjectの初期化に失敗しました"), _T("エラー"), MB_OK);

		return false;
	}
#pragma endregion

#pragma region アルファブレンドの設定
	//描画先にある画像に対するブレンド方法を指定（D3DBLEND_SRCALPHAでアルファ値による描画が可能）
	d3dObject.pD3Ddevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//描画元の画像に対するブレンドを指定
	//D3DBLEND_INVSRCALPHAで画像の状態にあわせて描画先画像のアルファ値が変わる
	d3dObject.pD3Ddevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//アルファブレンドを有効化
	d3dObject.pD3Ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	if(FAILED(D3DXCreateSprite(d3dObject.pD3Ddevice, &d3dObject.pSprite))){
		MessageBox(NULL, _T("SpriteObjectの作成に失敗しました"), _T("エラー"), MB_OK);

		return false;
	}
#pragma endregion
	
	return true;
}

bool DirectX::DxEnd(){
	
	ReleaseD3DObject(d3dObject.pSprite);
	ReleaseD3DObject(d3dObject.pD3Ddevice);
	ReleaseD3DObject(d3dObject.pD3D);
	
	return true;
}