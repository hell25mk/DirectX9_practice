#include "Window.h"
//#include <string>

bool Window::SetWindowSize(const int wid, const int hig){

	widthSize = wid;
	heightSize = hig;

	return true;
}

bool Window::SetScreenMode(const bool flg){

	if(flg){
		nCmdShow = SW_MAXIMIZE;
		return true;
	}

	nCmdShow = SW_SHOW;

	return true;
}

bool Window::SetWindowName(const TCHAR* name){

	_tcscpy_s(windowName, Max_NameSize, name);

	return true;
}

bool Window::SetWindowIcon(){


	return true;
}

bool Window::SetBackgroundColor(const int color){

	return true;
}

/// <summary>
/// @brief �w�i�̐F����
/// </summary>
/// <param name="r">�Ԃ̒l</param>
/// <param name="g">�΂̒l</param>
/// <param name="b">�̒l</param>
/// <returns>����true�A���sfalse</returns>
bool Window::SetBackgroundColor(const int r, const int g, const int b){

	return true;
}