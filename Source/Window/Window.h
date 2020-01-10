#pragma once

#include "WindowObject.h"
#include <tchar.h>

namespace{
	constexpr int Max_TitleLength = 32;

	LPCTSTR Default_WindowName = _T("MyWindow");
}

class Window{

public:
	Window();
	Window(unsigned int wid, unsigned int hig);
	~Window();			//ポリモーフィズムは使用しないためvirtualはつけていない

	bool WindowInit();
	bool Process() const;

#pragma region Getter
	WindowObject GetWindowObject();
#pragma endregion


#pragma region Accessor
	void SetWindowSize(unsigned int wid, unsigned int hig);
	void SetScreenMode(bool full);
	void SetWindowTitle(LPCTSTR title);
	void SetWindowIcon();
	void SetBackgroundColor(int color);
	void SetBackgroundColor(int r, int g, int b);
#pragma endregion

protected:
	virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual bool WindowClose();

protected:
	WNDCLASS windowClass;	//登録する情報を格納する構造体
	WindowObject windowObject;
	int nCmdShow;
	TCHAR windowTitle[Max_TitleLength];
	unsigned int widthSize;
	unsigned int heightSize;

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};