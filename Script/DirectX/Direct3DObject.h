#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")	// Direct3D9 ライブラリをリンクする
#pragma comment(lib, "d3dx9.lib")	// Direct3DX9 ライブラリをリンクする

#pragma comment(lib, "DxErr.lib")	//使ってないけど一応
#pragma comment(lib, "dxguid.lib")

//デバッグ時のみインクルード
#if _DEBUG
#include <crtdbg.h>		//_CrtSetDbgFlagを使用するため

//メモリリークが発生してもどこに問題があったか突き止めやすくするため
//DirectX SDK内で記述されているnewを置換されることを避けるためdefineを行った後で追加
#define new ::new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

//C言語用
#define RELEASE_D3DOBJECT(obj) {if(obj) x->Release();}

/// <summary>
/// @brief D3Dオブジェクトを開放する
/// </summary>
template<class Type>
constexpr void ReleaseD3DObject(Type obj){

	if(obj){
		obj->Release();
		obj = nullptr;
	}

}

namespace{
	constexpr int Name_Size = 32;

	constexpr float D2r(float d){

		return (d / 180.0f * D3DX_PI);
	}
}

class Direct3DObject{

public:
	static LPDIRECT3D9 pD3D;
	static LPDIRECT3DDEVICE9 pD3Ddevice;
	static LPD3DXSPRITE pSprite;

};

