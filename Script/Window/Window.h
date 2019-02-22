#pragma once

#include <Windows.h>
#include <tchar.h>

namespace{
	constexpr int Max_NameSize = 16;

	LPCTSTR Default_WindowName = _T("MyWindow");
}

class Window{

public:
	Window();
	~Window();			//�|�����[�t�B�Y���͎g�p���Ȃ�����virtual�͂��Ă��Ȃ�

	bool WindowInit();
	bool Process() const;

#pragma region Accessor
	bool SetWindowSize(const int wid, const int hig);
	bool SetScreenMode(const bool flg);
	bool SetWindowName(const TCHAR* name);
	bool SetWindowIcon();
	bool SetBackgroundColor(const int color);
	bool SetBackgroundColor(const int r, const int g, const int b);
#pragma endregion

protected:
	WNDCLASS wc;			//�o�^��������i�[����\����
	HINSTANCE hInstance;	//�C���X�^���X�n���h�����擾
	HWND hWnd;
	int widthSize;
	int heightSize;
	bool isMaxWindowSize;
	int nCmdShow;
	TCHAR windowName[Max_NameSize];

};

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);