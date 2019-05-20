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
/// @brief ”wŒi‚ÌF‚·‚é
/// </summary>
/// <param name="r">Ô‚Ì’l</param>
/// <param name="g">—Î‚Ì’l</param>
/// <param name="b">Â‚Ì’l</param>
/// <returns>
/// @return true ¬Œ÷
/// false ¸”s
/// </returns>
bool Window::SetBackgroundColor(int r, int g, int b){

	return true;
}