#include "TaskObject.h"

void TaskObject::Init(){

	fps.Init();

}

void TaskObject::BeginTask(){

	fps.Update();

	//�摜�̃N���A
	d3dObject.pD3Ddevice->Clear(
		0,							//�N���A����̈�̔z���
		NULL,						//�N���A����̈�̔z��
		D3DCLEAR_TARGET,			//�Ώۂ��w��̐F�ŃN���A����
		D3DCOLOR_XRGB(0, 0, 64),		//�N���A����F�����F�ɐݒ�
		1.0f,						//z�����̃N���A
		0							//�X�e���V���o�b�t�@�̃N���A
	);

	//�J�n�錾
	d3dObject.pD3Ddevice->BeginScene();

}

void TaskObject::EndTask(){

	//�\��
	d3dObject.pD3Ddevice->EndScene();
	d3dObject.pD3Ddevice->Present(
		NULL,				//�]�����̗̈�iNULL�őS��j 
		NULL,				//�]����̗̈�
		NULL,				//�]����̃E�B���h�E�������n���h���iNULL�ŕW���E�B���h�E�j
		NULL				//���o�[�W�����ł͏��NULL���w��
	);

}