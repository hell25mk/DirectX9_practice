#include "GameMain.h"

bool TaskTail::Update(){

	//�\��
	pD3Ddevice->EndScene();
	pD3Ddevice->Present(
		NULL,				//�]�����̗̈�iNULL�őS��j 
		NULL,				//�]����̗̈�
		NULL,				//�]����̃E�B���h�E�������n���h���iNULL�ŕW���E�B���h�E�j
		NULL				//���o�[�W�����ł͏��NULL���w��
	);

	return true;
}