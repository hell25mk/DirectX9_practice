#include "Window.h"

bool Window::WindowClose(){

	short onButton = MessageBox(NULL, _T("�f�X�g���C�H"), _T("���b�Z�[�W"), MB_YESNO | MB_ICONQUESTION);

	if(onButton == IDYES){
		//�E�B���h�E������ꂽ��v���O�������I������
		DestroyWindow(hWnd);
		PostQuitMessage(NULL);

		return true;
	}

	return false;
}