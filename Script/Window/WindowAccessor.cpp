#include "Window.h"
//#include <string>

bool Window::SetWindowSize(int wid, int hig){

	widthSize = wid;
	heightSize = hig;

	return true;
}

bool Window::SetScreenMode(bool flg){

	if(flg){
		nCmdShow = SW_MAXIMIZE;
		return true;
	}

	nCmdShow = SW_SHOW;

	return true;
}

bool Window::SetWindowName(LPCTSTR name){

	_tcscpy_s(windowName, Max_NameSize, name);

	return true;
}

bool Window::SetWindowIcon(){


	return true;
}

bool Window::SetBackgroundColor(int color){

	return true;
}

/// <summary>
/// @brief �w�i�̐F����
/// </summary>
/// <param name="r">�Ԃ̒l</param>
/// <param name="g">�΂̒l</param>
/// <param name="b">�̒l</param>
/// <returns>
/// @return true ����
/// false ���s
/// </returns>
bool Window::SetBackgroundColor(int r, int g, int b){

	return true;
}