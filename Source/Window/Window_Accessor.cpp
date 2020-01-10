#include "Window.h"

/// <summary>
/// Windowの高さと横幅をセットする
/// </summary>
/// <param name="wid">高さ値</param>
/// <param name="hig">横幅値</param>
void Window::SetWindowSize(unsigned int wid, unsigned int hig){

	widthSize = wid;
	heightSize = hig;

}

/// <summary>
/// スクリーンモードの設定をセットする
/// </summary>
/// <param name="full">true:フルスクリーン,false:ウィンドウ</param>
void Window::SetScreenMode(bool full){

	if(full){
		nCmdShow = SW_MAXIMIZE;
		return;
	}

	nCmdShow = SW_SHOW;

}

/// <summary>
/// Windowのタイトルをセットする
/// </summary>
/// <param name="name">タイトルの名前</param>
void Window::SetWindowTitle(LPCTSTR title){

	_tcscpy_s(windowTitle, Max_TitleLength, title);

}

void Window::SetWindowIcon(){



}

void Window::SetBackgroundColor(int color){



}

/// <summary>
/// @brief 背景の色する
/// </summary>
/// <param name="r">赤の値</param>
/// <param name="g">緑の値</param>
/// <param name="b">青の値</param>
void Window::SetBackgroundColor(int r, int g, int b){



}