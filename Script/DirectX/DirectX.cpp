#include "DirectX.h"



DirectX::DirectX(){
}


DirectX::~DirectX(){
}

bool DirectX::DirectXInit(){
	/*
	//Direct3D�I�u�W�F�N�g�𐶐�
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(pD3D == nullptr){
		MessageBox(NULL, _T("DirectXDevice�̏������Ɏ��s���܂���"), _T("�G���["), MB_OK);
		//DXTRACE_MSG(_T("DirectXDevice�̏������Ɏ��s���܂���"));	//�Ȃ����G���[�o��

		return false;
	}

	D3DDISPLAYMODE d3ddm;
	if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		MessageBox(NULL, _T("DirectX3DDevice�̏������Ɏ��s���܂���"), _T("�G���["), MB_OK);
		//DXTRACE_MSG(_T("DirectX3DDevice�̏������Ɏ��s���܂���"));

		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;										//�E�B���h�E���[�h�̐ݒ�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//�f�B�X�v���C�h���C�o�ɍł������I�ȕ��@��I��������
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					//�o�b�N�O���E���h�`��̕��@���V�X�e���ɔC����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//�`��X�V�̎w�������莟��҂����ɂ����X�V

	//D3D�f�o�C�X�I�u�W�F�N�g�̍쐬
	if(FAILED(pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&pD3Ddevice))){
		MessageBox(NULL, _T("3DDeviceObject�̏������Ɏ��s���܂���"), _T("�G���["), MB_OK);
		//DXTRACE_MSG(_T("3DDeviceObject�̏������Ɏ��s���܂���"));

		return false;
	}

	//�A���t�@�u�����h�̐ݒ�
	pD3Ddevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD3Ddevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pD3Ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	if(FAILED(D3DXCreateSprite(pD3Ddevice, &pSprite))){
		MessageBox(NULL, _T("SpriteObject�̍쐬�Ɏ��s���܂���"), _T("�G���["), MB_OK);
		//DXTRACE_MSG(_T("SpriteObject�̍쐬�Ɏ��s���܂���"));

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