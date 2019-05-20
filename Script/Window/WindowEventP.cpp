#include "Window.h"

bool Window::WindowClose(){

	short onButton = MessageBox(NULL, _T("デストロイ？"), _T("メッセージ"), MB_YESNO | MB_ICONQUESTION);

	if(onButton == IDYES){
		//ウィンドウが閉じられたらプログラムを終了する
		DestroyWindow(hWnd);
		PostQuitMessage(NULL);

		return true;
	}

	return false;
}