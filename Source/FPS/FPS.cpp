#include "FPS.h"

FPS::FPS() : lastTime() {
}

void FPS::Init(){

	lastTime = 0;

}

bool FPS::Update(){

	const DWORD Wait_Time = 16;		//約60FPS

	//最後に行った処理からの時間を調べる
	DWORD nTime = timeGetTime();		//システムが起動してからの時間を取得
	DWORD rTime = nTime - lastTime;

	lastTime = nTime;

	if(rTime < Wait_Time){
		Sleep(Wait_Time - rTime);
	}

	return true;
}