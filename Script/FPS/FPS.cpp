#include "FPS.h"

void FPS::Init(){

	lasttime = 0;

}

bool FPS::Update(){

	const DWORD Wait_Time = 16;		//約60FPS

	//最後に行った処理からの時間を調べる
	DWORD nTime = timeGetTime();		//システムが起動してからの時間を取得
	DWORD rTime = nTime - lasttime;

	lasttime = nTime;

	if(rTime < Wait_Time){
		Sleep(Wait_Time - rTime);
	}

	return true;
}