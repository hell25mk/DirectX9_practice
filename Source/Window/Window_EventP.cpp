#include "Window.h"

/// <summary>
/// ウィンドウを破棄するかどうか
/// </summary>
/// <returns>true:破棄,false:破棄しない</returns>
bool Window::WindowClose(){

	short onButton = MessageBox(NULL, _T("終了しますか？"), _T("メッセージ"), MB_YESNO | MB_ICONQUESTION);

	if(onButton == IDYES){
		//ウィンドウが閉じられたらプログラムを終了する
		DestroyWindow(windowObject.hWnd);
		PostQuitMessage(NULL);

		return true;
	}

	return false;
}