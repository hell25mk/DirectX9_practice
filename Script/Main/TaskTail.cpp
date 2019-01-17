#include "GameMain.h"

bool TaskTail::Update(){

	//表示
	pD3Ddevice->EndScene();
	pD3Ddevice->Present(
		NULL,				//転送元の領域（NULLで全域） 
		NULL,				//転送先の領域
		NULL,				//転送先のウィンドウを示すハンドル（NULLで標準ウィンドウ）
		NULL				//現バージョンでは常にNULLを指定
	);

	return true;
}