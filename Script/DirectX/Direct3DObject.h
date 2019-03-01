#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")	// Direct3D9 ライブラリをリンクする
#pragma comment(lib, "d3dx9.lib")	// Direct3DX9 ライブラリをリンクする

//C言語用
#define RELEASE_D3DOBJECT(obj) {if(obj) x->Release();}

/// <summary>
/// @brief D3Dオブジェクトを開放する
/// </summary>
template<class Type>
constexpr void ReleaseD3DObject(Type obj){

	if(obj){
		obj->Release();
	}

}

class Direct3DObject{

public:
	static LPDIRECT3D9 pD3D;
	static LPDIRECT3DDEVICE9 pD3Ddevice;
	static LPD3DXSPRITE pSprite;

};

