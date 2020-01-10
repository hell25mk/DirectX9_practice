#include "Window.h"

/// <summary>
/// Window�̍����Ɖ������Z�b�g����
/// </summary>
/// <param name="wid">�����l</param>
/// <param name="hig">�����l</param>
void Window::SetWindowSize(unsigned int wid, unsigned int hig){

	widthSize = wid;
	heightSize = hig;

}

/// <summary>
/// �X�N���[�����[�h�̐ݒ���Z�b�g����
/// </summary>
/// <param name="full">true:�t���X�N���[��,false:�E�B���h�E</param>
void Window::SetScreenMode(bool full){

	if(full){
		nCmdShow = SW_MAXIMIZE;
		return;
	}

	nCmdShow = SW_SHOW;

}

/// <summary>
/// Window�̃^�C�g�����Z�b�g����
/// </summary>
/// <param name="name">�^�C�g���̖��O</param>
void Window::SetWindowTitle(LPCTSTR title){

	_tcscpy_s(windowTitle, Max_TitleLength, title);

}

void Window::SetWindowIcon(){



}

void Window::SetBackgroundColor(int color){



}

/// <summary>
/// @brief �w�i�̐F����
/// </summary>
/// <param name="r">�Ԃ̒l</param>
/// <param name="g">�΂̒l</param>
/// <param name="b">�̒l</param>
void Window::SetBackgroundColor(int r, int g, int b){



}