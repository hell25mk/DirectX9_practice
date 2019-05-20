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
	bool SetWindowSize(int wid, int hig);
	bool SetScreenMode(bool flg);
	bool SetWindowName(LPCTSTR name);
	bool SetWindowIcon();
	bool SetBackgroundColor(int color);
	bool SetBackgroundColor(int r, int g, int b);
#pragma endregion

protected:
	virtual LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
	virtual bool WindowClose();

protected:
	WNDCLASS wc;			//�o�^��������i�[����\����
	HINSTANCE hInstance;	//�C���X�^���X�n���h�����擾
	HWND hWnd;
	int widthSize;
	int heightSize;
	bool isMaxWindowSize;
	int nCmdShow;
	TCHAR windowName[Max_NameSize];

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

};