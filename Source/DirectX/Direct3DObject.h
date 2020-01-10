#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")	// Direct3D9 ���C�u�����������N����
#pragma comment(lib, "d3dx9.lib")	// Direct3DX9 ���C�u�����������N����

#pragma comment(lib, "DxErr.lib")
#pragma comment(lib, "dxguid.lib")

#if _DEBUG
#include <crtdbg.h>		//_CrtSetDbgFlag���g�p���邽��

//���������[�N���������Ă��ǂ��ɖ�肪���������˂��~�߂₷�����邽��
//DirectX SDK���ŋL�q����Ă���new��u������邱�Ƃ�����邽��define���s������Œǉ�
#define new ::new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

#pragma region D3D�I�u�W�F�N�g���J������
/// <summary>
/// C����p
/// </summary>
#define RELEASE_OBJECT(obj) {if(obj) x->Release();}

/// <summary>
/// C++����p
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
	//���O�T�C�Y�̍ő吔
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

