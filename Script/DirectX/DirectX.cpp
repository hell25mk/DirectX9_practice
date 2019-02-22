#include "DirectX.h"



DirectX::DirectX(){
}


DirectX::~DirectX(){
}

bool DirectX::DirectXInit(){
	/*
	//Direct3Dオブジェクトを生成
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D == nullptr){
		MessageBox(NULL, _T("DirectXDeviceの初期化に失敗しました"), _T("エラー"), MB_OK);
		//DXTRACE_MSG(_T("DirectXDeviceの初期化に失敗しました"));	//なぜかエラー出る

		return false;
	}

	D3DDISPLAYMODE d3ddm;
	if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		MessageBox(NULL, _T("DirectX3DDeviceの初期化に失敗しました"), _T("エラー"), MB_OK);
		//DXTRACE_MSG(_T("DirectX3DDeviceの初期化に失敗しました"));

		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;										//ウィンドウモードの設定
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//ディスプレイドライバに最も効率的な方法を選択させる
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					//バックグラウンド描画の方法をシステムに任せる
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//描画更新の指示があり次第待たずにすぐ更新

	//D3Dデバイスオブジェクトの作成
	if(FAILED(pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&pD3Ddevice))){
		MessageBox(NULL, _T("3DDeviceObjectの初期化に失敗しました"), _T("エラー"), MB_OK);
		//DXTRACE_MSG(_T("3DDeviceObjectの初期化に失敗しました"));

		return false;
	}

	//アルファブレンドの設定
	pD3Ddevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3Ddevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3Ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	if(FAILED(D3DXCreateSprite(pD3Ddevice, &pSprite))){
		MessageBox(NULL, _T("SpriteObjectの作成に失敗しました"), _T("エラー"), MB_OK);
		//DXTRACE_MSG(_T("SpriteObjectの作成に失敗しました"));

		return false;
	}
	*/
	return true;
}

bool DirectX::DirectXEnd(){
	/*
	D3D_RELEASE(pSprite);
	D3D_RELEASE(pD3Ddevice);
	D3D_RELEASE(pD3D);

	for(auto itr = listObject.begin(), end = listObject.end(); itr != end;){

		if((*itr).autoDelete){
			delete (*itr).gameObject;
			(*itr).gameObject = nullptr;
		}

		itr++;

	}
	*/
	return true;
}