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
/// @brief 背景の色する
/// </summary>
/// <param name="r">赤の値</param>
/// <param name="g">緑の値</param>
/// <param name="b">青の値</param>
/// <returns>成功true、失敗false</returns>
bool Window::SetBackgroundColor(const int r, const int g, const int b){

	return true;
}