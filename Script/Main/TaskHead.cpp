#include "GameMain.h"

void TaskHead::Init(){

	fps.Init();

}

bool TaskHead::Update(){

	fps.Update();

	//�摜�̃N���A
	pD3Ddevice->Clear(
		0,							//�N���A����̈�̔z���
		NULL,						//�N���A����̈�̔z��
		D3DCLEAR_TARGET,			//�Ώۂ��w��̐F�ŃN���A����
		D3DCOLOR_XRGB(0,0,64),	//�N���A����F�����F�ɐݒ�
		1.0f,						//z�����̃N���A
		0							//�X�e���V���o�b�t�@�̃N���A
	);

	//�J�n�錾
	pD3Ddevice->BeginScene();

	return true;
}