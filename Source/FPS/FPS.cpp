#include "FPS.h"

FPS::FPS() : lastTime() {
}

void FPS::Init(){

	lastTime = 0;

}

bool FPS::Update(){

	const DWORD Wait_Time = 16;		//��60FPS

	//�Ō�ɍs������������̎��Ԃ𒲂ׂ�
	DWORD nTime = timeGetTime();		//�V�X�e�����N�����Ă���̎��Ԃ��擾
	DWORD rTime = nTime - lastTime;

	lastTime = nTime;

	if(rTime < Wait_Time){
		Sleep(Wait_Time - rTime);
	}

	return true;
}