#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")	// Direct3D9 ライブラリをリンクする
#pragma comment(lib, "d3dx9.lib")	// Direct3DX9 ライブラリをリンクする

#pragma comment(lib, "DxErr.lib")
#pragma comment(lib, "dxguid.lib")

#if _DEBUG
#include <crtdbg.h>		//_CrtSetDbgFlagを使用するため

//メモリリークが発生してもどこに問題があったか突き止めやすくするため
//DirectX SDK内で記述されているnewを置換されることを避けるためdefineを行った後で追加
#define new ::new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

#pragma region D3Dオブジェクトを開放する
/// <summary>
/// C言語用
/// </summary>
#define RELEASE_OBJECT(obj) {if(obj) x->Release();}

/// <summary>
/// C++言語用
/// </summary>
template<class Type>
constexpr void ReleaseObject(Type obj) {

	if (obj) {
		obj->Release();
		obj = nullptr;
	}

}
#pragma endregion

namespace{
	//名前サイズの最大数
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

