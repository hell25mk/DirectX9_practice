#include "FPS.h"

void FPS::Init(){

	lasttime = 0;

}

bool FPS::Update(){

	const DWORD Wait_Time = 16;		//��60FPS

	//�Ō�ɍs������������̎��Ԃ𒲂ׂ�
	DWORD nTime = timeGetTime();		//�V�X�e�����N�����Ă���̎��Ԃ��擾
	DWORD rTime = nTime - lasttime;

	lasttime = nTime;

	if(rTime < Wait_Time){
		Sleep(Wait_Time - rTime);
	}

	return true;
}