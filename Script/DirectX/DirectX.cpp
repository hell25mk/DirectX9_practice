#include "DirectX.h"

/// <summary>
/// @brief DirectX�̏��������s��
/// </summary>
/// <returns>
/// @return true�@����������
/// @return false�@���������s
/// </returns>
bool DirectX::DxInit(){
	
	//Direct3D�I�u�W�F�N�g�𐶐�
	d3dObject.pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(!d3dObject.pD3D){
		MessageBox(NULL, _T("DirectXDevice�̏������Ɏ��s���܂���"), _T("�G���["), MB_OK);
		//DXTRACE_MSG(_T("DirectXDevice�̏������Ɏ��s���܂���"));	//�G���[�o��

		return false;
	}

	D3DDISPLAYMODE d3ddm;
	if(FAILED(d3dObject.pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))){
		MessageBox(NULL, _T("DirectX3DDevice�̏������Ɏ��s���܂���"), _T("�G���["), MB_OK);

		return false;
	}

#pragma region �ׂ�����ʃ��[�h�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//�\���̂̒��g��0�ŏ�����
	d3dpp.Windowed = true;										//�E�B���h�E���[�h�̐ݒ�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//�f�B�X�v���C�h���C�o�ɍł������I�ȕ��@��I��������
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;					//�o�b�N�O���E���h�`��̕��@���V�X�e���ɔC����
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//�`��X�V�̎w�������莟��҂����ɂ����X�V

	//D3D�f�o�C�X�I�u�W�F�N�g�̍쐬
	if(FAILED(d3dObject.pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,							//�v���C�}���f�B�X�v���C�ɕ`��
		D3DDEVTYPE_HAL,								//�O���t�B�b�N�{�[�h�̗��p��D�悵�ď���
		hWnd,										//�\������E�B���h�E�iCreateWindow�Ŏ擾�����n���h���j
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,		//�O���t�B�b�N�{�[�h�̗��p��D�悵�Ē��_�������s��
		&d3dpp,										//��ʃ��[�h�̏�Ԃ��i�[�����\����
		&d3dObject.pD3Ddevice						//�i�[����Direct3DDevice9�ւ̃|�C���^
		))){
		MessageBox(NULL, _T("3DDeviceObject�̏������Ɏ��s���܂���"), _T("�G���["), MB_OK);

		return false;
	}
#pragma endregion

#pragma region �A���t�@�u�����h�̐ݒ�
	//�`���ɂ���摜�ɑ΂���u�����h���@���w��iD3DBLEND_SRCALPHA�ŃA���t�@�l�ɂ��`�悪�\�j
	d3dObject.pD3Ddevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//�`�挳�̉摜�ɑ΂���u�����h���w��
	//D3DBLEND_INVSRCALPHA�ŉ摜�̏�Ԃɂ��킹�ĕ`���摜�̃A���t�@�l���ς��
	d3dObject.pD3Ddevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//�A���t�@�u�����h��L����
	d3dObject.pD3Ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	if(FAILED(D3DXCreateSprite(d3dObject.pD3Ddevice, &d3dObject.pSprite))){
		MessageBox(NULL, _T("SpriteObject�̍쐬�Ɏ��s���܂���"), _T("�G���["), MB_OK);

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